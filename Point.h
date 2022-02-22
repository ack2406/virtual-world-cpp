#pragma once


// class used for easier way to handle positions

class Point {
    int x;
    int y;
public:
    Point(int x, int y);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    virtual ~Point();

};