#include "diren.h"
#include <QDebug>

//怪物类函数实现
diren::diren(CoorStr **pointarr, int arrlength, int x, int y, int fid) :
    mx(x), my(y), id(fid)
{
    for(int i = 0; i < arrlength; i++)      //将传进来的数组插入到Waypoint动态数组
        Waypoint.push_back(pointarr[i]);


    //确定不同怪物的生命值
    switch (id)
    {
    case 1: //怪1
        health = 100;
        mwidth = 64, mheight = 64;
        ImgPath = ":/image/B 50.png";
        break;
    case 2: //怪2
        health = 160;
        mwidth = 64, mheight = 64;
        ImgPath = ":/image/B 99.png";
        break;
    case 3: //怪3
        health = 300;
        mwidth = 64, mheight = 64;
        ImgPath = ":/image/B 115.png";
        break;
    case 4: //怪4
        health = 400;
        mwidth = 60, mheight = 90;
        ImgPath = ":/image/Upink.png";
        break;
    case 5: //怪5
        health = 500;
        mwidth = 60, mheight = 75;
        ImgPath = ":/image/Ublack.png";
        break;
    default:
        break;
    }
}

//怪物按设定路径点移动
bool diren::Move()
{
    if(Waypoint.empty())
        return true;

    //如果第一个路径点的y小于怪物原本的路径点，则怪物向下走
    if (Waypoint.at(0)->y > my) //下
    {
        my += mspeed;
        return false;
    }

    if (Waypoint.at(0)->x < mx) //左
    {
        mx -= mspeed;
        return false;
    }

    if (Waypoint.at(0)->x > mx) //右
    {
        mx += mspeed;
        return false;
    }

    if (Waypoint.at(0)->y < my) //上
    {
        my -= mspeed;
        return false;
    }

    //如果怪物的坐标和路径点坐标几乎重合，则删除这个路径点
    if (Waypoint.at(0)->y == my && Waypoint.at(0)->x == mx)
    {
//        delete Waypoint.begin();                //释放坐标点内存
        Waypoint.erase(Waypoint.begin());       //从数组中删除

//        return false;
    }

    return false;
}


int diren::GetX() const       //获取横坐标
{
    return mx;
}

int diren::GetY() const       //获取横坐标
{
    return my;
}

int diren::GetWidth() const   //获取宽
{
    return mwidth;
}

int diren::GetHeight() const  //获取高
{
    return mheight;
}

QString diren::GetImgPath() const //获取图片路径
{
    return ImgPath;
}

int diren::GetId() const      //获取编号
{
    return id;
}

int diren::GetHealth() const  //获取生命值
{
    return health;
}

void diren::SetHealth(int fhealth)//设置生命值
{
    health = fhealth;
}

