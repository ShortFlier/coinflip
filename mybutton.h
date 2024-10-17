#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QString>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString normalImg, QString pressImg="");

    //弹跳
    void zoom1();
    void zoom2();

    //按下、释放
    void mousePressEvent(QMouseEvent*)override;
    void mouseReleaseEvent(QMouseEvent*)override;

private:
    QString normalImgPath;
    QString pressImgPath;
signals:
};

#endif // MYBUTTON_H
