#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QRect>
#include <QPoint>


class MovingRectangle : public QWidget
{
    Q_OBJECT
public:
    explicit MovingRectangle(QWidget *parent = nullptr);

    ~MovingRectangle();

    void paintEvent(QPaintEvent *event) override;

protected:
    QTimer *timerLeft;
    QTimer *timerRight;

public slots:
    void moveLeft();
    void stopMoving();
    void left();
    void moveRight();
    void right();
};

#endif // MOVINGRECTANGLE_H
