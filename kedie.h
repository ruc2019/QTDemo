#ifndef FIRETURRECT_H
#define FIRETURRECT_H

#include "shipParent.h"

//火炮塔类，继承防御塔父类
class kedie: public shipParent
{
protected:

public:
    kedie(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // KEDIE_H
