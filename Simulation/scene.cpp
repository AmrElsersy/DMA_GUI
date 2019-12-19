#include "scene.h"

myScene::myScene(QWidget *parent) : QGraphicsScene(MAX_TOP_LEFT_CORNER,1900,1000,parent)
{
    // MSH MOHEM
    // cursor for printing points coordinates
    this->cursor = new QGraphicsTextItem();
    this->cursor->setPos(600,-350);
    this->addItem(this->cursor);
    QString image_path = QCoreApplication::applicationDirPath()+"/../../DMA_GUI/DMA.png";
    this->image = QImage(image_path);

    this->index = 0;
    this->verilogPath = (QCoreApplication::applicationDirPath() + "/../../DMA_GUI/feedback.txt").toStdString();
//    this->verilogPath = (QCoreApplication::applicationDirPath() + "/../../DMA/feedback.txt").toStdString();

    this->initColors();
    this->setBackgroundBrush(QBrush(QColor(Qt::black)));

    this->myPainter = new Painter(this);
}
void myScene::updateStates(int direction)
{

    if(direction == 1) // right
    {
        if (this->index == this->max_clocks ) // if index is the last index in clocks vector
        {
            cout << "End of Execution" << endl;
            return;
        }
        this->index++;
    }
    else if (direction == -1) // backward
    {
        if(this->index == 0) // if it is the first state
        {
            cout << "First State cannot go backword" << endl;
            return;
        }
        this->index --;
    }

    this->myPainter->setCPU_Color(this->states[this->index].CPUColor);
    this->myPainter->setDMA_Color(this->states[this->index].DMAColor);
    this->myPainter->setIO1_Color(this->states[this->index].IO1Color);
    this->myPainter->setIO2_Color(this->states[this->index].IO2Color);
    this->myPainter->setRAM_Color(this->states[this->index].RAMColor);

    this->myPainter->setDataBusColor(this->states[this->index].DataBusColor);
    this->myPainter->setAddressBusColor(this->states[this->index].AddressBusColor);
    this->myPainter->setControlBusColor(this->states[this->index].ControlBusColor);

    this->myPainter->setHOLD_Color(this->states[this->index].Hold);
    this->myPainter->setHOLD_ACK_Color(this->states[this->index].HoldAck);

    this->myPainter->setDREQ_IO1_Color(this->states[this->index].DREQ_IO_1);
    this->myPainter->setDREQ_IO2_Color(this->states[this->index].DREQ_IO_2);
    this->myPainter->setDACK_IO1_Color(this->states[this->index].DACK_IO_1);
    this->myPainter->setDACK_IO2_Color(this->states[this->index].DACK_IO_2);

    this->myPainter->setDataBusValue(this->states[this->index].DataBusValue);
    this->myPainter->setAddressBusValue(this->states[this->index].AddressBusValue);
    this->myPainter->setControlValue(this->states[this->index].ControlValue);

    this->myPainter->setRAMTextColor(this->states[this->index].RamTextColor);
    this->myPainter->setKeyboardTextColor(this->states[this->index].KeyboardTextColor);
    this->myPainter->setPrinterTextColor(this->states[this->index].PrinterTextColor);

    this->myPainter->setPC(QString::number(this->states[this->index].PC));
    this->myPainter->setInstruction(this->states[this->index].Instruction);

}
void myScene::addNewItem(QGraphicsItem * item)
{
    this->addItem(item);
}
void myScene::INIT_Scene(vector<string> Code)
{
    // clear all
    this->index = 0;
    this->states.clear();
    this->initColors();    // initialize black color
    this->code.clear();

    // get instruction code
    for (uint i =0; i<Code.size();i++)
        this->code.push_back( Code[i] );
    this->code.push_back("xxxx");

    // read clocks description
    this->ReadClocks(); // read feedback.txt
    this->initStates();

    this->index = 0;
}
void myScene::initStates()
{
    for (uint i = 0 ; i < this->clocks_verilog.size() ; i++)
    {
        State state ;
        vector<string> data = split_string(clocks_verilog[i],",");

        int PC  = string_to_int(data[0]);
        QString Instruction = QString::fromStdString(this->code[PC]);

        state.PC = PC;
        state.Instruction = Instruction;


        int DataBusValue    = string_to_int(data[1]);
        int AddressBusValue = string_to_int(data[2]);
        int ControlValue    = string_to_int(data[3]);

        int Hold     = string_to_int(data[4]);
        int HoldAck  = string_to_int(data[5]);
        int DONT_NEED_BUS = string_to_int(data[6]);
        int DREQ_IO1 = string_to_int(data[7]);
        int DACK_IO1 = string_to_int(data[8]);
        int DREQ_IO2 = string_to_int(data[9]);
        int DACK_IO2 = string_to_int(data[10]);

        state.ControlValue    = QString::number(ControlValue);
        state.AddressBusValue = QString::number(AddressBusValue);
        state.DataBusValue    = QString::number(DataBusValue);

        // ============== Masters & AddressBus ================
        if(HoldAck == 1) // DMA
        {
            state.DMAColor = DMA_COLOR;
            state.CPUColor = CPU_COLOR;

            state.AddressBusColor = DMA_COLOR;
            state.Hold = DMA_COLOR;
            state.HoldAck = CPU_COLOR;
        }
        else if (HoldAck == 0) // CPU
        {
            // CPU NEEDS BUS and Uses it (CPU needs to remain colored if he execute instructions)
            state.CPUColor = CPU_COLOR;
            if(DONT_NEED_BUS == 0) // Needs it
            {
                state.AddressBusColor = CPU_COLOR;
                if(Hold == 1) // CPU && DMA Waiting
                {
                    state.DMAColor = DMA_COLOR;
                    state.Hold = DMA_COLOR;
                    state.HoldAck = INITIAL_COLOR;
                }
                else if (Hold == 0) // CPU && DMA is not Waiting
                {
                    state.DMAColor = INITIAL_COLOR;
                    state.Hold = INITIAL_COLOR;
                    state.HoldAck = INITIAL_COLOR;
                }
            }
            // Normal CPU Operations
            else if (DONT_NEED_BUS==1) // No one Uses the BUS
            {
                // state constructor assign everything to INITIAL_COLOR
                state.CPUColor = CPU_COLOR;
                // i guess it will not happen
                if (Hold == 1)
                {
                    state.DMAColor = DMA_COLOR;
                    state.Hold = DMA_COLOR;
                }
                else if (Hold == 0)
                {
                    // dont do anything (default initial colors)
                }
            }
        }
        // ============== DataBus & Control ================
        if (ControlValue == 0 )
        {
            state.ControlBusColor = INITIAL_COLOR;
        }
        else if (ControlValue ==1 )
        {
            if (HoldAck == 1)
            {
                state.DataBusColor = DMA_COLOR;
                state.ControlBusColor = DMA_COLOR;
            }
            else if (HoldAck == 0 && DONT_NEED_BUS == 0)
            {
                state.DataBusColor = CPU_COLOR;
                state.ControlBusColor = CPU_COLOR;
            }
            else
            {
                state.DataBusColor = INITIAL_COLOR;
            }

        }
        // ============== Slaves =================
        if     (AddressBusValue >= RAM_ADDRESS_START && AddressBusValue <= RAM_ADDRESS_END && ( HoldAck == 1 || DONT_NEED_BUS == 0 ))
        {
            state.RAMColor  = RAM_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = INITIAL_COLOR;

            if(ControlValue == 0) state.DataBusColor = RAM_COLOR;
            // Text Coloring
            if(HoldAck == 1) state.RamTextColor = DMA_COLOR;
            else if (DONT_NEED_BUS == 0) state.RamTextColor = CPU_COLOR;

        }
        else if(AddressBusValue >= IO1_ADDRESS_START && AddressBusValue <= IO1_ADDRESS_END && ( HoldAck == 1 || DONT_NEED_BUS == 0))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = IO1_COLOR;
            state.IO2Color = INITIAL_COLOR;

            if(ControlValue == 0) state.DataBusColor = IO1_COLOR;
            // Text Coloring
            if(HoldAck == 1) state.PrinterTextColor= RAM_COLOR;
            else if (DONT_NEED_BUS == 0) state.PrinterTextColor = CPU_COLOR;

        }
        else if(AddressBusValue >= IO2_ADDRESS_START && AddressBusValue <= IO2_ADDRESS_END && ( HoldAck == 1 || DONT_NEED_BUS == 0 ))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = IO2_COLOR;

            if(ControlValue == 0) state.DataBusColor = IO2_COLOR;
            // Text Coloring
            if(HoldAck == 1) state.KeyboardTextColor = DMA_COLOR;
            else if (DONT_NEED_BUS == 0) state.KeyboardTextColor = CPU_COLOR;

        }
        else if(AddressBusValue >= DMA_ADDRESS_START && AddressBusValue <= DMA_ADDRESS_END && ( HoldAck == 1 || DONT_NEED_BUS == 0 ))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = INITIAL_COLOR;
            state.DMAColor = DMA_COLOR;

            if(ControlValue == 0) state.DataBusColor = DMA_COLOR;
        }
        // ============== DREQ & DACK ============
        if(DREQ_IO1 == 1)
        {
            state.IO1Color = IO1_COLOR;
            state.DREQ_IO_1 = IO1_COLOR;
        }
        if(DREQ_IO2 == 1)
        {
            state.IO2Color = IO2_COLOR;
            state.DREQ_IO_2 = IO2_COLOR;
        }
        if(DACK_IO1 == 1) // printer
        {
            state.DMAColor = DMA_COLOR;
            state.DACK_IO_1 = DMA_COLOR;

            state.IO1Color = IO1_COLOR;
            if(ControlValue == 0 )
            {
                state.RAMColor = RAM_COLOR;
                state.DataBusColor = RAM_COLOR;
                state.PrinterTextColor = RAM_COLOR;
            }
        }
        if(DACK_IO2 == 1) // keyboard
        {
            state.DMAColor = DMA_COLOR;
            state.DACK_IO_2 = DMA_COLOR;

            state.IO2Color = IO2_COLOR;
            if(ControlValue == 1 )
            {
                state.DataBusColor = IO2_COLOR;
                state.RamTextColor = IO2_COLOR;
            }
        }
        // ============== Z & X ==================
        if (DataBusValue == XX || DataBusValue == ZZ) state.DataBusColor = INITIAL_COLOR;
        if (AddressBusValue == XX || AddressBusValue == ZZ) state.AddressBusColor = INITIAL_COLOR;
        if (ControlValue == XX || ControlValue == ZZ) state.DataBusColor = INITIAL_COLOR;
        this->states.push_back(state);
    }
}
void myScene::rightButton()
{
    if(this->timer->isActive())
        this->timer->stop();
    this->updateStates(1);
}
void myScene::leftButton()
{
    if(this->timer->isActive())
        this->timer->stop();
    this->updateStates(-1);
}
void myScene::playButton()
{
    if(!this->timer->isActive())
        this->timer->start();
    else
        this->timer->stop();
}
void myScene::continuous_play()
{
    if(this->index == this->max_clocks)
    {
        this->timer->stop();
        return;
    }
    this->updateStates(1);
}
void myScene::ReadClocks()
{
    this->clocks_verilog.clear();
    this->verilog_file.open(this->verilogPath);
    if(!this->verilog_file.is_open()) { cout << "file cannot open" << endl; }
    string s;
    while (getline(this->verilog_file,s))
    {
        if (s[0] == '/')
            continue;
        if (s == "" || s == " ")
            continue;
        for (int i =0 ; i < s.size();i ++)
            if(s[i]== ' ')
            {
                s.erase(i,1);
                i--;
            }
        this->clocks_verilog.push_back(s);
    }

    cout << "feedback.txt data:" << endl;
    for (uint i =0 ; i< this->clocks_verilog.size() ; i++ )
        cout << this->clocks_verilog[i] << "   " ;
    cout << endl;

    this->max_clocks = this->clocks_verilog.size();
    cout << "maxclocks = " << this->max_clocks << endl;
    this->verilog_file.close();
}
void myScene::initColors()
{
    State ray2;
    this->states.push_back(ray2);
}
void myScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        cout << endl;
}
vector<string> myScene :: split_string(string s,string splitter)
{
    vector<string> splitted;
    uint n = s.length();
    int pos = 0;
    int start = pos;
    while (pos != string::npos)
    {
        pos = s.find_first_of(splitter,pos+1);
        string splitted_string = s.substr(start,pos-start);
        splitted.push_back(splitted_string);
        start = pos+1;
    }

    return splitted;}

int myScene::string_to_int(string str)
{
    if (str == "X" || str == "x")
        return XX;
    else if (str == "Z" || str == "z")
        return ZZ;
    try {
        return stoi(str);
    } catch (...) {
        cout << "xxxx string_to_int not ray2" << endl;
        return XX;
    }
}
void myScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    QString s = QString::number(point.x()) + "," + QString :: number(point.y()) ;
    this->cursor->setPlainText(s);
//    cout << "x=" << point.x() << ",y=" << point.y() << endl;
    //    this->myPainter->checkPos(point.x(),point.y());

}
void myScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    QString s = QString::number(point.x()) + "," + QString :: number(point.y()) ;
    this->cursor->setPlainText(s);
    this->cursor->setPos(QPointF(point.x()+10,point.y())); // +10 for visualization only
    cout << point.x() << "," << point.y() << endl ;
}
void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    // string the point
    QString s = QString::number(point.x()) + "," + QString :: number(point.y()) ;
    this->cursor->setPlainText(s);
    // print the QGraphicText Item on the Scene
    //    this->cursor->setPos(QPointF(point.x()+10,point.y())); // +10 for visualization only
    cout << "\"" << point.x() << "," << point.y() << "\" ," ;
}
//void myScene::drawBackground(QPainter *painter, const QRectF &rect)
//{
//    painter->drawImage(QRectF(-900,-400,1600,900),this->image);
//}
void myScene::initButtons()
{
    QWidget* buttons_widget = new QWidget();
    QGridLayout* layout = new QGridLayout();
    buttons_widget->setStyleSheet("background-color:#035c70; border-radius:5px;");

    this->progressBar = new QProgressBar();
    this->progressBar->setRange(0,100);
    this->progressBar->setStyleSheet("QProgressBar{border: 2px solid grey;border-radius: 5px;text-align: center;background-color:rgb(15,15,15); margin-bottom:5px;}"
                                     "QProgressBar::chunk{background-color:#fff;};");//#55cc00
    this->progressBar->setValue(0);
    QPushButton* right_btn = new QPushButton("");
    QPushButton* left_btn = new QPushButton("");
    QPushButton* play_btn = new QPushButton("");


    right_btn->setIcon(QIcon(QCoreApplication::applicationDirPath() +"/../../MIPS_Simulator/icons\\right.png"));
    left_btn->setIcon(QIcon(QCoreApplication::applicationDirPath()  +"/../../MIPS_Simulator/icons\\left.png"));
    play_btn->setIcon(QIcon(QCoreApplication::applicationDirPath()  +"/../../MIPS_Simulator/icons\\play.png"));

    right_btn->setStyleSheet("border:0; background:#01333e; padding: 5px;");
    left_btn->setStyleSheet("border:0; background:#01333e; padding: 5px;");
    play_btn->setStyleSheet("border:0; background:#01333e; padding: 5px;");

    right_btn->setIconSize(QSize(30,30));
    left_btn->setIconSize(QSize(30,30));
    play_btn->setIconSize(QSize(30,30));

    connect(right_btn,SIGNAL(pressed()),this,SLOT(rightButton()));
    connect(left_btn,SIGNAL(pressed()),this,SLOT(leftButton()));
    connect(play_btn,SIGNAL(pressed()),this,SLOT(playButton()));

    layout->addWidget(this->progressBar,0,0,1,-1);
    layout->addWidget(left_btn,1,0);
    layout->addWidget(play_btn,1,1);
    layout->addWidget(right_btn,1,2);

    buttons_widget->setLayout(layout);
    this->addWidget(buttons_widget)->setPos(-920,420);
}
