#include "chooselevelscene.h"

#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

#include "mybutton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(350, 600);
    setWindowIcon(QPixmap(":/img/Coin0001.png"));
    setWindowTitle("选择关卡");

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
        qDebug()<<"点击返回";
        emit back(x(), y());
    });

    QSoundEffect* sound=new QSoundEffect(this);
    //选择关卡按钮
    for(int i=0; i<20; i++){
        MyButton* btn=new MyButton(":/img/LevelIcon.png");
        btn->setParent(this);
        btn->move(35+ i%4 * 70, 150+ i/4 * 70);

        connect(btn, &MyButton::clicked, [=](){
            qDebug()<<"选择关卡："<<i+1;

            playScene=new PlayScene(i+1);

            sound->setSource(QUrl::fromLocalFile(":/img/TapButtonSound.wav"));
            sound->play();

            this->hide();
            QTimer::singleShot(100,[=](){
                playScene->move(x(),y());
                playScene->show();
            });

            connect(playScene, &PlayScene::back, [=](int x, int y){
                sound->setSource(QUrl::fromLocalFile(":/img/BackButtonSound.wav"));
                sound->play();

                playScene->hide();
                playScene->deleteLater();
                QTimer::singleShot(100,[=](){
                    this->move(x,y);
                    this->show();
                });
            });
        });

        QLabel* label=new QLabel();
        label->setParent(this);
        label->setFixedSize(btn->width(), btn->height());
        label->setText(QString::number(i+1));
        label->move(35+ i%4 * 70, 150+ i/4 * 70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap back;
    back.load(":/img/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),back);

    back.load(":/img/Title.png");
    back = back.scaled(back.width(),back.height());
    painter.drawPixmap(20,30,back.width(),back.height(),back);
}
