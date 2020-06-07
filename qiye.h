#ifndef BIGTURRET_H
#define BIGTURRET_H

#include "shipParent.h"

//大炮防御塔类
class qiye : public shipParent
{
protected:

public:
    qiye(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // QIYE_H
