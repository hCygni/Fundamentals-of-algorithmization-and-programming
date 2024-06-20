#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
public:
    explicit Circle(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

public slots:

    void increaseSize() override;
    void decreaseSize() override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;

    const double pi = M_PI;
};

#endif // CIRCLE_H
