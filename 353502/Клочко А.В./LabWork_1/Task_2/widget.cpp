#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    figures.clear();

    timerUpdate = new QTimer;
    timerInfo = new QTimer;

    timerUpdate->start(10);
    timerInfo->start(10);

    this->rectangleRadioButton = new QRadioButton("Rectangle", this);
    this->rectangleRadioButton->setGeometry(1700, 40, 100, 30);

    this->rhombusRadioButton = new QRadioButton("Rhombus", this);
    this->rhombusRadioButton->setGeometry(1700, 60, 100, 30);

    this->squareRadioButton = new QRadioButton("Square", this);
    this->squareRadioButton->setGeometry(1700, 80, 100, 30);

    this->circleRadioButton = new QRadioButton("Circle", this);
    this->circleRadioButton->setGeometry(1700, 100, 100, 30);

    this->hexagonRadioButton = new QRadioButton("Hexagon", this);
    this->hexagonRadioButton->setGeometry(1700, 120, 100, 30);

    this->lineRadioButton = new QRadioButton("Line", this);
    this->lineRadioButton->setGeometry(1700, 140, 100, 30);

    this->plusRadioButton = new QRadioButton("Plus", this);
    this->plusRadioButton->setGeometry(1700, 160, 100, 30);
    //
    this->starRadioButton = new QRadioButton("Star", this);
    this->starRadioButton->setGeometry(1700, 210, 100, 30);

    this->starSpinBox = new QSpinBox(starRadioButton);
    this->starSpinBox->setGeometry(50, 0, 50, 30);

    starSpinBox->setMinimum(2);
    starSpinBox->setMaximum(100);
    connect(starSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeNumberOfThorns()));
    //
    this->triangleRadioButton = new QRadioButton("Triangle", this);
    this->triangleRadioButton->setGeometry(1700, 180, 100, 30);

    this->rotateLeftButton = new QPushButton("⟲", this);
    this->rotateLeftButton->setGeometry(1700, 700, 30, 30);

    this->rotateRightButton = new QPushButton("⟳", this);
    this->rotateRightButton->setGeometry(1750, 700, 30, 30);

    this->increaseFigureSizeButton = new QPushButton("+", this);
    this->increaseFigureSizeButton->setGeometry(1700, 750, 30, 30);

    this->decreaseFigureSizeButton = new QPushButton("-", this);
    this->decreaseFigureSizeButton->setGeometry(1750, 750, 30, 30);

    this->nextFigureButton = new QPushButton("->", this);
    this->nextFigureButton->setGeometry(1750, 800, 30, 30);

    this->previousFigureButton = new QPushButton("<-", this);
    this->previousFigureButton->setGeometry(1700, 800, 30, 30);

    this->clearButton = new QPushButton("clear", this);
    this->clearButton->setGeometry(1700, 900, 80, 30);

    this->drawRadioButton = new QRadioButton("draw", this);
    this->drawRadioButton->setGeometry(1700, 600, 100, 30);

    this->moveRadioButton = new QRadioButton("move", this);
    this->moveRadioButton->setGeometry(1700, 650, 100, 30);
    //
    this->perimeterLabel = new QLabel("perimeter", this);
    this->perimeterLabel->setGeometry(1700, 410, 80, 30);

    this->perimeterText = new QLabel("0", this);
    this->perimeterText->setGeometry(1700, 440, 80, 30);

    this->areaLabel = new QLabel("area", this);
    this->areaLabel->setGeometry(1700, 470, 60, 30);

    this->areaText = new QLabel("0", this);
    this->areaText->setGeometry(1700, 500, 80, 30);

    this->centerLabel = new QLabel("center", this);
    this->centerLabel->setGeometry(1700, 530, 65, 30);

    this->centerText = new QLabel("0", this);
    this->centerText->setGeometry(1700, 560, 80, 40);

    figureGroup = new QButtonGroup(this);
    modeGroup = new QButtonGroup(this);

    this->figureGroup->addButton(circleRadioButton);
    this->figureGroup->addButton(hexagonRadioButton);
    this->figureGroup->addButton(lineRadioButton);
    this->figureGroup->addButton(plusRadioButton);
    this->figureGroup->addButton(rectangleRadioButton);
    this->figureGroup->addButton(rhombusRadioButton);
    this->figureGroup->addButton(squareRadioButton);
    this->figureGroup->addButton(starRadioButton);
    this->figureGroup->addButton(triangleRadioButton);

    this->modeGroup->addButton(drawRadioButton);
    this->modeGroup->addButton(moveRadioButton);

    drawRadioButton->setChecked(true);

    connectRadioButtons();

    QWidget::connect(this->timerUpdate, SIGNAL(timeout()), this, SLOT(updateWidget()));
    QWidget::connect(this->timerInfo, SIGNAL(timeout()), this, SLOT(getInfo()));

    QWidget::connect(this->nextFigureButton, SIGNAL(clicked()), this, SLOT(nextFigure()));
    QWidget::connect(this->previousFigureButton, SIGNAL(clicked()), this, SLOT(previousFigure()));

    QWidget::connect(clearButton, SIGNAL(clicked()), this, SLOT(clearWidget()));

    this->lineRadioButton->setChecked(true);

    this->createFigure();
}

void Widget::getInfo()
{
    centerText->setText("x " + QString::number(figures[index]->centerPoint.x(), 'd', 1) + "\n"
                        + "y " + QString::number(figures[index]->centerPoint.y(), 'd', 1));

    areaText->setText(QString::number(figures[index]->area, 'd', 1));
    perimeterText->setText(QString::number(figures[index]->perimeter, 'd', 1));
}

void Widget::clearWidget()
{
    disconnectButtons();
    figures.clear();
    index = -1;
    createFigure();
    update();
}

void Widget::createFigure()
{
    disconnectButtons();

    index = figures.size();

    Figure *newFigure;

    if (rectangleRadioButton->isChecked()) {
        newFigure = new Rectangle(this);
    } else if (squareRadioButton->isChecked()) {
        newFigure = new Square(this);
    } else if (starRadioButton->isChecked()) {
        newFigure = new Star(this);
        newFigure->numberOfThorns = starSpinBox->value();
    } else if (circleRadioButton->isChecked()) {
        newFigure = new Circle(this);
    } else if (hexagonRadioButton->isChecked()) {
        newFigure = new Hexagon(this);
    } else if (lineRadioButton->isChecked()) {
        newFigure = new Line(this);
    } else if (plusRadioButton->isChecked()) {
        newFigure = new Plus(this);
    } else if (rhombusRadioButton->isChecked()) {
        newFigure = new Rhombus(this);
    } else if (triangleRadioButton->isChecked()) {
        newFigure = new Triangle(this);
    }

    figures.emplace_back(newFigure);

    figures[index]->setFixedSize(1700, 1080);

    connectButtons();
}

void Widget::connectButtons()
{
    if (index >= 0 && index < figures.size() && figures[index]) {
        Figure::connect(rotateLeftButton,
                        SIGNAL(pressed()),
                        figures[index],
                        SLOT(startRotateLeft()));

        Figure::connect(rotateLeftButton,
                        SIGNAL(released()),
                        figures[index],
                        SLOT(stopRotateLeft()));

        Figure::connect(rotateRightButton,
                        SIGNAL(pressed()),
                        figures[index],
                        SLOT(startRotateRight()));

        Figure::connect(rotateRightButton,
                        SIGNAL(released()),
                        figures[index],
                        SLOT(stopRotateRight()));

        Figure::connect(increaseFigureSizeButton,
                        SIGNAL(pressed()),
                        figures[index],
                        SLOT(startIncrease()));

        Figure::connect(increaseFigureSizeButton,
                        SIGNAL(released()),
                        figures[index],
                        SLOT(stopIncrease()));

        Figure::connect(decreaseFigureSizeButton,
                        SIGNAL(pressed()),
                        figures[index],
                        SLOT(startDecrease()));

        Figure::connect(decreaseFigureSizeButton,
                        SIGNAL(released()),
                        figures[index],
                        SLOT(stopDecrease()));
    }
}

void Widget::disconnectButtons()
{
    if (index >= 0 && index < figures.size()) {
        Figure::disconnect(rotateLeftButton,
                           SIGNAL(pressed()),
                           figures[index],
                           SLOT(startRotateLeft()));

        Figure::disconnect(rotateLeftButton,
                           SIGNAL(released()),
                           figures[index],
                           SLOT(stopRotateLeft()));

        Figure::disconnect(rotateRightButton,
                           SIGNAL(pressed()),
                           figures[index],
                           SLOT(startRotateRight()));

        Figure::disconnect(rotateRightButton,
                           SIGNAL(released()),
                           figures[index],
                           SLOT(stopRotateRight()));

        Figure::disconnect(increaseFigureSizeButton,
                           SIGNAL(pressed()),
                           figures[index],
                           SLOT(startIncrease()));

        Figure::disconnect(increaseFigureSizeButton,
                           SIGNAL(released()),
                           figures[index],
                           SLOT(stopIncrease()));

        Figure::disconnect(decreaseFigureSizeButton,
                           SIGNAL(pressed()),
                           figures[index],
                           SLOT(startDecrease()));

        Figure::disconnect(decreaseFigureSizeButton,
                           SIGNAL(released()),
                           figures[index],
                           SLOT(stopDecrease()));
    }
}

void Widget::connectRadioButtons()
{
    Figure::connect(circleRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(hexagonRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(lineRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(plusRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(rectangleRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(rhombusRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(squareRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(starRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
    Figure::connect(triangleRadioButton, SIGNAL(clicked()), this, SLOT(createFigure()));
}

void Widget::nextFigure()
{
    if (index < figures.size() - 1) {
        disconnectButtons();
        index++;
        connectButtons();
    }
}

void Widget::previousFigure()
{
    if (index > 0) {
        disconnectButtons();
        index--;
        connectButtons();
    }
}

void Widget::updateWidget()
{
    update();
}

void Widget::changeNumberOfThorns()
{
    starRadioButton->setChecked(false);
    starRadioButton->setChecked(true);

    createFigure();

    figures[index]->update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (drawRadioButton->isChecked()) {
        this->figures[index]->drawClickEvent(event);
    } else if (moveRadioButton->isChecked()) {
        this->figures[index]->moveClick(event);
    }
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() <= 1700) {
        if (drawRadioButton->isChecked()) {
            this->figures[index]->drawMoveEvent(event);
        } else if (moveRadioButton->isChecked()) {
            this->figures[index]->startMove(event);
        }

        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //figures[0]->drawReleaseEvent(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    painter->begin(this);

    for (auto &figure : figures) {
        figure->drawPaintEvent(painter);
    }

    painter->end();
}
