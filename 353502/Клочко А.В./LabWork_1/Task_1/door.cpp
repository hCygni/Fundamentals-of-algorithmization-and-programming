#include "door.h"

Door::Door(QWidget *parent) : MovingRectangle(parent){
    this->setParent(parent);

    this->timerOpen = new QTimer;

    this->timerOpen->setInterval(10);

    angle = 0;

    isRight = true;

    x1 = 325, x2 = 425, x3 = 435, x4 = 315;
    y1 = 475, y2 = 475, y3 = 445, y4 = 425;

    p1 = {x1, y1}, p2 = {x2, y2}, p3 = {x3, y3}, p4 = {x4, y4};
}

void Door::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter;

    painter->begin(this);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);

    QPolygonF *door = new QPolygonF;

    *door << p1
          << p2
          << p3
          << p4;

    painter->drawPolygon(*door);

    painter->end();
}

void Door::openDoor(){
    this->timerOpen->start(10);

    isRight = true;

    Door::connect(timerOpen, SIGNAL(timeout()), this, SLOT(open()));
}

void Door::closeDoor(){
    this->timerOpen->start(10);

    isRight = false;

    Door::connect(timerOpen, SIGNAL(timeout()), this, SLOT(open()));
}

void Door::stopDoor(){
    Door::disconnect(timerOpen, SIGNAL(timeout()), this, SLOT(open()));
}

void Door::changePoint(QPointF* point){
    double t = 0.01;

    if(!isRight){
        t *= -1;
    }

    angle += t;

    if(angle > 7 || angle < 0){
        angle -= t;
        Door::stopDoor();
        return;
    }

    double x, y;
    x = (point->x() - x2) * qCos(t) - (point->y() - y2) * qSin(t) + x2;
    y = (point->x() - x2) * qSin(t) + (point->y() - y2) * qCos(t) + y2;

    point->setX(x);
    point->setY(y);
}

void Door::open(){

    changePoint(&p1);
    changePoint(&p2);
    changePoint(&p3);
    changePoint(&p4);

    update();
    //this->repaint();
}


