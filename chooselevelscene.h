#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include "playscene.h"


class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*) override;

private:
    PlayScene* playScene=nullptr;

signals:
    void back(int x, int y);
};

#endif // CHOOSELEVELSCENE_H
