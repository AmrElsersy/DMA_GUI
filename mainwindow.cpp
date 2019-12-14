#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent)
{
//    // ************ USE OF SIMULATOR *******************
//    this->simulator =new Simulator();
//    vector<string> ins={"addi $s0,$s0,1",
//                       "add $s0,$s0,$s4",
//                       "LW $s15,1000",
//                       "addi $s0,$s0,1"};
//    this->simulator->ASSEMBLY(ins);
//    // **************************************************


    QWidget* mainWidget = new QWidget();
//    QWidget* widget1 = new QWidget();
//    QWidget* widget2 = new QWidget();
//    QWidget* widget3 = new QWidget();
//    QWidget* widget4 = new QWidget();

//    widget1->setStyleSheet("background-color:red;");
//    widget2->setStyleSheet("background-color:black;");
//    widget3->setStyleSheet("background-color:yellow;");
//    widget4->setStyleSheet("background-color:blue;");


    lineEdit = new QLineEdit();
    button = new QPushButton("Button");

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(lineEdit,0,0);
    grid->addWidget(button,0,1);

    mainWidget->setLayout(grid);
    this->setCentralWidget(mainWidget);
}

void MainWindow::slot_for_button()
{

}
