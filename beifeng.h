#ifndef BEIFENG_H
#define BEIFENG_H

#include "shipParent.h"

//绿色炮塔类，继承防御塔父类
class beifeng : public shipParent
{
protected:

public:
    beifeng(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // BEIFENG_H
