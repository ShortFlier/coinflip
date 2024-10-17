#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int levelNum);

    void paintEvent(QPaintEvent*)override;

    bool isWin=false;

    //检查是否胜利
    void victory();

private:
    int levelIndex;
    int gameArray[4][4];

    MyCoin* coinArray[4][4];


signals:
    void back(int x, int y);
};

#endif // PLAYSCENE_H
