#include "mypushbutton.h"
#include "QPushButton"
#include "QDebug"
#include "QPropertyAnimation"
MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{
    qDebug()<<"我的按钮类构造调用";
}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret)
    {
        qDebug() << "图片加载失败";
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
}

void MyPushButton::zoom1()
{
    QPropertyAnimation * animation=new  QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
   //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();


}

void MyPushButton::zoom2()
{
    QPropertyAnimation * animation=new  QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
   //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //传入的按下图片不为空,说明需要有按下状态，切换图片
    if (this->pressImgPath!=""){
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if (!ret)
        {
            qDebug() << "图片加载失败";
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
    };
    //让父类执行其他内容,实际上只是拦截了然后加上了自己的一段处理

    //为什么这里不加后，start按钮也没有反应，因为start按钮也是使用mypushbutton来实现的，这里的鼠标按下和释放按钮操作已经被重写了，所以其实start
    //按钮也会走这里，拦截了没有后续不让父类执行其他内容，所以start按钮会失效，同时上面的if判断也是为了让start按钮不去替换图片
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //传入的按下图片不为空,说明需要有按下状态，切换初始图片
    if (this->pressImgPath!=""){
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (!ret)
        {
            qDebug() << "图片加载失败";
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
    };
    //让父类执行其他内容,实际上只是拦截了然后加上了自己的一段处理
    return QPushButton::mouseReleaseEvent(e);

}
