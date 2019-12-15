#include "gui.h"

/************* Fucntion Prototypes ************/

Gui::Gui(QWidget *parent) : QWidget(parent){

    //Allocating objects
    memoryIO = new QPushButton("Memory - IO");
    IOMemory = new QPushButton("IO - Memory");
    MemtoMem = new QPushButton("Memory - Memory");
    open = new QPushButton("Open");
    save = new QPushButton("Save");

    simulate = new QPushButton("Simulate");

    source = new QLineEdit();
    destination = new QLineEdit();
    count = new QLineEdit();

    plainText = new QPlainTextEdit();

    systemGrid = new QGridLayout();

    errorMessage = new QMessageBox();

    assemblyCode = new QVector<QString>();

    // Calling proper functions
    drawButtons();
    drawLineEdit();
    drawPlainText();
    connections();

}

void Gui::drawButtons()
{

    // Adjusting button sizes

    memoryIO->setMinimumSize(100,100);
    IOMemory->setMinimumSize(100,100);
    MemtoMem->setMinimumSize(100,100);
    open->setMinimumSize(100,100);
    save->setMinimumSize(100,100);
    simulate->setMinimumSize(200,200);

    memoryIO->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));
    IOMemory->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));
    MemtoMem->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));

    systemGrid->addWidget(open,0,1,1,1);
    systemGrid->addWidget(save,0,2,1,1);

    systemGrid->addWidget(memoryIO,2,4,1,3);
    systemGrid->addWidget(IOMemory,3,4,1,3);
    systemGrid->addWidget(MemtoMem,4,4,1,3);
    systemGrid->addWidget(simulate,6,4,1,3);

    //systemGrid->setContentsMargins(7,7,7,7);


}

void Gui::drawLineEdit()
{

    source->setPlaceholderText("Source Field");
    destination->setPlaceholderText("Destination Field");
    count->setPlaceholderText("Count Field");

    source->setMinimumSize(80,100);
    destination->setMinimumSize(80,100);
    count->setMinimumSize(80,100);

    systemGrid->addWidget(source,6,1,1,1);
    systemGrid->addWidget(destination,6,2,1,1);
    systemGrid->addWidget(count,6,3,1,1);


}

void Gui::drawPlainText()
{

    plainText->setPlaceholderText("Insert Assembly Instructions");
    plainText->setBackgroundVisible(true);
    systemGrid->addWidget(plainText,1,1,5,3);
}

void Gui::connections()
{

    // Connecting signals to proper slots

    // Connecting Memory to I/O slot to a button click signal
    connect(memoryIO,SIGNAL(clicked()),this,SLOT(memory_IO_Slot()));

    // Connecting I/O to memory slot to a button click signal
    connect(IOMemory,SIGNAL(clicked()),this,SLOT(io_Memory_Slot()));

    // Connecting memory to memory slot to a button click signal
    connect(MemtoMem,SIGNAL(clicked()),this,SLOT(memory_Memory_Slot()));

    /* Connecting simulate slot to a button click & returning vector
     * of strings which represents my assembly code
     */
    connect(simulate,SIGNAL(clicked()),this,SLOT(simulate_Slot()));



}

QGridLayout* Gui::getMainGrid()
{
    return systemGrid;
}

void Gui::memory_IO_Slot()
{

    plainText->appendPlainText("init mem write");

}

void Gui::io_Memory_Slot()
{
    plainText->appendPlainText("init mem read");
}

void Gui::memory_Memory_Slot()
{
    // Checking if source, destination & count are specified or not
    if(source->isModified() != 1)
    {
        errorMessage->setInformativeText("Please Specify Source Field");
        errorMessage->show();
    }
    else if(destination->isModified() != 1)
    {
       errorMessage->setInformativeText("Please Specify Destination Field");
       errorMessage->show();
    }

    else if(count->isModified() != 1)
    {
        errorMessage->setInformativeText("Please Specify Count Field");
        errorMessage->show();
    }
    /* Checking if source, destination & count within available transfer range or not
     * Assuming our range from location 64 to 1023 & count ranges from 1 to 512
     */
    else if (source->text().toInt()<64 ||
             destination->text().toInt()>1023)
    {
        //errorMessage->setInformativeText(source->text());
        errorMessage->setInformativeText("Please Specify Within Range (64-1023) ");
        errorMessage->show();
    }
    else if (count->text().toInt() <= 0)
    {
        errorMessage->setInformativeText("Please Specify A Correct Count Value ");
        errorMessage->show();
    }
    else
    {
        plainText->appendPlainText("init mem mem");
    }
}

void Gui::simulate_Slot()
{
    /*
     *
     *
     */
    QStringList *list = new QStringList();

    QString *temp = new QString(plainText->toPlainText());
    list->append(temp->split("\n"));

    for (int i =0;i<list->size();i++)
    {
        assemblyCode->push_back(list->at(i));

    }
    delete list;
    delete temp;
}












