#include <QApplication>
#include <QPushButton>


#include "car.h"
#include "mainwindow.h"
#include "door.h"
#include "light.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    //MainWindow *buttonLayer = new MainWindow(w);

    w->setFixedSize(1800, 1000);


    Car *car = new Car(w);

    Door *door = new Door(w);

    Light *light = new Light(w);

    car->setFixedSize(1800, 1000);

    door->setFixedSize(1800, 1000);

    light->setFixedSize(3600, 1000);

    //buttonLayer->setGeometry(1500, 800, 150, 150);

    QPushButton *pushRightButton = new QPushButton(">", w);
    QPushButton *pushLeftButton = new QPushButton("<", w);

    QPushButton *openTheDoors = new QPushButton("Open", w);
    QPushButton *closeTheDoors = new QPushButton("Close", w);

    QPushButton *turnLight = new QPushButton("Light", w);


    pushLeftButton->setGeometry(1400, 550, 50, 50);
    pushRightButton->setGeometry(1500, 550, 50, 50);

    openTheDoors->setGeometry(1400, 650, 150, 50);
    closeTheDoors->setGeometry(1400, 750, 150, 50);

    turnLight->setGeometry(1400, 850, 150, 50);


    MovingRectangle::connect(pushLeftButton, SIGNAL(pressed()), car, SLOT(moveLeft()));

    MovingRectangle::connect(pushLeftButton, SIGNAL(released()), car, SLOT(stopMoving()));

    MovingRectangle::connect(pushLeftButton, SIGNAL(pressed()), door, SLOT(moveLeft()));

    MovingRectangle::connect(pushLeftButton, SIGNAL(released()), door, SLOT(stopMoving()));

    MovingRectangle::connect(pushLeftButton, SIGNAL(pressed()), light, SLOT(moveLeft()));

    MovingRectangle::connect(pushLeftButton, SIGNAL(released()), light, SLOT(stopMoving()));


    Light::connect(turnLight, SIGNAL(clicked()), light, SLOT(switchLight()));


    Door::connect(openTheDoors, SIGNAL(clicked()), door, SLOT(openDoor()));

    Door::connect(closeTheDoors, SIGNAL(clicked()), door, SLOT(closeDoor()));


    MovingRectangle::connect(pushRightButton, SIGNAL(pressed()), car, SLOT(moveRight()));

    MovingRectangle::connect(pushRightButton, SIGNAL(released()), car, SLOT(stopMoving()));

    MovingRectangle::connect(pushRightButton, SIGNAL(pressed()), door, SLOT(moveRight()));

    MovingRectangle::connect(pushRightButton, SIGNAL(released()), door, SLOT(stopMoving()));

    MovingRectangle::connect(pushRightButton, SIGNAL(pressed()), light, SLOT(moveRight()));

    MovingRectangle::connect(pushRightButton, SIGNAL(released()), light, SLOT(stopMoving()));


    w->show();
    //buttonLayer->show();
    return a.exec();
}
