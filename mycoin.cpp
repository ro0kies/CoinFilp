#include "mycoin.h"
#include "QDebug"
MyCoin::MyCoin(QWidget *parent)
    : QPushButton{parent}
{

}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if (!ret)
    {
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug() << str;
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));





    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听正面翻反面的信号，并且反转金币   金币翻银币
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/Coin000%1").arg(this->min++);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断 如果翻完了，将min重置为1
        if (this->min > this->max)
        {
            this->min = 1;
            isAnimation=false;
            timer1->stop();
        }
    });
    //监听反面翻正面的信号，并且反转金币   银币翻金币
    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/Coin000%1").arg(this->max--);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断 如果翻完了，将min重置为1
        if (this->max< this->min)
        {
            this->max = 8;
            isAnimation=false;
            timer2->stop();
        }
    });
}
void MyCoin::changeFlag()
{
    //如果是正面 翻成反面
    if (this->flag)
    {
        //开始正面翻反面的定时器
        timer1->start(30);
        this->flag = false;
        isAnimation=true;
    }
    else
    {
        timer2->start(30);
        this->flag = true;
        isAnimation=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if (this->isAnimation||this->isWin){
        return ;
    }else{
        return QPushButton::mousePressEvent(e);
    }


}



