#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

#include <circle.h>
#include <hexagon.h>
#include <line.h>
#include <plus.h>
#include <rectangle.h>
#include <rhombus.h>
#include <square.h>
#include <star.h>
#include <triangle.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    QButtonGroup *figureGroup;
    QButtonGroup *modeGroup;

    QRadioButton *rectangleRadioButton;
    QRadioButton *rhombusRadioButton;
    QRadioButton *squareRadioButton;
    QRadioButton *circleRadioButton;
    QRadioButton *lineRadioButton;
    QRadioButton *starRadioButton;
    QRadioButton *triangleRadioButton;
    QRadioButton *hexagonRadioButton;
    QRadioButton *plusRadioButton;

    QSpinBox *starSpinBox;

    QRadioButton *drawRadioButton;
    QRadioButton *moveRadioButton;

    QPushButton *rotateLeftButton;
    QPushButton *rotateRightButton;

    QPushButton *increaseFigureSizeButton;
    QPushButton *decreaseFigureSizeButton;

    QPushButton *nextFigureButton;
    QPushButton *previousFigureButton;

    QPushButton *clearButton;

    int index = -1;

    std::vector<Figure *> figures;

    QTimer *timerUpdate;
    QTimer *timerInfo;

    QLabel *centerLabel;
    QLabel *areaLabel;
    QLabel *perimeterLabel;

    QLabel *centerText;
    QLabel *areaText;
    QLabel *perimeterText;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QPainter *painter = new QPainter();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    void connectButtons();
    void disconnectButtons();

    void connectRadioButtons();

public slots:
    void createFigure();

    void updateWidget();

    void getInfo();

    void changeNumberOfThorns();

    void clearWidget();

    void nextFigure();

    void previousFigure();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
