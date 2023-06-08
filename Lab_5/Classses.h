//
// Created by Ющенко Андрей on 07.06.2023.
//

#ifndef LAB_5_CLASSSES_H
#define LAB_5_CLASSSES_H
#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;


class TPoint {
public:
    double x, y;

    TPoint();
    TPoint(double x, double y);
};


class TFigure {
public:
    virtual double getArea() = 0;
    virtual double getPerimeter() = 0;
};

class TPentagon : public TFigure {
private:
    TPoint a = {0, 0 },
            b = { 0, 0 },
            c = { 0, 0 },
            d = { 0, 0 },
            e = { 0, 0 };

public:
    TPentagon() = default;
    TPentagon(TPoint a, TPoint b, TPoint c, TPoint d, TPoint e);

    double getSideLength(TPoint p1, TPoint p2);
    double getPerimeter() override;
    double getArea() override;
};

class THexagon : public TFigure {
private:
    TPoint a = {0, 0 },
        b = { 0, 0 },
        c = { 0, 0 },
        d = { 0, 0 },
        e = { 0, 0 },
        f = { 0, 0 };

public:
    THexagon() = default;
    THexagon(TPoint a, TPoint b, TPoint c, TPoint d, TPoint e, TPoint f);

    double getSideLength(TPoint p1, TPoint p2);
    double getPerimeter() override;
    double getArea() override;
};

#endif //LAB_5_CLASSSES_H
