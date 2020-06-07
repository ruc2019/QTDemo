#include "beifeng.h"

//绿色防御塔类函数实现
//构造
beifeng::beifeng(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x-10, my = y-25;
    DefImgPath = QString(":/image/beifeng.png");
    width = 75, height = 88;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 200;    //射程
    BullPath = QString(":/image/yulei.png");
    bullwidth = 30, bullheight = 30;           //子弹大小
    attack = 40;    //攻击力
}
