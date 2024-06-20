#include "figure.h"

Figure::Figure(QWidget *parent)
{
    timer = new QTimer;
}

void Figure::drawClickEvent(QMouseEvent *event){
    this->insertionPoint.setX(event->x());
    this->insertionPoint.setY(event->y());
}

void Figure::drawMoveEvent(QMouseEvent *event)
{
    points.clear();
    polygon.clear();
}

void Figure::startRotateLeft()
{
    this->timer->start(10);

    Figure::connect(timer, SIGNAL(timeout()), this, SLOT(rotateLeft()));
}

void Figure::stopRotateLeft()
{
    this->timer->stop();

    Figure::disconnect(timer, SIGNAL(timeout()), this, SLOT(rotateLeft()));
}

void Figure::rotateLeft()
{
    double angleDeltaLeft = -angleDelta;

    for (auto &point : points) {
        double x, y;
        x = (point.x() - centerPoint.x()) * qCos(angleDeltaLeft)
            - (point.y() - centerPoint.y()) * qSin(angleDeltaLeft) + centerPoint.x();
        y = (point.x() - centerPoint.x()) * qSin(angleDeltaLeft)
            + (point.y() - centerPoint.y()) * qCos(angleDeltaLeft) + centerPoint.y();

        point.setX(x);
        point.setY(y);
    }

    this->polygon.clear();

    for (auto point : points) {
        this->polygon << point;
    }

    update();
}

void Figure::startRotateRight()
{
    this->timer->start(10);

    Figure::connect(timer, SIGNAL(timeout()), this, SLOT(rotateRight()));
}

void Figure::stopRotateRight()
{
    this->timer->stop();

    Figure::disconnect(timer, SIGNAL(timeout()), this, SLOT(rotateRight()));
}

void Figure::rotateRight()
{
    double angleDeltaRight = angleDelta;

    for (auto &point : points) {
        double x, y;
        x = (point.x() + centerPoint.x()) * qCos(angleDeltaRight)
            - (point.y() + centerPoint.y()) * qSin(angleDeltaRight) + centerPoint.x();
        y = (point.x() - centerPoint.x()) * qSin(angleDeltaRight)
            + (point.y() - centerPoint.y()) * qCos(angleDeltaRight) + centerPoint.y();

        point.setX(x);
        point.setY(y);
    }

    this->polygon.clear();

    for (auto point : points) {
        this->polygon << point;
    }

    update();
}

void Figure::startIncrease()
{
    this->timer->start(10);

    Figure::connect(timer, SIGNAL(timeout()), this, SLOT(increaseSize()));
}

void Figure::stopIncrease()
{
    this->timer->stop();

    Figure::disconnect(timer, SIGNAL(timeout()), this, SLOT(increaseSize()));
}

void Figure::increaseSize()
{
    if (points.size() == 0) {
        return;
    }
    for (auto &point : points) {
        double deltaX, deltaY;

        deltaX = (point.x() - centerPoint.x()) / 300;
        deltaY = (point.y() - centerPoint.y()) / 300;

        point.setX(point.x() + deltaX);
        point.setY(point.y() + deltaY);
    }

    this->polygon.clear();

    for (auto point : points) {
        this->polygon << point;
    }

    calculatePerimeter();
    calculateArea();

    update();
}

void Figure::startDecrease()
{
    this->timer->start(10);

    Figure::connect(timer, SIGNAL(timeout()), this, SLOT(decreaseSize()));
}

void Figure::stopDecrease()
{
    this->timer->stop();

    Figure::disconnect(timer, SIGNAL(timeout()), this, SLOT(decreaseSize()));
}

void Figure::decreaseSize()
{
    if (points.size() == 0) {
        return;
    }
    for (auto &point : points) {
        double deltaX, deltaY;

        deltaX = (point.x() - centerPoint.x()) / 300;
        deltaY = (point.y() - centerPoint.y()) / 300;

        point.setX(point.x() - deltaX);
        point.setY(point.y() - deltaY);
    }

    this->polygon.clear();

    for (auto point : points) {
        this->polygon << point;
    }

    calculatePerimeter();
    calculateArea();

    update();
}

void Figure::calculatePerimeter() {}

void Figure::calculateArea() {}

void Figure::startMove(QMouseEvent *event)
{
    movePoint.setX(event->x());
    movePoint.setY(event->y());

    moving();

    update();
}

void Figure::moving()
{
    deltaPoint.setX(movePoint.x() - clickPoint.x());
    deltaPoint.setY(movePoint.y() - clickPoint.y());

    this->centerPoint.setX(centerPoint.x() + deltaPoint.x());
    this->centerPoint.setY(centerPoint.y() + deltaPoint.y());

    this->insertionPoint.setX(insertionPoint.x() + deltaPoint.x());
    this->insertionPoint.setY(insertionPoint.y() + deltaPoint.y());

    for (int i = 0; i < points.size(); ++i) {
        points[i].setX(points[i].x() + deltaPoint.x());
        points[i].setY(points[i].y() + deltaPoint.y());
    }

    polygon.clear();

    for (auto &point : points) {
        polygon << point;
    }

    clickPoint = movePoint;
}

void Figure::moveClick(QMouseEvent *event)
{
    clickPoint.setX(event->x());
    clickPoint.setY(event->y());

    update();
}
