#include "movingrectangle.h"


MovingRectangle::MovingRectangle(QWidget *parent)
    : QWidget{}
{
    this->setParent(parent);


    this->timerLeft = new QTimer;

    this->timerLeft->setInterval(10);


    this->timerRight = new QTimer;

    this->timerRight->setInterval(10);
}

MovingRectangle::~MovingRectangle(){
    delete this->timerLeft;
    delete this->timerRight;
}

void MovingRectangle::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter;

    painter->begin(this);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::yellow);

    QRect *rectangle = new QRect(QPoint(500, 400), QPoint(700, 600));

    painter->drawRect(*rectangle);

    painter->end();
}

void MovingRectangle::moveLeft(){
    this->timerLeft->start();

    MovingRectangle::connect(timerLeft, SIGNAL(timeout()), this, SLOT(left()));
}

void MovingRectangle::left(){
    this->move(this->x() - 2, this->y());
}

void MovingRectangle::stopMoving(){
    this->timerLeft->stop();
    this->timerRight->stop();

    MovingRectangle::disconnect(timerLeft, SIGNAL(timeout()), this, SLOT(left()));
    MovingRectangle::disconnect(timerRight, SIGNAL(timeout()), this, SLOT(right()));
}

void MovingRectangle::moveRight(){
    this->timerRight->start();

    MovingRectangle::connect(timerRight, SIGNAL(timeout()), this, SLOT(right()));
}

void MovingRectangle::right(){
    this->move(this->x() + 3, this->y());
}
