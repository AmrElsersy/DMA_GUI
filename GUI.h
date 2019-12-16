#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QIcon>
#include <QString>
#include <QVector>
#include <QStringList>

#include "Assembler/simulator.h"
#include <bits/stdc++.h>
using namespace std;

class Gui : public QWidget
{
    Q_OBJECT

private:
    const short MIN_TRANSFER_LOCATION = 64;
    const short MAX_TRANSFER_LOCATION = 1023;
    const short MAX_TRANSFER_BYTES = 512;

    Simulator* simulator;
    //GUI push buttons
    QPushButton *memoryIO;

    QPushButton *IOMemory;
    QPushButton *MemtoMem;
    QPushButton *simulate;
    QPushButton *open;
    QPushButton *save;

    //GUI text editor
    QPlainTextEdit *plainText;

    //GUI text lines
    QLineEdit *source;
    QLineEdit *destination;
    QLineEdit *count;

    //GUI grid layout
    QGridLayout *systemGrid;

    //GUI triggering message when error occurs
    QMessageBox *errorMessage;

    QFileDialog *dialogFile;

    // Vector of strings which holds program assembly code
    vector<string> assemblyCode;


public:
    explicit Gui(QWidget *parent = nullptr);

    void drawButtons();
    void drawLineEdit();
    void drawPlainText();


    void connections();
    QGridLayout* getMainGrid();


signals:

public slots:
    void memory_IO_Slot();
    void io_Memory_Slot();
    void memory_Memory_Slot();
    void simulate_Slot();

//    void open_Slot();
//    void save_Slot();

};

#endif // GUI_H
