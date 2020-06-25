#ifndef WUQI_H
#define WUQI_H

#include "shipParent.h"
//吾妻类
class wuqi : public shipParent
{
protected:

public:
    wuqi(int x, int y, int FUpLeftX, int FUpLeftY, int Fwidth = 80, int Fheight = 80);
};

#endif // WUQI_H
