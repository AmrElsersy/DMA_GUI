#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent)
{
    this->gui = new Gui();
    this->setCentralWidget(this->gui);
    this->view = new View();
    connect(this->gui->simulator,SIGNAL(init_simulation(vector<string>)),this,SLOT(start_simulation(vector<string>)));
    this->setStyleSheet("background-color:black; color:white;");
}

void MainWindow::start_simulation(vector<string> code)
{
    this->view->my_scene->INIT_Scene(code);
    this->view->show();
}
