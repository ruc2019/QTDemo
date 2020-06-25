#include "beifeng.h"

//北风类函数实现
//构造
beifeng::beifeng(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    mx = x-10, my = y-25;
    DefImgPath = QString(":/image/beifeng.png");
    width = 75, height = 88;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 200;    //射程
    BullPath = QString(":/image/yulei.png");   //子弹种类
    bullwidth = 30, bullheight = 30;           //子弹大小
    attack = 40;    //攻击力
}
