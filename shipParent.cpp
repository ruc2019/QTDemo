#include "shipParent.h"

int shipParent::GetX() const     //获取横坐标
{
    return mx;
}

int shipParent::GetY() const     //获取横坐标
{
    return my;
}

int shipParent::GetWidth() const //获取宽
{
    return width;
}

int shipParent::GetHeight() const //获取高
{
    return height;
}

QString shipParent::GetDefImgPath() const   //获取防御塔图片路径
{
    return DefImgPath;
}

int shipParent::GetUpLeftX() const     //获取防御塔左上角原横坐标
{
    return UpLeftX;
}

int shipParent::GetUpLeftY() const     //获取防御塔左上角原纵坐标
{
    return UpLeftY;
}

int shipParent::GetRange() const           //获取防御塔射程
{
    return Range;
}

diren* shipParent::GetAimsdiren() const //返回当前防御塔的目标怪物
{
    return aimsmon;
}

void shipParent::SetAimsdiren(diren* mon)  //设置当前防御塔的目标怪物
{
    aimsmon = mon;
}

QString shipParent::GetBulletPath() const      //返回防御塔子弹图片路径
{
    return BullPath;
}

QVector<BulletStr*>& shipParent::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void shipParent::InterBullet()     //新建子弹函数
{
    counter++;

    if(counter < 7 || !aimsmon)      //计数器到达一定数值且目标怪物不为空时
        return;

    //向子弹数组中插入子弹
    BulletStr *bull = new BulletStr(CoorStr(UpLeftX + 40, UpLeftY + 40));

    bull->coor.x = UpLeftX + 40, bull->coor.y = UpLeftY + 40;

    //计算每一个子弹的路径
    if((!(aimsmon->GetX() - bull->coor.x)))   //除数为0或时不创建子弹
    {
        delete bull;
        bull = NULL;
        goto L1;
    }

    bull->k = (aimsmon->GetY() - bull->coor.y) / (aimsmon->GetX() - bull->coor.x);
    bull->b = aimsmon->GetY() - aimsmon->GetX() * bull->k;

    bull->coor.x = UpLeftX + 40, bull->coor.y = UpLeftY + 40;

    BulletVec.push_back(bull);              //将子弹插入到子弹数组当中

    if(aimsmon->GetX() <= UpLeftX + 40)     //确定子弹的移动方向
        bull->dirflag = true;
    L1:

    counter = 0;    //计数器重置为0

}

void shipParent::BulletMove()         //子弹移动函数
{
    //子弹移动
    for(auto bulli : BulletVec)
    {
        const int speed = 24;              //子弹移动速度，每一次刷新画面移动的像素距离，这个值可以随意

        //子弹的移动方向为左则子弹x坐标每次-=，反之+=
        bulli->dirflag ? bulli->coor.x -= speed : bulli->coor.x += speed;

        bulli->coor.y = bulli->k * bulli->coor.x + bulli->b;    //子弹纵坐标改变
    }

    for(auto bullit = BulletVec.begin(); bullit != BulletVec.end(); bullit++)         //遍历删除越界子弹
        if((*bullit)->coor.x > 1040 || (*bullit)->coor.x < 0 || (*bullit)->coor.y > 640 || (*bullit)->coor.y < 0)
        {
            delete bullit;
            BulletVec.erase(bullit);
            break;
        }
}

int shipParent::GetBulletWidth() const //获取子弹的宽度
{
    return bullwidth;
}

int shipParent::GetBulletHeight() const//获取子弹的宽度
{
    return bullheight;
}

int shipParent::GetAttack() const      //获取防御塔攻击力
{
    return attack;
}

void shipParent::SetAttack(int attack)       //设置防御塔攻击力
{
    this->attack = attack;
}

void shipParent::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->width = width, this->height = height;
}

void shipParent::SetXY(int x, int y)       //设置坐标
{
    this->mx = x, this->my = y;
}

int& shipParent::SetRange()                //设置防御塔的攻击范围
{
    return Range;
}

void shipParent::SetBulletWidthHeight(int width, int height)         //设置子弹宽高
{
    bullwidth = width, bullheight = height;
}











