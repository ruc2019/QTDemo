#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>  //鼠标
#include <Qtimer>       //定时器
#include "dao.h"
#include "selectionbox.h"
#include "shipParent.h"
#include "diren.h"
#include <QLabel>

class MainWindow : public QWidget
{
//    Q_OBJECT
private:
    QVector<dao*> daoVec;  //岛数组
    SelectionBox* SelBox = new SelectionBox(":/image/SelectionBox.png"); //选择框类

    QVector<shipParent*> shipVec; //重要防御塔父类数组

    QVector<diren*> direnVec;           //怪物数组

    void paintEvent(QPaintEvent *);         //绘图事件
    void mousePressEvent(QMouseEvent *);    //鼠标点击事件
//    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件

    void DrawMapArr(QPainter&);             //用于画出地图函数
    void DrawSelectionBox(QPainter&);       //用于画出选择框
    void DrawDefenseTower(QPainter&);       //画出防御塔
    void DrawMonster(QPainter&);            //画出怪物
    void DrawRangeAndUpgrade(QPainter&);    //画出防御塔攻击范围和升级按钮

    int DisplayRangeX, DisplayRangeY;       //用于记录显示范围的防御塔的坐标
    bool DisplayRange = false;              //用于显示防御塔攻击范围

    int money = 1000;   //记录石油
    QLabel *moneylable = new QLabel(this);   //显示石油标签控件

    inline bool DeductionMoney(int);         //判断石油是否足够并刷新标签

    int life = 10;      //生命数量

    int counter = 0;    //用于产生怪的计数器

    const int RewardMoney = 28; //每次击败怪获得的石油数量

    CoorStr *homecoor = new CoorStr(0, 0);  //记录家的坐标，从地图中自动获取

    void IrodMonsProgDefa(CoorStr**, CoorStr**, CoorStr*, int*, QLabel*); //预设两条路产生怪物方案函数

    const int LevelNumber;      //标识关卡

    bool DisplayAllRange = false;  //标识是否显示所有防御塔的攻击范围

public:
    MainWindow(int);            //构造
    ~MainWindow();
};

#endif  //MAINWINDOW_H
