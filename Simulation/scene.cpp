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
//        QString Instruction = QString::fromStdString(this->code[PC]);

        state.PC = PC;
        state.Instruction = "ray2";


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

        state.ControlValue    = QString::fromStdString(to_string(ControlValue));
        state.AddressBusValue = QString::fromStdString(to_string(AddressBusValue));
        state.DataBusValue    = QString::fromStdString(to_string(DataBusValue));

        if(HoldAck == 1) // DMA
        {
            state.DMAColor = DMA_COLOR;
            state.CPUColor = CPU_COLOR;

            state.AddressBusColor = DMA_COLOR;
            state.Hold = DMA_COLOR;
            state.HoldAck = CPU_COLOR;
        }
        else if (!HoldAck) // CPU
        {
            // CPU NEEDS BUS and Uses it
            state.CPUColor = CPU_COLOR;
            if(!DONT_NEED_BUS)
            {
                state.AddressBusColor = CPU_COLOR;
                if(Hold == 1) // CPU && DMA Waiting
                {
                    state.DMAColor = DMA_COLOR;
                    state.Hold = DMA_COLOR;
                    state.HoldAck = INITIAL_COLOR;
                }
                else if (!Hold) // CPU && DMA is not Waiting
                {
                    state.Hold = INITIAL_COLOR;
                    state.HoldAck = INITIAL_COLOR;
                }
            }

            else if (DONT_NEED_BUS==1) // No one Uses the BUS
            {
                // state constructor assign everything to INITIAL_COLOR
                state.CPUColor = CPU_COLOR;
            }
        }

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
            else if (HoldAck == 0 && !DONT_NEED_BUS)
            {
                state.DataBusColor = CPU_COLOR;
                state.ControlBusColor = CPU_COLOR;
            }
            else
            {
                state.DataBusColor = INITIAL_COLOR;
            }

        }

        if     (AddressBusValue >= RAM_ADDRESS_START && AddressBusValue <= RAM_ADDRESS_END && ( HoldAck || !DONT_NEED_BUS ))
        {
            state.RAMColor  = RAM_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = INITIAL_COLOR;

            if(ControlValue == 0) state.DataBusColor = RAM_COLOR;
        }
        else if(AddressBusValue >= IO1_ADDRESS_START && AddressBusValue <= IO1_ADDRESS_END && ( HoldAck || !DONT_NEED_BUS ))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = IO1_COLOR;
            state.IO2Color = INITIAL_COLOR;

            if(ControlValue == 0) state.DataBusColor = IO1_COLOR;
        }
        else if(AddressBusValue >= IO2_ADDRESS_START && AddressBusValue <= IO2_ADDRESS_END && ( HoldAck || !DONT_NEED_BUS ))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = IO2_COLOR;

            if(ControlValue == 0) state.DataBusColor = IO2_COLOR;
        }
        else if(AddressBusValue >= DMA_ADDRESS_START && AddressBusValue <= DMA_ADDRESS_END && ( HoldAck || !DONT_NEED_BUS ))
        {
            state.RAMColor = INITIAL_COLOR;
            state.IO1Color = INITIAL_COLOR;
            state.IO2Color = INITIAL_COLOR;
            state.DMAColor = DMA_COLOR;

            if(ControlValue == 0) state.DataBusColor = DMA_COLOR;
        }

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
    this->verilog_file.open(this->verilogPath);
    if(!this->verilog_file.is_open()) { cout << "file cannot open" << endl; }
    string s;
    while (getline(this->verilog_file,s))
    {
        if (s == "" || s == " ")
            continue;
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
