#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QMessageBox>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include "GUI.h"
#include "Simulation/view.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    View* view;
    Gui* gui;
public:
    MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void start_simulation(vector<string>);
};
#endif // MAINWINDOW_H
