#include "mainscene.h"
#include "./ui_mainscene.h"

#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>

#include "mybutton.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    setFixedSize(350, 600);

    setWindowIcon(QPixmap(":/img/Coin0001.png"));

    setWindowTitle("翻金币");

    //退出
    connect(ui->actionquit, &QAction::triggered, [this](){
        close();
    });

    //开始按钮
    MyButton* startBtn=new MyButton(":/img/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(width()*0.5-startBtn->width()*0.5,height()*0.7);

    QSoundEffect* sound=new QSoundEffect(this);

    //关卡场景
    chols=new ChooseLevelScene();

    connect(chols, &ChooseLevelScene::back, [=](int x, int y){
        sound->setSource(QUrl::fromLocalFile(":/img/BackButtonSound.wav"));
        sound->play();

        chols->hide();
        QTimer::singleShot(100,[=](){
            this->move(x, y);
            this->show();
        });
    });




    //点击事件
    connect(startBtn, &MyButton::clicked, [=](){
        qDebug()<<"点击了开始按钮!";
        startBtn->zoom1();

        //音效
        sound->setSource(QUrl::fromLocalFile(":/img/TapButtonSound.wav"));
        sound->play();

        startBtn->zoom2();

        //延时进入选择关卡场景
        QTimer::singleShot(300, [=](){
            this->hide();
            QTimer::singleShot(100,[=](){
                chols->move(x(),y());
                chols->show();
            });
        });
    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap back;
    back.load(":/img/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,width(),height(),back);

    back.load(":/img/Title.png");
    back = back.scaled(back.width()*0.5,back.height()*0.5);
    painter.drawPixmap(10,30,back.width(),back.height(),back);
}
