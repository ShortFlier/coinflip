#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);
    int x;
    int y;
    bool status;

    void change();

    QTimer* timer1;
    QTimer* timer2;
    int min=1;
    int max=8;

    bool* isWin;

    //是否触发动画
    bool active=false;

    void mousePressEvent(QMouseEvent* e)override{
        if(!active&& !(*isWin)){
            QPushButton::mousePressEvent(e);
        }
    }
    void mouseReleaseEvent(QMouseEvent* e)override{
        if(!active&& !(*isWin)){
            QPushButton::mouseReleaseEvent(e);
        }
    }

signals:
};

#endif // MYCOIN_H
