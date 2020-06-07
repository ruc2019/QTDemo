#ifndef DAO_H
#define DAO_H

#include <QVector>

class dao
{
private:
    const int mx, my;           //位置坐标
    const int mwidth, mheight;  //宽高

public:
    //构造   坐标、宽高
    dao(int x, int y, int width = 80, int height = 80);

    int GetX() const;     //横坐标
    int GetY() const;     //横坐标
    int GetWidth() const; //宽
    int GetHeight() const;//高
};

#endif // DAO_H
