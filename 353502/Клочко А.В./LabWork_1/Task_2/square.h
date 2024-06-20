#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    explicit Square(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // SQUARE_H
