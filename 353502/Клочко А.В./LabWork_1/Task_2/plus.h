#ifndef PLUS_H
#define PLUS_H

#include "figure.h"

class Plus : public Figure
{
public:
    explicit Plus(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // PLUS_H
