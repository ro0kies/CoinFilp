#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    //内部成员属性，记录所选择的关卡
    int levelIndex ;

    //重写paintEvent事件，画背景图
    void paintEvent(QPaintEvent *);

    MyCoin * coinBtn[4][4];
    int gameArray[4][4];    //二维数组，维护每个关卡的数据
    //是否胜利
    bool isWin;
signals:
    void choseSceneBack();
};

#endif // PLAYSCENE_H
