#include "view.h"

View :: View(QWidget* parent) : QGraphicsView(parent)
{
    this->setFixedSize(QSize(1920,1000));
    this->my_scene= new myScene();
    this->setScene(this->my_scene);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key()== Qt::Key_D)
        this->my_scene->updateStates(1);
    else if (event->key() == Qt::Key_A)
        this->my_scene->updateStates(-1);
    else if (event->key() == Qt::Key_Space)
        cout << endl;
}
