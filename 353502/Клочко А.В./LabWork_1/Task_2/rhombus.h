#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

class Rhombus : public Figure
{
public:
    explicit Rhombus(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // RHOMBUS_H
