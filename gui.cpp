#include "GUI.h"

/************* Fucntion Prototypes ************/

Gui::Gui(QWidget *parent) : QWidget(parent){

    //Allocating objects
    dialogFile = new QFileDialog();
    simulator =new Simulator();
    memoryIO = new QPushButton("Memory - IO");
    IOMemory = new QPushButton("IO - Memory");
    MemtoMem = new QPushButton("Memory - Memory");
    open = new QPushButton("Open");
    programDMA = new QPushButton("Program DMA");

    simulate = new QPushButton("Simulate");

    source = new QLineEdit();
    destination = new QLineEdit();
    count = new QLineEdit();

    plainText = new QPlainTextEdit();

    systemGrid = new QGridLayout();

    errorMessage = new QMessageBox();

    toolBar = new QToolBar();

    //Alocating register objects
    BWRegister = new QLineEdit();
    BWCRegister = new QLineEdit();
    commandRegister = new QLineEdit();
    modeRegister = new QLineEdit();
    maskRegister = new QLineEdit();
    requestRegister = new QLineEdit();



    // Calling proper functions
    drawButtons();
    drawLineEdit();
    drawPlainText();
    connections();
    adjustButtons();
    adjustErrorBox();
    adjustPlainText();
    adjustLineEdit();
    handleToolBar();


    this->setLayout(this->systemGrid);

}

void Gui::drawButtons()
{
//    systemGrid->addWidget(open,0,1,1,1);

//    systemGrid->addWidget(memoryIO,2,4,1,3);
//    systemGrid->addWidget(IOMemory,3,4,1,3);
//    systemGrid->addWidget(MemtoMem,4,4,1,3);
//    systemGrid->addWidget(programDMA,5,4,1,3);
//    systemGrid->addWidget(simulate,6,4,1,3);
}

void Gui::drawLineEdit()
{
    source->setPlaceholderText("Source Field");
    destination->setPlaceholderText("Destination Field");
    count->setPlaceholderText("Count Field");

    BWRegister->setPlaceholderText("Base Word Register");
    BWCRegister->setPlaceholderText("Base Word Count Register");
    commandRegister->setPlaceholderText("Command Register");
    modeRegister->setPlaceholderText("Mode Register");
    maskRegister->setPlaceholderText("Mask Register");
    requestRegister->setPlaceholderText("Request Register");

    systemGrid->addWidget(source,6,1,1,1);
    systemGrid->addWidget(destination,6,2,1,1);
    systemGrid->addWidget(count,6,3,1,1);

    systemGrid->addWidget(BWRegister,0,4,1,1);
    systemGrid->addWidget(BWCRegister,0,5,1,1);
    systemGrid->addWidget(commandRegister,0,6,1,1);
    systemGrid->addWidget(modeRegister,1,4,1,1);
    systemGrid->addWidget(maskRegister,1,5,1,1);
    systemGrid->addWidget(requestRegister,1,6,1,1);

}

void Gui::drawPlainText()
{

    plainText->setPlaceholderText("Insert Assembly Instructions");
    plainText->setBackgroundVisible(true);
    systemGrid->addWidget(plainText,1,1,5,3);
}

void Gui::adjustButtons()
{
    // Adjusting button sizes
    memoryIO->setMinimumSize(100,100);
    IOMemory->setMinimumSize(100,100);
    MemtoMem->setMinimumSize(100,100);
    open->setMinimumSize(100,100);
    simulate->setMinimumSize(100,100);
    programDMA->setMinimumSize(100,100);

    memoryIO->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));
    IOMemory->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));
    MemtoMem->setIcon(QIcon("C:/Users/Ayman/Desktop/ButtonIcon.png"));

    memoryIO ->setStyleSheet(" QPushButton{ background-color:rgba(160, 160, 160, 0.849);border-radius:10%; font-size: 17px;} QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;} ");
    IOMemory ->setStyleSheet(" QPushButton{ background-color:rgba(160, 160, 160, 0.849);border-radius:10%; font-size: 17px;} QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;} ");
    MemtoMem->setStyleSheet(" QPushButton{ background-color:rgba(160, 160, 160, 0.849);border-radius:10%; font-size: 17px;} QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;} ");
    open->setStyleSheet(" QPushButton{ background-color:rgba(125, 219, 70, 0.904);border-radius:10%;font-size: 17px;} QPushButton:hover { background-color: rgba(32, 99, 30, 0.849); border-radius:10%; color:white;}  ");
    simulate->setStyleSheet(" QPushButton{background-color:rgba(143, 202, 236, 0.849);border-radius:10%;font-size: 23px;}QPushButton:hover { background-color:white;border-radius:10%; color:rgba(55, 192, 255, 0.849) ;border-width: 0.5px; border-style: solid; border-color: rgba(55, 192, 255, 0.849) ;} ");
    programDMA->setStyleSheet(" QPushButton{ background-color:rgba(160, 160, 160, 0.849);border-radius:10%; font-size: 17px;} QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;} ");

}

void Gui::adjustErrorBox()
{
//    QSize size;
//    size.setWidth(1000);
//    size.setHeight(1000);

    errorMessage->setWindowTitle("Informative Message");
    errorMessage->setIcon(QMessageBox::Warning);
    //errorMessage->setIconPixmap(*pixMap);
    errorMessage->setStyleSheet("background-color:rgba(224, 224, 224, 0.849); color:rgba(167, 0, 0, 0.849);");

}

void Gui::adjustPlainText()
{
    plainText->setStyleSheet("background-color:rgba(255, 254, 219, 0.849); font-size: 15px;");

}

void Gui::adjustLineEdit()
{
    source->setMinimumSize(100,100);
    destination->setMinimumSize(100,100);
    count->setMinimumSize(100,100);

    source->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    destination->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    count->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");

    BWRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    BWCRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    commandRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    modeRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    maskRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
    requestRegister->setStyleSheet("border-radius:5%;border-width: 0.5px; border-style: solid; border-color: gray ; background-color:rgba(255, 254, 219, 0.849);");
}

void Gui::handleToolBar()
{
    QIcon I_MemIO("C:/Users/Ayman/Desktop/Icons/floppy-disk.png"); QString S_MemIO("Memory IO");
    QIcon I_IOMem("C:/Users/Ayman/Desktop/Icons/printer.png"); QString S_IOMem("IO Memory");
    QIcon I_Mem_Mem("C:/Users/Ayman/Desktop/Icons/ram.png"); QString S_Mem_Mem("Memory Memory");
    QIcon I_ProgramDMA("C:/Users/Ayman/Desktop/Icons/ButtonIcon.png"); QString S_ProgramDMA("Program DMA");
    QIcon I_Simulate("C:/Users/Ayman/Desktop/Icons/round-play-button.png"); QString S_Simulate("Simulate");
    QIcon I_Open("C:/Users/Ayman/Desktop/Icons/open-folder-with-document.png"); QString S_Open("Open");

    toolBar->setIconSize(QSize(70,70));
    toolBar->setOrientation(Qt::Vertical);
    toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    toolBar->setFont(QFont("Helvetica [Cronyx]",9,65,0));

    // Adding actions to the toolbar
    toolBar->addAction(I_Open,S_Open);
    toolBar->addAction(I_Simulate,S_Simulate);
    toolBar->addAction(I_MemIO,S_MemIO);
    toolBar->addAction(I_IOMem,S_IOMem);
    toolBar->addAction(I_Mem_Mem,S_Mem_Mem);
    toolBar->addAction(I_ProgramDMA,S_ProgramDMA);



    systemGrid->addWidget(toolBar,0,0,1,1);



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

    /* Connecting open file siganls to their proper slots,
     * when file is selected; a path is returned to
     * file_selected_slot as a const string
     */
    connect(open,SIGNAL(clicked()),this,SLOT(open_Slot()));
    connect(dialogFile,SIGNAL(fileSelected(QString)),this,SLOT(file_Is_Selected(const QString)));

    //Program DMA signal when button is clicked
    connect(programDMA,SIGNAL(clicked()),this,SLOT(program_DMA_Slot()));

    // Toolbar signal
    connect(toolBar,SIGNAL(actionTriggered(QAction*)),this,SLOT(tool_Bar_Slot(QAction *)));



}

QGridLayout* Gui::getMainGrid()
{
    return systemGrid;
}

void Gui::memory_IO_Slot()
{

    plainText->appendPlainText("INIT_MEM_IO");

}

void Gui::io_Memory_Slot()
{
    plainText->appendPlainText("INIT_IO_MEM");
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
    else if (source->text().toInt()<MIN_TRANSFER_LOCATION ||
             destination->text().toInt()>MAX_TRANSFER_LOCATION)
    {
        //errorMessage->setInformativeText(source->text());
        errorMessage->setInformativeText("Please Specify Within Allowed Range \nSource :384 \n "
                                         "Destination: 65,536‬ ");
        errorMessage->show();
    }
    else if (count->text().toInt() <= 0 || count->text().toInt() >= MAX_TRANSFER_BYTES)
    {
        errorMessage->setInformativeText("Please Specify A Correct Count Value ");
        errorMessage->show();
    }
    else
    {
        plainText->appendPlainText("INIT_MEM_MEM " + (source->text()) + QString(" ,") + (destination->text())
                                   + QString(" ,")  + (count->text()));
    }
}

void Gui::simulate_Slot()
{
    this->simulator->clear();
    this->assemblyCode.clear();

    QStringList *list = new QStringList();

    QString *temp = new QString(plainText->toPlainText());
    list->append(temp->split("\n"));

    for (int i =0;i<list->size();i++)
    {
        assemblyCode.push_back(list->at(i).toStdString());
    }
    this->simulator->ASSEMBLY(assemblyCode);
    delete list;
    delete temp;
}

void Gui::open_Slot()
{
    dialogFile->setNameFilter("*.txt");
    dialogFile->setAcceptMode(QFileDialog::AcceptOpen);
    dialogFile->setViewMode(QFileDialog::List);
    dialogFile->setFileMode(QFileDialog::ExistingFile);
    dialogFile->show();
}

void Gui::program_DMA_Slot()
{
    if(BWRegister->isModified()!=1 || BWCRegister->isModified()!=1 ||
       commandRegister->isModified()!=1 || maskRegister->isModified()!=1 ||
       modeRegister->isModified()!=1 || requestRegister->isModified()!=1 )
    {
        errorMessage->setInformativeText("Please Specify All Registers");
        errorMessage->show();
    }
    else if (BWRegister->text().toInt() > MAX_REGISTER_VALUE ||
             BWCRegister->text().toInt() > MAX_REGISTER_VALUE ||
             commandRegister->text().toInt() > MAX_REGISTER_VALUE ||
             maskRegister->text().toInt() > MAX_REGISTER_VALUE ||
             modeRegister->text().toInt() > MAX_REGISTER_VALUE ||
             requestRegister->text().toInt() > MAX_REGISTER_VALUE)
    {
        errorMessage->setInformativeText("Please Specify Registers Value Within Range");
        errorMessage->show();
    }
    else
    {
        plainText->insertPlainText("INIT_PROGRAM_MEM \n");
        plainText->insertPlainText(BWRegister->text() +"\n");
        plainText->insertPlainText(BWCRegister->text() +"\n");
        plainText->insertPlainText(commandRegister->text() +"\n");
        plainText->insertPlainText(maskRegister->text() +"\n");
        plainText->insertPlainText(modeRegister->text() +"\n");
        plainText->insertPlainText(requestRegister->text() +"\n");
    }
}

void Gui::file_Is_Selected(const QString processFile)
{
    QStringList list;
    QFile assemblyFile(processFile);
    assemblyFile.open(QIODevice::ReadOnly);

    while(!(assemblyFile.atEnd()))
    {
        list.push_back(assemblyFile.readLine());
    }
    short i =0;
    while(i < list.size())
    {
       plainText->insertPlainText(list.at(i));
       i++;
    }
    assemblyFile.close();
}

void Gui::tool_Bar_Slot(QAction *actionTrig)
{
    if(actionTrig->text() == "Open")
    {
        dialogFile->setNameFilter("*.txt");
        dialogFile->setAcceptMode(QFileDialog::AcceptOpen);
        dialogFile->setViewMode(QFileDialog::List);
        dialogFile->setFileMode(QFileDialog::ExistingFile);
        dialogFile->show();

    }
    else if (actionTrig->text() == "Simulate")
    {
        this->simulator->clear();
        this->assemblyCode.clear();

        QStringList *list = new QStringList();

        QString *temp = new QString(plainText->toPlainText());
        list->append(temp->split("\n"));

        for (int i =0;i<list->size();i++)
        {
            assemblyCode.push_back(list->at(i).toStdString());
        }
        this->simulator->ASSEMBLY(assemblyCode);
        delete list;
        delete temp;
    }
    else if (actionTrig->text() == "Memory IO")
    {
        plainText->appendPlainText("INIT_MEM_IO");
    }
    else if (actionTrig->text() == "IO Memory")
    {
        plainText->appendPlainText("INIT_IO_MEM");
    }
    else if (actionTrig->text() == "Memory Memory")
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
        else if (source->text().toInt()<MIN_TRANSFER_LOCATION ||
                 destination->text().toInt()>MAX_TRANSFER_LOCATION)
        {
            //errorMessage->setInformativeText(source->text());
            errorMessage->setInformativeText("Please Specify Within Allowed Range \nSource :384 \n "
                                             "Destination: 65,536‬ ");
            errorMessage->show();
        }
        else if (count->text().toInt() <= 0 || count->text().toInt() >= MAX_TRANSFER_BYTES)
        {
            errorMessage->setInformativeText("Please Specify A Correct Count Value ");
            errorMessage->show();
        }
        else
        {
            plainText->appendPlainText("INIT_MEM_MEM " + (source->text()) + QString(" ,") + (destination->text())
                                       + QString(" ,")  + (count->text()));
        }
    }
    else if (actionTrig->text() == "Program DMA")
    {
        if(BWRegister->isModified()!=1 || BWCRegister->isModified()!=1 ||
           commandRegister->isModified()!=1 || maskRegister->isModified()!=1 ||
           modeRegister->isModified()!=1 || requestRegister->isModified()!=1 )
        {
            errorMessage->setInformativeText("Please Specify All Registers");
            errorMessage->show();
        }
        else if (BWRegister->text().toInt() > MAX_REGISTER_VALUE ||
                 BWCRegister->text().toInt() > MAX_REGISTER_VALUE ||
                 commandRegister->text().toInt() > MAX_REGISTER_VALUE ||
                 maskRegister->text().toInt() > MAX_REGISTER_VALUE ||
                 modeRegister->text().toInt() > MAX_REGISTER_VALUE ||
                 requestRegister->text().toInt() > MAX_REGISTER_VALUE)
        {
            errorMessage->setInformativeText("Please Specify Registers Value Within Range");
            errorMessage->show();
        }
        else
        {
            plainText->insertPlainText("\nINIT_PROGRAM_MEM \n");
            plainText->insertPlainText(BWRegister->text() +"\n");
            plainText->insertPlainText(BWCRegister->text() +"\n");
            plainText->insertPlainText(commandRegister->text() +"\n");
            plainText->insertPlainText(maskRegister->text() +"\n");
            plainText->insertPlainText(modeRegister->text() +"\n");
            plainText->insertPlainText(requestRegister->text() +"\n");
        }
    }
    else
    {

    }
}











