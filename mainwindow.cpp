#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent)
{
    this->gui = new Gui();
    this->setCentralWidget(this->gui);
}
