#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Assembler/simulator.h"

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Simulator* simulator;

    QPushButton* button;
    QLineEdit* lineEdit;

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void triger_event();
public slots:
    void slot_for_button();
};
#endif // MAINWINDOW_H
