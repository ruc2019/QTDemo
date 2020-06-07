#include "qiye.h"

qiye::qiye(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x-5, my = y-25;
    DefImgPath = QString(":/image/qiye.png");
    width = 63, height = 88;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 230;    //射程
    BullPath = QString(":/image/fly.png");
    bullwidth = 40, bullheight = 40;           //子弹大小
    attack = 118;
}
