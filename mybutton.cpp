#include "mybutton.h"

#include <QPropertyAnimation>


MyButton::MyButton(QString normalImg, QString pressImg)
{
    normalImgPath=normalImg;
    pressImgPath=pressImg;

    QPixmap pix;
    if(!pix.load(normalImg)){
        qDebug()<<normalImg<<"加载失败！";
    }

    //设置大小
    setFixedSize(pix.width(), pix.height());
    //样式设置
    setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}

void MyButton::zoom1()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this, "geometry");
    //动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(x(),y(),width(),height()));
    //结束位置
    animation->setEndValue(QRect(x(),y()+10,width(),height()));
    //弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyButton::zoom2()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this, "geometry");
    //动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(x(),y()+10,width(),height()));
    //结束位置
    animation->setEndValue(QRect(x(),y(),width(),height()));
    //弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!=""){
        QPixmap pix;
        if(!pix.load(pressImgPath)){
            qDebug()<<pressImgPath<<"加载失败！";
        }

        //设置大小
        setFixedSize(pix.width(), pix.height());
        //样式设置
        setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));
    }

    //父类执行其他事件
    QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath!=""){
        QPixmap pix;
        if(!pix.load(normalImgPath)){
            qDebug()<<normalImgPath<<"加载失败！";
        }

        //设置大小
        setFixedSize(pix.width(), pix.height());
        //样式设置
        setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));
    }

    //父类执行其他事件
    QPushButton::mouseReleaseEvent(e);
}
