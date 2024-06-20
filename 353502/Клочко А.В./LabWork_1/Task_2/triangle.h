#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
public:
    explicit Triangle(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // TRIANGLE_H
