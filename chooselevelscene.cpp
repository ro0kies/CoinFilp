#include "chooselevelscene.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QDebug"
#include "QLabel"
#include "QSoundEffect"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    this->setFixedSize(320,500);
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    //bar->setNativeMenuBar(false);加了后会崩溃？
    //创建退出菜单项
    QAction *quitAction= startMenu->addAction("退出");

    //实现退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //选择关卡音效
    QSoundEffect *chooseSound=new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));
    //返回按钮音效
    QSoundEffect *returnSound=new QSoundEffect(this);
    returnSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav    "));

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug() <<"点击了返回按钮";
        //返回按钮音效
        returnSound->play();
        emit this->choseSceneBack(); //发送自定义信号
    });

    //创建选择关卡场景
    for(int i=0;i<20;i++){
        MyPushButton *menuBtn=new MyPushButton(":LevelIcon.png");
        menuBtn->setParent(this);
        //行     列
        //25起始值，70间隔值
        menuBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放选择关卡音效
            chooseSound->play();
            qDebug() << "选择的是第"<<i+1<<"关";

            //进入到游戏关卡中
            this->hide();//隐藏选关界面

            play=new PlayScene(i+1);
            //设置关卡位置保持一致
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景
            connect(play,&PlayScene::choseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                play->disconnect();
                delete play;

                play=nullptr;
            });


        });

        QLabel *label=new QLabel();
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置对齐方式   水平和垂直居中
        label->setAlignment(Qt::AlignCenter);

        //设置让鼠标穿透，即不让label挡住button,51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }




}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);


}
