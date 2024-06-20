#ifndef STAR_H
#define STAR_H

#include "figure.h"

class Star : public Figure
{
public:
    explicit Star(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;

    const double pi = M_PI;
};

#endif // STAR_H
