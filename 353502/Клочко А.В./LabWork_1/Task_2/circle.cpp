#include "circle.h"

Circle::Circle(QWidget *parent)
    : Figure(parent)
{
    this->setParent(parent);
}

void Circle::drawMoveEvent(QMouseEvent *event)
{
    Figure::drawMoveEvent(event);

    this->xRadius = (event->x() - insertionPoint.x()) / 2;
    this->yRadius = (event->y() - insertionPoint.y()) / 2;

    int signx, signy;

    if (xRadius < 0) {
        signx = -1;
    } else
        signx = 1;

    if (yRadius < 0) {
        signy = -1;
    } else
        signy = 1;

    xRadius = std::min(abs(xRadius), abs(yRadius));
    yRadius = xRadius;

    xRadius *= signx;
    yRadius *= signy;

    this->centerPoint.setX(insertionPoint.x() + xRadius);
    this->centerPoint.setY(insertionPoint.y() + yRadius);

    calculatePerimeter();
    calculateArea();

    update();
}

void Circle::drawPaintEvent(QPainter *painter)
{
    painter->setPen(3);
    painter->drawEllipse(centerPoint.x() - xRadius,
                         centerPoint.y() - yRadius,
                         2 * xRadius,
                         2 * yRadius);
}

void Circle::calculatePerimeter()
{
    this->perimeter = 2 * pi * xRadius;
}

void Circle::calculateArea()
{
    this->area = pi * xRadius * xRadius;
}

void Circle::increaseSize()
{
    double deltaR = xRadius / 300;

    xRadius += deltaR;
    yRadius = xRadius;

    update();
}

void Circle::decreaseSize()
{
    double deltaR = xRadius / 300;

    xRadius -= deltaR;
    yRadius = xRadius;

    update();
}
