#include "wuqi.h"

//光炮防御塔函数实现
wuqi::wuqi(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x-5, my = y-25;
    DefImgPath = QString(":/image/wuqi.png");
    width = 69, height = 85;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 260;    //射程
    BullPath = QString(":/image/pao2.png");
    bullwidth = 40, bullheight = 40;           //子弹大小
    attack = 94;    //攻击
}
