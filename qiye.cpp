#include "qiye.h"

//企业类函数实现
//构造
qiye::qiye(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    mx = x-5, my = y-25;
    DefImgPath = QString(":/image/qiye.png");
    width = 63, height = 88;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 230;    //射程
    BullPath = QString(":/image/fly.png");
    bullwidth = 40, bullheight = 40;           //子弹大小
    attack = 118;
}
