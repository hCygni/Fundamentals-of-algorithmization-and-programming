#ifndef CAR_H
#define CAR_H

#include "movingrectangle.h"

/*
#include <QPainter>
#include <QWidget>
#include <QPolygon>
#include <QPoint>
*/

class Car : public MovingRectangle
{
    Q_OBJECT
public:
    Car(QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
};

#endif // CAR_H
