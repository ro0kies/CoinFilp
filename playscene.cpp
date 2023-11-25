#include "playscene.h"
#include "QDebug"
#include "QMenu"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "mycoin.h"
#include "dataconfig.h"
#include "QPropertyAnimation"
#include "QSoundEffect"
PlayScene::PlayScene(int levelNum)
{
    QString str=QString("进入了第%1关").arg(levelNum);
    this->levelIndex=levelNum;
    //qDebug()<<str;

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币关卡场景");

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

    //返回按钮音效
    QSoundEffect *returnSound=new QSoundEffect(this);
    returnSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));
    //胜利音效
    QSoundEffect *winSound=new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/LevelWinSound.wav"));
    //翻金币音效
    QSoundEffect *coinSound=new QSoundEffect(this);
    coinSound->setSource(QUrl::fromLocalFile(":/ConFlipSound.wav"));
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug() <<"翻金币场景点击了返回按钮";
        //返回音效
        returnSound->play();
        QTimer::singleShot(300,this,[=](){
            emit this->choseSceneBack(); //发送自定义信号
        });

    });

    //显示当前关卡数
    QLabel *label=new QLabel();
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    QString str2=QString("Level: %1").arg(this->levelIndex);
    label->setParent(this);

    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str2);
    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];

        }
    }




    //胜利图片显示 默认在背景外
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/LevelCompletedDialogBg.png");
    winLabel->setPixmap(tmpPix);
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) / 2, -tmpPix.height());


    //显示金币图案
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            //绘制背景图片
            QPixmap pix=QPixmap(":/BoardNode.png");
            QLabel *l=new QLabel(this);
            l->setGeometry(0,0,pix.width(),pix.height());
            l->setPixmap(pix);
            l->move(57+i*50,200+j*50);

            //创建金币
            if(this->gameArray[i][j]==1){
                //显示金币
                str=":/Coin0001.png";
            }else{
                //显示银币
                str=":/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];//1 正面 0反面

            //金币存放到金币数组
            coinBtn[i][j]=coin;
            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                coinSound->play();
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]=0 ? 1:0;

                //翻转右侧金币
                QTimer::singleShot(300,this,[=](){
                    if (coin->posX+1<=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]=0 ? 1:0;
                    }
                    //翻转左侧
                    if (coin->posX-1>=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]=0 ? 1:0;
                    }
                    //翻转上侧
                    if (coin->posY+1<=3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]=0 ? 1:0;
                    }
                    //翻转下侧
                    if (coin->posY-1>=0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]=0 ? 1:0;
                    }

                    //判断是否胜利
                    this->isWin=true;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if(coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if (this->isWin==true){
                        //游戏胜利
                        winSound->play();
                        qDebug()<<"游戏胜利";
                        //将所有按钮的胜利按钮改成true
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                coinBtn[i][j]->isWin=true;
                                //如果胜利，断开连接
                                coinBtn[i][j]->disconnect();
                            }
                        }

                        //胜利图片下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });


            });

        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
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
