#include "car.h"

Car::Car(QWidget *parent) : MovingRectangle(parent){
    this->setParent(parent);
}

void Car::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter;

    painter->begin(this);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);

    QPolygon *lamba = new QPolygon;

    *lamba << QPoint(200, 500)
           << QPoint(550, 500)
           << QPoint(550, 475)
           << QPoint(400, 400)
           << QPoint(200, 425);

    QPolygon *headLight = new QPolygon;

    painter->drawPolygon(*lamba);

    painter->setBrush(Qt::blue);

    *headLight << QPoint(550, 475)
               << QPoint(530, 475)
               << QPoint(510, 465)
               << QPoint(510, 455);

    painter->drawPolygon(*headLight);

    painter->setBrush(Qt::black);

    painter->drawEllipse(230, 460, 70, 70);

    painter->drawEllipse(450, 470, 60, 60);

    painter->end();

}
