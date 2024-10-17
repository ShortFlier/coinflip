#include "playscene.h"

#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSoundEffect>

#include "mybutton.h"
#include "mycoin.h"
#include "dataconfig.h"

PlayScene::PlayScene(int levelNum)
{
    qDebug()<<"进入关卡："<<levelNum;
    levelIndex=levelNum;

    //初始化
    setFixedSize(350,600);
    setWindowIcon(QPixmap(":/img/Coin0001.png"));
    setWindowTitle("关卡："+QString::number(levelNum));

    //菜单栏
    QMenuBar* bar=menuBar();
    setMenuBar(bar);
    QMenu* menu=bar->addMenu("开始");
    bar->addMenu(menu);
    QAction* quit=menu->addAction("退出");
    connect(quit, &QAction::triggered, [=](){
        close();
    });

    //返回按钮
    MyButton* backBtn=new MyButton(":/img/BackButton.png", ":/img/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(width()-backBtn->width(), height()-backBtn->height());
    //点击
    connect(backBtn, &MyButton::clicked, [=](){
        qDebug()<<"游戏中返回";
        emit back(x(), y());
    });

    //显示关卡
    QLabel* label=new QLabel(this);
    label->setText("Level：" + QString::number(levelNum));
    label->setGeometry(QRect(30, height()-50, 120, 50));
    //字体设计
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    //游戏关卡
    dataConfig data;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            gameArray[i][j]=data.mData[levelNum][i][j];
        }
    }

    QSoundEffect* sound=new QSoundEffect(this);

    //胜利图片
    QLabel* winLabel=new QLabel(this);
    QPixmap pix(":/img/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,pix.width(),pix.height());
    winLabel->setPixmap(pix);
    winLabel->move((width()-pix.width())*0.5, -pix.height());

    //显示游戏背景图
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            //图片
            QPixmap pix;
            pix.load(":/img/BoardNode.png");
            QLabel* label=new QLabel(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(pix);
            label->move(70+i*50,200+j*50);

            //创建金币
            QString img;
            if(gameArray[i][j]==1){
                //显示为金币
                img = QString(":/img/Coin0001.png");
            }else{
                img = QString(":/img/Coin0008.png");
            }
            MyCoin* coin=new MyCoin(img);
            coin->x=i;
            coin->y=j;
            coin->status=gameArray[i][j];
            coin->setParent(this);
            coin->move(72+i*50,203+j*50);
            coin->isWin=&isWin;

            coinArray[i][j]=coin;

            //点击金币
            connect(coin, &MyCoin::clicked, [=](){
                sound->setSource(QUrl::fromLocalFile(":/img/ConFlipSound.wav"));
                sound->play();

                coin->change();
                gameArray[i][j]= !gameArray[i][j];

                //翻转周围金币,延时
                QTimer::singleShot(300,[=](){
                    int x=coin->x, y=coin->y;
                    //右
                    if(x+1<4){
                        coinArray[x+1][y]->change();
                        gameArray[x+1][y]= !gameArray[x+1][y];
                    }
                    //下
                    if(y+1<4){
                        coinArray[x][y+1]->change();
                        gameArray[x][y+1]= !gameArray[x][y+1];
                    }
                    //左
                    if(x-1>=0){
                        coinArray[x-1][y]->change();
                        gameArray[x-1][y]= !gameArray[x-1][y];
                    }
                    //上
                    if(y-1>=0){
                        coinArray[x][y-1]->change();
                        gameArray[x][y-1]= !gameArray[x][y-1];
                    }

                    //判断是否胜利
//                  qDebug()<<"是否胜利："<<victory();
                    victory();
                    if(isWin){
                        //胜利结算
                        qDebug()<<"胜利";

                        sound->setSource(QUrl::fromLocalFile(":/img/LevelWinSound.wav"));
                        sound->play();

                        //胜利图片显示
                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel, "geometry");
                        //时间间隔
                        animation->setDuration(500);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(), winLabel->width(), winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+200, winLabel->width(), winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }

                });

            });

            //
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap back;
    back.load(":/img/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),back);

    back.load(":/img/Title.png");
    back = back.scaled(back.width(),back.height());
    painter.drawPixmap(20,30,back.width(),back.height(),back);

}

void PlayScene::victory()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(!gameArray[i][j])
                return ;
        }
    }
    isWin=true;
}
