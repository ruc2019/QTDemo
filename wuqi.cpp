#include "wuqi.h"

//吾妻类函数实现
wuqi::wuqi(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    mx = x-5, my = y-25;
    DefImgPath = QString(":/image/wuqi.png");
    width = 69, height = 85;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 260;    //射程
    BullPath = QString(":/image/pao2.png");
    bullwidth = 40, bullheight = 40;           //子弹大小
    attack = 94;    //攻击
}
