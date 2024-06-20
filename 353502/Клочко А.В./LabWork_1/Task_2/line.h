#ifndef LINE_H
#define LINE_H

#include "figure.h"

class Line : public Figure
{
public:
    explicit Line(QWidget *parent);

    void drawMoveEvent(QMouseEvent *event) override;

    void drawPaintEvent(QPainter *painter) override;

private:
    void calculatePerimeter() override;

    void calculateArea() override;
};

#endif // LINE_H
