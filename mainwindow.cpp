#include "mainwindow.h"
#include <QDebug>
#include "globalstruct.h"
#include <cmath>
#include "beifeng.h"        //北风类
#include "kedie.h"         //克爹类
#include "wuqi.h"        //吾妻类
#include "qiye.h"          //企业类
#include <QPushButton>

#define MouClickRegion(X, Width, Y, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

#define X40(X, Y) ((X) - 1) * 40 + 10, ((Y) - 1) * 40 + 10

//怪物  路径点数组名、怪物初始坐标、怪物编号
#define Insterdiren(PathNum, StaCoorNum, direnId)     \
direnVec.push_back(new diren(pointarr[PathNum], PathLength[PathNum], X40(staco[StaCoorNum].x, staco[StaCoorNum].y), direnId));

//石油判断
inline bool MainWindow::DeductionMoney(int money)
{
    if (this->money - money < 0) return true; //判断金钱是否足够
    this->money -= money; //扣除金钱
    moneylable->setText(QString("石油：%1").arg(this->money)); //刷新标签文本
    return false;
}

//构造
MainWindow::MainWindow(int LevelNumber) : LevelNumber(LevelNumber)
{
    //窗口大小
    setFixedSize(1040, 640);

    //名字
    setWindowTitle("保卫钻石");

    QLabel *victorylable = new QLabel(this);
    victorylable->move(176, 180);
    victorylable->setFont(QFont("楷体", 110));
    victorylable->setText(QString("win win win"));
    victorylable->hide();

    QTimer* timer2 = new QTimer(this);
    timer2->start(2000);

    connect(timer2,&QTimer::timeout,[=]()
    {
        //根据关卡编号确定执行怪物的路径方案
        switch (LevelNumber)
        {
        case 0:
        {

            CoorStr* Waypointarr1[] = {new CoorStr(X40(8, 6)/*X40是两个参数，为X坐标和Y坐标*/), new CoorStr(X40(2, 6)), new CoorStr(X40(2, 13)), new CoorStr(X40(19, 13)), new CoorStr(X40(19, 9)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(20, 5)), new CoorStr(X40(14, 5)), new CoorStr(X40(14, 9)),new CoorStr(homecoor->x, homecoor->y)}; //最后的路径点设为家
            //起点们
            CoorStr staco[] = {CoorStr(8, 0), CoorStr(20, 0), CoorStr(8, -1), CoorStr(20, -1)};

            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr2)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案

            break;
        }
        case 1:
        {

            CoorStr* Waypointarr1[] = {new CoorStr(X40(4, 8)), new CoorStr(X40(16, 8)), new CoorStr(X40(16, 13)), new CoorStr(X40(6, 13)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(11, 8)), new CoorStr(X40(20, 8)), new CoorStr(X40(20, 13)), new CoorStr(X40(6, 13)), new CoorStr(homecoor->x, homecoor->y)};

            //起点们
            CoorStr staco[] = {CoorStr(4, 0), CoorStr(11, 0), CoorStr(4, -1), CoorStr(11, -1)};

            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr2)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案
            break;
        }

        case 2:
        {

            CoorStr* Waypointarr1[] = {new CoorStr(X40(12, 9)), new CoorStr(X40(8, 9)), new CoorStr(X40(8, 0)), new CoorStr(homecoor->x, homecoor->y)};
            CoorStr* Waypointarr2[] = {new CoorStr(X40(12, 9)), new CoorStr(X40(16, 9)), new CoorStr(X40(16, 0)), new CoorStr(homecoor->x, homecoor->y)};

            //起点们
            CoorStr staco[] = {CoorStr(12, 16), CoorStr(12, 16), CoorStr(12, 17), CoorStr(12, 18)};

            int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

            IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路的产生怪物方案
            break;
        }
        }
    });

//    setMouseTracking(true);

    QPushButton* disranpush = new QPushButton(this);
    disranpush->setStyleSheet("color:black");
    disranpush->setGeometry(880,60, 150, 45);
    disranpush->setFont(QFont("宋体", 10));
    disranpush->setText("攻击范围");

    connect(disranpush,&QPushButton::clicked,[=](){
        if (DisplayAllRange)
        {
            DisplayAllRange = false;
            disranpush->setText("攻击范围");
        }
        else
        {
            DisplayAllRange = true;
            disranpush->setText("隐藏范围");
        };
        update();
    });
    //石油
    moneylable->move(900, 0);
    setStyleSheet("color:white");
    moneylable->setFont(QFont("微软雅黑", 12));
    moneylable->setText(QString("石油：%1").arg(money));
    //钻石
    QLabel *lifelable = new QLabel(this);
    lifelable->setGeometry(900, 20, 220, 40);
    lifelable->setFont(QFont("微软雅黑", 12));
    lifelable->setText(QString("钻石：%1").arg(life));

    QTimer* timer = new QTimer(this);
    timer->start(120);

    connect(timer,&QTimer::timeout,[=](){
        for (auto defei : shipVec){
            if (!defei->GetAimsdiren()){
                for(int i = direnVec.size() - 1; i >= 0; i--)
                    if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                        direnVec.at(i)->GetX() + (direnVec.at(i)->GetWidth() >> 1),
                        direnVec.at(i)->GetY() + (direnVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsdiren(direnVec.at(i));
                        break;
                    }
            }
            else
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsdiren()->GetX() + (defei->GetAimsdiren()->GetWidth() >> 1),
                    defei->GetAimsdiren()->GetY() + (defei->GetAimsdiren()->GetHeight() >> 1)) <= defei->GetRange())
                {

                     defei->InterBullet();
                }
            if (defei->GetAimsdiren())
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei->GetAimsdiren()->GetX() + (defei->GetAimsdiren()->GetWidth() >> 1),
                    defei->GetAimsdiren()->GetY() + (defei->GetAimsdiren()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsdiren(NULL);
        }
        for (auto defei : shipVec)
            defei->BulletMove();
        for (auto Moni = direnVec.begin(); Moni != direnVec.end(); Moni++)
            if((*Moni)->Move())
            {
                delete *Moni;
                direnVec.erase(Moni);

                life--;
                lifelable->setText(QString("钻石：%1").arg(life));
                if (life <= 0) this->close();
                break;
            }
        for (auto defei : shipVec)
        {
            auto &tbullvec = defei->GetBulletVec();
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)
                for (auto monit = direnVec.begin(); monit != direnVec.end(); monit++)
                    if ((*bullit)->GetX() + (defei->GetBulletWidth() >> 1) >= (*monit)->GetX() && (*bullit)->GetX() <= (*monit)->GetX() + (*monit)->GetWidth() &&
                       (*bullit)->GetY() + (defei->GetBulletHeight() >> 1) >= (*monit)->GetY() && (*bullit)->GetY() <= (*monit)->GetY() + (*monit)->GetHeight()){
                        tbullvec.erase(bullit);
                        (*monit)->SetHealth((*monit)->GetHealth() - defei->GetAttack());
                        if ((*monit)->GetHealth() <= 0)
                        {
                            for (auto defei2 : shipVec)
                                if (defei2->GetAimsdiren() == *monit)
                                    defei2->SetAimsdiren(NULL);
                            direnVec.erase(monit);
                            money += RewardMoney;
                            moneylable->setText(QString("石油：%1").arg(money));
                        }
                        goto L1;
                    }
            L1:;
        }
        update();
    });
}
void MainWindow::IrodMonsProgDefa(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* staco, int* PathLength, QLabel* victorylable)
{
    CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};
    if(counter >= 1 && counter <= 12)
    {
        Insterdiren(0, 0, 1);
    }
    else if(counter > 12 && counter <= 34)
    {
        Insterdiren(0, 0, 1);
        Insterdiren(1, 1, 2);
    }
    else if (counter > 34 && counter <= 35)
    {
        Insterdiren(0, 0, 3);
        Insterdiren(1, 1, 3);
    }
    else if (counter > 35 && counter <= 52)
    {
        Insterdiren(0, 2, 4);
        Insterdiren(0, 0, 4);
        Insterdiren(1, 1, 1);
    }
    if(counter > 52 && counter <= 56)
    {
        Insterdiren(0, 0, 3);
        Insterdiren(1, 1, 3);
    }
    if (counter > 52 && counter <= 71)
    {
        Insterdiren(0, 2, 2);
        Insterdiren(0, 0, 5);
        Insterdiren(1, 3, 1);
        Insterdiren(1, 1, 4);
    }

    if (counter > 71 && direnVec.empty())
        victorylable->show();

    counter++;
    update();
}
void MainWindow::DrawMapArr(QPainter& painter)
{
    //第一关
    int Map_1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 3, 6, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 6, 6, 1, 1, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0,
        0, 1, 1, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1,
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 3, 6, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0,
        0, 1, 1, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第二关
    int Map_2[16][26] =
    {
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 3, 6, 1, 1, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0,
        0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 6, 6, 0, 0, 0, 3, 6, 0, 0, 6, 6, 1, 1, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 1, 1, 6, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第三关
    int Map_3[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 3, 6, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 6, 6, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map[16][26];
    switch (LevelNumber)
    {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map_3, sizeof(Map));
        break;
    default:
        break;
    }

    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/hai.jpg"));
                break;
            case 1:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/lujing.jpg"));
                break;
            case 3:
                painter.drawPixmap(i * 40, j * 40, 80, 80,
                    QPixmap(":/image/xiaodao.png"));
                daoVec.push_back(new dao(i * 40, j * 40));
                break;
            case 5:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/image/lujing.jpg"));
                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,
        QPixmap(":/image/mubiao.png"));
}
void MainWindow::DrawSelectionBox(QPainter& painter)
{
    if (!SelBox->GetDisplay())
        return;
    painter.drawPixmap(SelBox->GetX(), SelBox->GetY(), SelBox->GetWidth(), SelBox->GetHeight(),
        QPixmap(SelBox->GetImgPath()));
    SubbutStr *ASubBut = SelBox->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        painter.drawPixmap(ASubBut[i].SubX, ASubBut[i].SubY, ASubBut[i].SubWidth, ASubBut[i].SubHeight,
            QPixmap(ASubBut[i].SubImgPath));
    painter.setPen(QPen(Qt::yellow, 6, Qt::SolidLine));
    painter.drawRect(QRect(SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 80));
}
void MainWindow::DrawDefenseTower(QPainter& painter)
{
    for (auto defei : shipVec)
    {
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40), defei->GetRange(), defei->GetRange());
        for (auto bulli : defei->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, defei->GetBulletWidth(), defei->GetBulletHeight(),QPixmap(defei->GetBulletPath()));
        painter.translate(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40);
        painter.translate(-(defei->GetUpLeftX() + 40), -(defei->GetUpLeftY() + 40));
        painter.drawPixmap(defei->GetX(), defei->GetY(), defei->GetWidth(), defei->GetHeight(), QPixmap(defei->GetDefImgPath())/*图片路径*/);
        painter.resetTransform();
    }
}
void MainWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : direnVec)
        painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
}
void MainWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    for (auto defei : shipVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {
            painter.setPen(QPen(Qt::red));
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/image/qianghua.jpg"));
        }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    painter.setRenderHint(QPainter::Antialiasing);

    DrawMapArr(painter);        //画地图

    DrawDefenseTower(painter);  //画船和子弹

    DrawMonster(painter);       //画怪

    DrawRangeAndUpgrade(painter);//画攻击范围和升级

    DrawSelectionBox(painter);  //画选择框
}

//鼠标点击事件
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;

    //判断升级按钮的点击
    if (DisplayRange)
    {
        if (MouClickRegion(DisplayRangeX + 10, 60 , DisplayRangeY - 80, 60))
        {
            //设置防御塔宽高，攻击力，微调坐标
            for (auto defei : shipVec)
                if (defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (DeductionMoney(200)) return;        //升级需要200

                    defei->SetAttack(defei->GetAttack() + 30);          //每次升级攻击+30
                    defei->SetWidthHeight(defei->GetWidth() + 8, defei->GetHeight() + 13);   //升级变大
                    defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整坐标
                    defei->SetAimsdiren(NULL);
                    defei->SetRange() += 14;                            //设置攻击范围
                    defei->SetBulletWidthHeight(defei->GetBulletWidth() + 5, defei->GetBulletHeight() + 5);          //设置子弹宽高
                    break;
                }

            SelBox->SetDisplay(false);
            DisplayRange = false;
            update();
            return;
        }
    }

    //判断选择框四个子按钮的点击
    SubbutStr *ASubBut = SelBox->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        if (MouClickRegion(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelBox->GetDisplay())
        {
            SelBox->SetDisplay(false);      //取消显示选择框

            //根据点击的不同的按钮，将防御塔子类插入到防御塔父类数组
            switch (i)
            {
            case 0:
                if (DeductionMoney(100)) return;    //扣除金钱
                shipVec.push_back(new beifeng(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
                break;
            case 1:
                if (DeductionMoney(160)) return;
                shipVec.push_back(new kedie(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 72, 46));
                break;
            case 2:
                if (DeductionMoney(240)) return;
                shipVec.push_back(new wuqi(SelBox->GetX() + 110, SelBox->GetY() + 112, SelBox->GetX() + 95, SelBox->GetY() + 95, 76, 50));
                break;
            case 3:
                if (DeductionMoney(400)) return;
                shipVec.push_back(new qiye(SelBox->GetX() + 110, SelBox->GetY() + 104, SelBox->GetX() + 95, SelBox->GetY() + 95, 80, 70));
                break;
            default:
                break;
            }

            update();
            return;
        }

    //遍历所有塔坑
    for (auto APit : daoVec)
        //判断点击塔坑
        if (MouClickRegion(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;               //降防御塔的升级选择显示关闭
            for (auto defei : shipVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(defei->GetUpLeftX() == APit->GetX() && defei->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }

            SelBox->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
    SelBox->SetDisplay(false);      //取消显示选择框
}
//析构释放内存
MainWindow::~MainWindow()
{
    //释放防御塔坑指针数组TowerPitVec
    for (auto it = daoVec.begin(); it != daoVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放选择框类SelBox
    delete SelBox;
    SelBox = NULL;

    //释放防御塔父类指针数组DefeTowerVec
    for (auto it = shipVec.begin(); it != shipVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    //释放怪物数组MonsterVec
    for (auto it = direnVec.begin(); it != direnVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    delete homecoor;
}
