#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent)
{
    this->gui = new Gui();
    this->setCentralWidget(this->gui);
    this->view = new View();
}

void MainWindow::start_simulation()
{
    this->view->my_scene->INIT_Scene({});
    this->view->show();
}
