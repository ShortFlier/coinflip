#include "mycoin.h"


MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    if(!pix.load(btnImg)){
        qDebug()<<"Coin 图片加载失败："<<btnImg;
    }

    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));

    timer1=new QTimer(this);
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString img=QString(":/img/Coin000%1.png").arg(min);
        ++min;

        pix.load(img);
        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));
        //翻完了，重置min
        if(min>max){
            min=1;
            active=false;
            timer1->stop();
        }
    });

    timer2=new QTimer(this);
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString img=QString(":/img/Coin000%1.png").arg(max);
        --max;

        pix.load(img);
        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:0px;}");
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));
        //翻完了，重置min
        if(max<min){
            max=8;
            active=false;
            timer2->stop();
        }
    });

}

void MyCoin::change()
{
    if(this->status){   //正面
        timer1->start(30);
        active=true;
        status=false;
    }else{
        //反面到正面
        timer2->start(30);
        active=true;
        status=true;
    }
}


