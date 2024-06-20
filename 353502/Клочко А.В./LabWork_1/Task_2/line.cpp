#include "line.h"

Line::Line(QWidget *parent)
    : Figure(parent)
{
    this->setParent(parent);
}

void Line::drawMoveEvent(QMouseEvent *event)
{
    points.emplace_back(event->pos());

    long double newCenterX = 0, newCenterY = 0;

    for (auto &point : points) {
        newCenterX += point.x();
        newCenterY += point.y();
    }

    newCenterX /= points.size();
    newCenterY /= points.size();

    centerPoint.setX(newCenterX);
    centerPoint.setY(newCenterY);

    calculatePerimeter();
    calculateArea();

    update();
}

void Line::drawPaintEvent(QPainter *painter)
{
    painter->setPen(3);
    for (int i = 1; i < points.size(); ++i) {
        painter->drawLine(points[i - 1], points[i]);
    }
    //painter->drawPolygon(this->polygon);
}

void Line::calculatePerimeter()
{
    this->perimeter = 0;
    for (int i = 1; i < points.size(); ++i) {
        this->perimeter += qSqrt(
            (points[i].x() - points[i - 1].x()) * (points[i].x() - points[i - 1].x())
            + (points[i].y() - points[i - 1].y()) * (points[i].y() - points[i - 1].y()));
    }
}

void Line::calculateArea() {}
