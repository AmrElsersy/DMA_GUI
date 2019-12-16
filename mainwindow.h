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


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Gui* gui;
public:
    MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};
#endif // MAINWINDOW_H
