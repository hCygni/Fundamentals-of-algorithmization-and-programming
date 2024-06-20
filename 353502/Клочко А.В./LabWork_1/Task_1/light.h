#ifndef LIGHT_H
#define LIGHT_H

#include "movingrectangle.h"


#include <QPainter>
#include <QWidget>
#include <QPolygon>
#include <QPoint>
#include <QTimer>


class Light : public MovingRectangle
{
    Q_OBJECT
public:
    Light(QWidget *parent);

    ~Light();

    void paintEvent(QPaintEvent *event) override;

protected:
    QTimer *timer;

    bool isLight;

public slots:
    void switchLight();
};

#endif // LIGHT_H
