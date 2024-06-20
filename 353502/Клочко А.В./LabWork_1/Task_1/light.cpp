#include "light.h"

Light::Light(QWidget *parent) : MovingRectangle(parent){
    this->setParent(parent);

    this->timer = new QTimer;

    this->timer->setInterval(10);

    isLight = false;

    this->hide();
}

Light::~Light(){
    delete this->timer;
}

void Light::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter;

    painter->begin(this);

    painter->setPen(Qt::yellow);
    painter->setBrush(Qt::yellow);

    QPolygon *light = new QPolygon;

    *light << QPoint(520, 460)
           << QPoint(540, 470)
           << QPoint(3000, 1270)
           << QPoint(3000, -330);

    painter->drawPolygon(*light);

    painter->end();
}

void Light::switchLight(){
    isLight ^= 1;

    if(isLight){
        this->show();
    }else{
        this->hide();
    }

    update();
}
