#ifndef DOOR_H
#define DOOR_H

#include "movingrectangle.h"


#include <QPainter>
#include <QWidget>
#include <QPolygon>
#include <QPoint>
#include <QTimer>
#include <QtCore>
//#include <cmath>


class Door : public MovingRectangle
{
    Q_OBJECT

private:
    QTimer *timerOpen;

    double x1, x2, x3, x4;
    double y1, y2, y3, y4;

    double angle;

    bool isRight;

    QPointF p1, p2, p3, p4;

public:
    Door(QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
    void changePoint(QPointF*);

public slots:
    void openDoor();
    void open();
    void stopDoor();
    void closeDoor();
};

#endif // DOOR_H
