#include "dao.h"

//构造
dao::dao(int x, int y, int width, int height)
    : mx(x), my(y), mwidth(width), mheight(height) {}

int dao::GetX() const     //获取横坐标
{
    return mx;
}

int dao::GetY() const     //获取横坐标
{
    return my;
}

int dao::GetWidth() const //获取宽
{
    return mwidth;
}

int dao::GetHeight() const //获取高
{
    return mheight;
}

