#include "kedie.h"

//火防御塔类函数实现
//构造
kedie::kedie(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth, int Fheight)
{
    //初始化成员变量，这里不能用初始化列表
    mx = x, my = y-25;
    DefImgPath = QString(":/image/kelifulan.png");
    width = 65, height = 80;
    UpLeftX = FUpLeftX, UpLeftY = FUpLeftY;
    Range = 170;    //射程
    BullPath = QString(":/image/pao1.png");
    bullwidth = 40, bullheight = 40;           //子弹大小
    attack = 65;    //攻击力
}
