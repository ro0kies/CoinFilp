#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include "QTimer"
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    //参数代表传入的金币路径
    MyCoin(QString btnImg);

    //金币属性
    int posX;
    int posY;
    bool flag;//正反

    //翻金币
    void changeFlag();
    QTimer *timer1; //正面翻反面
    QTimer *timer2; //反面翻正面
    int min=1;
    int max=8;

    //执行动画 标志
    bool isAnimation=false;

    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
