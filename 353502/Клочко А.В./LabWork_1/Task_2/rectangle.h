#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure
{
public:
    explicit Rectangle(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // RECTANGLE_H
