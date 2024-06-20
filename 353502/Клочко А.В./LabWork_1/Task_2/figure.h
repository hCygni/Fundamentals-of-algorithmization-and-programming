#ifndef FIGURE_H
#define FIGURE_H
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPolygon>
#include <QPushButton>
#include <QRadioButton>
#include <QTimer>
#include <QtMath>
#include <cmath>
#include <vector>

class Figure : public QWidget
{
protected:
    Q_OBJECT

public:
    explicit Figure(QWidget *parent);

    virtual void drawPaintEvent(QPainter *painter) = 0;

    void drawClickEvent(QMouseEvent* event);

    virtual void drawMoveEvent(QMouseEvent *event) = 0;

    QPointF insertionPoint;
    QPointF centerPoint;

    double perimeter = 0;

    double area = 0;

    void startMove(QMouseEvent *event);

    void moving();

    void moveClick(QMouseEvent *event);

    int numberOfThorns;

public slots:

    void startRotateLeft();
    void stopRotateLeft();
    void rotateLeft();

    void startRotateRight();
    void stopRotateRight();
    void rotateRight();

    void startIncrease();
    void stopIncrease();
    virtual void increaseSize();

    void startDecrease();
    void stopDecrease();
    virtual void decreaseSize();

protected:
    QTimer *timer;

    double xRadius;
    double yRadius;
    QPointF movePoint;
    QPointF clickPoint;
    QPointF deltaPoint;

    std::vector<QPointF> points;
    QPolygonF polygon;

    virtual void calculatePerimeter();
    virtual void calculateArea();

private:
    const double angleDelta = 0.01;
    const double deltaSize = 1.0;
};

#endif // FIGURE_H
