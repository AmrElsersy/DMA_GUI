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
#include <QFile>
#include <math.h>

#include "Assembler/simulator.h"
#include <bits/stdc++.h>
using namespace std;

class Gui : public QWidget
{
    Q_OBJECT

private:
    const double MIN_TRANSFER_LOCATION = 32*6; // 4-IO devices each 32 location + 2*32 location for DMA
    const double MAX_TRANSFER_LOCATION = pow(2,16); // 64K Memory
    const double MAX_TRANSFER_BYTES = pow(2,14); // Max bytes to transfer

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
    void open_Slot();
//    void save_Slot();
    void file_Is_Selected(const QString);
};

#endif // GUI_H
