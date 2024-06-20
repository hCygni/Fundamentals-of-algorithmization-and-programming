#include "star.h"

Star::Star(QWidget *parent)
    : Figure(parent)
{
    this->setParent(parent);
}

void Star::drawMoveEvent(QMouseEvent *event)
{
    Figure::drawMoveEvent(event);

    this->xRadius = (event->x() - insertionPoint.x()) / 2;
    this->yRadius = (event->y() - insertionPoint.y()) / 2;

    this->centerPoint.setX(insertionPoint.x() + xRadius);
    this->centerPoint.setY(insertionPoint.y() + yRadius);

    QPointF farPoint = {centerPoint.x(), centerPoint.y() - yRadius};
    QPointF nearPoint = {centerPoint.x(), centerPoint.y() - yRadius / 2};

    double x, y;

    x = (nearPoint.x() - centerPoint.x()) * qCos(pi / numberOfThorns)
        - (nearPoint.y() - centerPoint.y()) * qSin(pi / numberOfThorns) + centerPoint.x();
    y = (nearPoint.x() - centerPoint.x()) * qSin(pi / numberOfThorns)
        + (nearPoint.y() - centerPoint.y()) * qCos(pi / numberOfThorns) + centerPoint.y();

    nearPoint.setX(x);
    nearPoint.setY(y);

    points.emplace_back(farPoint);
    points.emplace_back(nearPoint);

    for (int i = 1; i < numberOfThorns; ++i) {
        x = (farPoint.x() - centerPoint.x()) * qCos(2 * pi / numberOfThorns)
            - (farPoint.y() - centerPoint.y()) * qSin(2 * pi / numberOfThorns) + centerPoint.x();
        y = (farPoint.x() - centerPoint.x()) * qSin(2 * pi / numberOfThorns)
            + (farPoint.y() - centerPoint.y()) * qCos(2 * pi / numberOfThorns) + centerPoint.y();

        farPoint.setX(x);
        farPoint.setY(y);

        x = (nearPoint.x() - centerPoint.x()) * qCos(2 * pi / numberOfThorns)
            - (nearPoint.y() - centerPoint.y()) * qSin(2 * pi / numberOfThorns) + centerPoint.x();
        y = (nearPoint.x() - centerPoint.x()) * qSin(2 * pi / numberOfThorns)
            + (nearPoint.y() - centerPoint.y()) * qCos(2 * pi / numberOfThorns) + centerPoint.y();

        nearPoint.setX(x);
        nearPoint.setY(y);

        points.emplace_back(farPoint);
        points.emplace_back(nearPoint);
    }

    for (auto &point : points) {
        polygon << point;
    }

    calculatePerimeter();
    calculateArea();

    update();
}

void Star::drawPaintEvent(QPainter *painter)
{
    painter->setPen(3);
    painter->drawPolygon(this->polygon);
}

void Star::calculatePerimeter()
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

void Star::calculateArea()
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
