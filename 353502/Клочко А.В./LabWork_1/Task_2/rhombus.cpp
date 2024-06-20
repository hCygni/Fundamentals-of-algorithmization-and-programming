#include "rhombus.h"

Rhombus::Rhombus(QWidget *parent)
    : Figure(parent)
{
    this->setParent(parent);
}

void Rhombus::drawMoveEvent(QMouseEvent *event)
{
    Figure::drawMoveEvent(event);

    this->xRadius = (event->x() - insertionPoint.x()) / 2;
    this->yRadius = (event->y() - insertionPoint.y()) / 2;

    this->centerPoint.setX(insertionPoint.x() + xRadius);
    this->centerPoint.setY(insertionPoint.y() + yRadius);

    points.emplace_back(centerPoint.x() - xRadius, centerPoint.y());
    points.emplace_back(centerPoint.x(), centerPoint.y() - yRadius);
    points.emplace_back(centerPoint.x() + xRadius, centerPoint.y());
    points.emplace_back(centerPoint.x(), centerPoint.y() + yRadius);

    for (auto &point : points) {
        polygon << point;
    }

    calculatePerimeter();
    calculateArea();

    update();
}

void Rhombus::drawPaintEvent(QPainter *painter)
{
    painter->setPen(3);
    painter->drawPolygon(this->polygon);
}

void Rhombus::calculatePerimeter()
{
    this->perimeter = 0;
    for (int i = 1; i < points.size(); ++i) {
        this->perimeter += qSqrt(
            (points[i].x() - points[i - 1].x()) * (points[i].x() - points[i - 1].x())
            + (points[i].y() - points[i - 1].y()) * (points[i].y() - points[i - 1].y()));
    }

    this->perimeter += qSqrt(
        (points[points.size()].x() - points[0].x()) * (points[points.size()].x() - points[0].x())
        + (points[points.size()].y() - points[0].y()) * (points[points.size()].y() - points[0].y()));
}

void Rhombus::calculateArea()
{
    this->area = 0;

    for (int i = 1; i < points.size(); ++i) {
        double a = qSqrt((points[i].x() - points[i - 1].x()) * (points[i].x() - points[i - 1].x())
                         + (points[i].y() - points[i - 1].y())
                               * (points[i].y() - points[i - 1].y()));
        double b = qSqrt((points[i].x() - centerPoint.x()) * (points[i].x() - centerPoint.x())
                         + (points[i].y() - centerPoint.y()) * (points[i].y() - centerPoint.y()));
        double c = qSqrt(
            (points[i - 1].x() - centerPoint.x()) * (points[i - 1].x() - centerPoint.x())
            + (points[i - 1].y() - centerPoint.y()) * (points[i - 1].y() - centerPoint.y()));
        double halfPerimeter = (a + b + c) / 2;

        this->area += qSqrt(halfPerimeter * (halfPerimeter - a) * (halfPerimeter - b)
                            * (halfPerimeter - c));
    }

    double a = qSqrt(
        (points[points.size()].x() - points[0].x()) * (points[points.size()].x() - points[0].x())
        + (points[points.size()].y() - points[0].y()) * (points[points.size()].y() - points[0].y()));
    double b = qSqrt((points[points.size()].x() - centerPoint.x())
                         * (points[points.size()].x() - centerPoint.x())
                     + (points[points.size()].y() - centerPoint.y())
                           * (points[points.size()].y() - centerPoint.y()));
    double c = qSqrt((points[0].x() - centerPoint.x()) * (points[0].x() - centerPoint.x())
                     + (points[0].y() - centerPoint.y()) * (points[0].y() - centerPoint.y()));
    double halfPerimeter = (a + b + c) / 2;

    this->area += qSqrt(halfPerimeter * (halfPerimeter - a) * (halfPerimeter - b)
                        * (halfPerimeter - c));
}
