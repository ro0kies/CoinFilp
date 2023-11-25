#include "mainscene.h"
#include "ui_mainscene.h"
#include "QPainter"
#include "QPixmap"
#include "mypushbutton.h"
#include "QTimer"
#include "QSoundEffect"  //多媒体模块的音效头文件

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币游戏主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮的音效
    QSoundEffect *startSound=new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));



    //开始按钮
    MyPushButton *startBtn=new MyPushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene=new ChooseLevelScene();

    //监听选择关卡的返回按钮信号
    connect(chooseScene,&ChooseLevelScene::choseSceneBack,[=](){
        //延时0.2s返回
        QTimer::singleShot(200,this,[=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();//选择关卡场景隐藏
            this->show();//重新显示主场景
        });
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了开始";
        //播放开始音效
        //设置播放次数
        //startSound->setLoopCount(-1);
        startSound->play();

        //弹起动画
        startBtn->zoom1();

        startBtn->zoom2();

        //延时进入到选择关卡场景中
        QTimer::singleShot(300,this,[=](){
            //设置chooseScene场景位置
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();
        });


    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.drawLine(QPoint(0,0),QPoint(100,100 ));
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":Title.png");
    //缩放
    pix= pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

