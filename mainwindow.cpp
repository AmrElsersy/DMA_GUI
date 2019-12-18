#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent)
{
    this->gui = new Gui();
    this->view = new View();
    this->setCentralWidget(this->gui);
    //this->setCentralWidget(this->view);
    //this->view->show();
}
