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
#include <QSize>
#include <QToolBar>
#include <QAction>
#include <QFont>

#include "Assembler/simulator.h"
#include <bits/stdc++.h>
using namespace std;

class Gui : public QWidget
{
    Q_OBJECT

private:
    const long MIN_TRANSFER_LOCATION = 32*6; // 4-IO devices each 32 location + 2*32 location for DMA
    const long MAX_TRANSFER_LOCATION = pow(2,16); // 64K Memory
    const long MAX_TRANSFER_BYTES = pow(2,14); // Max bytes to transfer
    const long MAX_REGISTER_VALUE = pow(2,16);

    Simulator* simulator;

    //GUI push buttons
    QPushButton *memoryIO;

    QPushButton *IOMemory;
    QPushButton *MemtoMem;
    QPushButton *simulate;
    QPushButton *open;
    QPushButton *programDMA;


    //GUI text editor
    QPlainTextEdit *plainText;

    //GUI text lines
    QLineEdit *source;
    QLineEdit *destination;
    QLineEdit *count;

    //GUI text lines for DMA registers
    QLineEdit *BWRegister;
    QLineEdit *BWCRegister;
    QLineEdit *commandRegister;
    QLineEdit *modeRegister;
    QLineEdit *maskRegister;
    QLineEdit *requestRegister;

    //GUI grid layout
    QGridLayout *systemGrid;

    //GUI triggering message when error occurs
    QMessageBox *errorMessage;

    QFileDialog *dialogFile;

    QToolBar *toolBar;

    // Vector of strings which holds program assembly code
    vector<string> assemblyCode;


public:
    explicit Gui(QWidget *parent = nullptr);

    void drawButtons();
    void drawLineEdit();
    void drawPlainText();
    void adjustButtons();
    void adjustErrorBox();
    void adjustPlainText();
    void adjustLineEdit();
    void adjustGrid();
    void handleToolBar();

    void connections();


signals:

public slots:
    void memory_IO_Slot();
    void io_Memory_Slot();
    void memory_Memory_Slot();
    void simulate_Slot();
    void open_Slot();
    void program_DMA_Slot();
    void file_Is_Selected(const QString);

    void tool_Bar_Slot(QAction*);

};

#endif // GUI_H
