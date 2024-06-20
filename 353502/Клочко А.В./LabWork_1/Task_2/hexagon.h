#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"

class Hexagon : public Figure
{
public:
    explicit Hexagon(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;

    const double pi = M_PI;

    const int numberOfVerticles = 6;
};

#endif // HEXAGON_H
