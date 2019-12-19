#include "painter.h"

void Painter::init_Modules()
{
    // CPU
    this->CPU = new QGraphicsRectItem(-772,-327,168,330);
    this->CPU->setPen(this->pen);
    emit addnewItem(this->CPU);
    // DMA
    this->DMA = new QGraphicsRectItem(-394,266,322,163);
    this->DMA->setPen(this->pen);
    emit addnewItem(this->DMA);
    // RAM
    this->RAM  = new QGraphicsRectItem(289,-326,170,270);
    this->RAM->setPen(this->pen);
    emit addnewItem(this->RAM);
    // IO 1
    this->IO_1 = new QGraphicsRectItem(290,-22,170,140);
    this->IO_1->setPen(this->pen);
    emit addnewItem(this->IO_1);
    // IO 2
    this->IO_2 = new QGraphicsRectItem(290,176,170,120);
    this->IO_2->setPen(this->pen);
    emit addnewItem(this->IO_2);
}
void Painter::init_BUSs()
{
    // Address_Bus
    this->Address_Bus["CPU_RAM_1_Down"] = newPath({"-603,-198" ,"-309,-198" });
    this->Address_Bus["CPU_RAM_2_Down"] = newPath({"-290,-198" ,"51,-198"});
    this->Address_Bus["CPU_RAM_3_Down"] = newPath({"70,-198" ,"288,-198" });
    this->Address_Bus["CPU_RAM_1_Up1"] = newPath({"-605,-215" ,"-310,-215"});
    this->Address_Bus["CPU_RAM_1_Up2"] = newPath({"-291,-215" ,"50,-215"});
    this->Address_Bus["CPU_RAM_1_Up3"] = newPath({"69,-215" ,"287,-215"});
    this->Address_Bus["Address_DMA_Left"] = newPath({"-247,-199" ,"-247,263"});
    this->Address_Bus["Address_DMA_Right"] = newPath({"-228,-199" ,"-228,264"});
    this->Address_Bus["Address_IO_2_Left"] = newPath({"107,-197" ,"107,240" ,"288,240"});
    this->Address_Bus["Address_IO_2_Right1"] = newPath({"125,-198" ,"125,42"});
    this->Address_Bus["Address_IO_2_Right2"] = newPath({"125,57" ,"125,224" ,"289,224"});
    this->Address_Bus["Address_IO_1_Down"] = newPath({"127,43" ,"287,43"});
    this->Address_Bus["Address_IO_1_Up"] = newPath({"126,57" ,"289,57"});

    // Control_Bus
    this->Control["CPU_RAM_Control"] = newPath({"-604,-138" ,"288,-138"});
    this->Control["Control_DMA"] = newPath({"-152,-137" ,"-152,264"});
    this->Control["Control_IO2"] = newPath({"200,-139" ,"200,195" ,"288,195"});
    this->Control["Control_IO1"] = newPath({"203,12" ,"289,12"});

    // Data_Bus
    this->Data_Bus["CPU_RAM_Up"] = newPath({"-603,-304" ,"287,-304" });
    this->Data_Bus["CPU_RAM_Down"] = newPath({"-603,-290" ,"287,-290" });
    this->Data_Bus["Data_DMA_Left"] = newPath({ "-308,-292" ,"-308,264"});
    this->Data_Bus["Data_DMA_Right"] = newPath({ "-293,-289" ,"-293,264" });
    this->Data_Bus["Data_IO2_Down"] = newPath({"51,-289" ,"51,272" ,"288,272" });
    this->Data_Bus["Data_IO2_Up"] = newPath({"67,-290","67,256" ,"289,256" });
    this->Data_Bus["Data_IO1_Up1"] = newPath({ "68,88" ,"107,88"});
    this->Data_Bus["Data_IO1_Up2"] = newPath({ "126,88" ,"290,88" });
    this->Data_Bus["Data_IO1_Down1"] = newPath({ "68,100" ,"107,100"});
    this->Data_Bus["Data_IO1_Down2"] = newPath({ "126,100" ,"290,100" });

    // Other Paths
    this->Paths["DREQ_IO1"] = newPath({"461,45" ,"571,45" ,"571,412" ,"-72,412" });
    this->Paths["DACK_IO1"] = newPath({"460,67" ,"533,67" ,"533,390" ,"-70,390" });
    this->Paths["DREQ_IO2"] = newPath({"331,295" ,"331,325" ,"-70,325" });
    this->Paths["DACK_IO2"] = newPath({"373,299" ,"373,348" ,"-70,348" });
    this->Paths["IOR"] = newPath({"-623,3" ,"-623,306" ,"-397,306" });
    this->Paths["IOW"] = newPath({"-640,5" ,"-640,322" ,"-396,322" });
    this->Paths["HOLD"] = newPath({"-698,7" ,"-698,370" ,"-397,370" });
    this->Paths["HOLD_ACK"] = newPath({ "-716,6" ,"-716,395" ,"-397,395"});
}
void Painter::init_Text()
{
    //=========== Modules =================
    this->Text["CPU"] = newText(-712,-175,"CPU");
    this->Text["DMA"] = newText(-260,332,"DMA");
    this->Text["Keyboard"] = newText(322,220,"Keyboard");
    this->Text["Printer"] = newText(320,25,"Printer");
    this->Text["RAM"] = newText(345,-208,"RAM");
    // ========== BUS ======================
    this->Text["Data_Bus"] = newText(-570,-335,"Data Bus",true);
    this->Text["Address_Bus"] = newText(-520,-253,"Address Bus",true);
    this->Text["Control"] = newText(-450,-170,"MEMR/W",true);
    // ========== Paths ====================
    this->Text["DREQ_IO2"] = newText(-35,300,"DREQ",true);
    this->Text["DACK_IO2"] = newText(-35,325,"DACK",true);
    this->Text["DREQ_IO1"] = newText(-28,370,"DREQ",true);
    this->Text["DACK_IO1"] = newText(-28,390,"DACK",true);
    this->Text["HOLD"] = newText(-510,345,"HOLD",true);
    this->Text["HOLD_ACK"] = newText(-510,370,"HLDA",true);
    this->Text["IOW"] = newText(-590,280,"IOW",true);
    this->Text["IOR"] = newText(-590,320,"IOR",true);

    // ============ Values ==================
    this->Text["Address"]  = newText(700,400,"Address=",true);
    this->Text["Data"]  = newText(700,450,"Data=",true);
    this->Text["Control"] = newText(700,500,"Control=",true);
}
Painter::Painter(QObject *parent) : QObject(parent)
{
    this->color = QColor(Qt::black);
    this->pen = QPen(QBrush(INITIAL_COLOR,Qt::SolidPattern),5);
    connect(this,SIGNAL(addnewItem(QGraphicsItem*)),parent,SLOT(addNewItem(QGraphicsItem*)));

    init_Modules();
    init_BUSs();
    init_Text();
}
void Painter::setDataBusColor(QColor clr)
{
    for(auto i = this->Data_Bus.begin() ; i != this->Data_Bus.end() ; i++)
        i->second->setColor(clr);
}
void Painter::setAddressBusColor(QColor clr)
{
    for(auto i = this->Address_Bus.begin() ; i != this->Address_Bus.end() ; i++)
        i->second->setColor(clr);
}
void Painter::setControlBusColor(QColor clr)
{
    for(auto i = this->Control.begin() ; i != this->Control.end() ; i++)
        i->second->setColor(clr);
}

void Painter::setHOLD_Color(QColor clr)
{
    this->Paths["HOLD"]->setColor(clr);
}
void Painter::setHOLD_ACK_Color(QColor clr)
{
    this->Paths["HOLD_ACK"]->setColor(clr);
}
void Painter::setDREQ_IO1_Color(QColor clr)
{
    this->Paths["DREQ_IO1"]->setColor(clr);
}
void Painter::setDACK_IO1_Color(QColor clr)
{
    this->Paths["DACK_IO1"]->setColor(clr);
}
void Painter::setDREQ_IO2_Color(QColor clr)
{
    this->Paths["DREQ_IO2"]->setColor(clr);
}
void Painter::setDACK_IO2_Color(QColor clr)
{
    this->Paths["DACK_IO2"]->setColor(clr);
}
void Painter::setCPU_Color(QColor clr)
{
    this->pen.setColor(clr);
    this->CPU->setPen(this->pen);
}
void Painter::setDMA_Color(QColor clr)
{
    this->pen.setColor(clr);
    this->DMA->setPen(this->pen);
}

void Painter::setRAM_Color(QColor clr)
{
    this->pen.setColor(clr);
    this->RAM->setPen(this->pen);
}

void Painter::setIO1_Color(QColor clr)
{
    this->pen.setColor(clr);
    this->IO_1->setPen(this->pen);
}

void Painter::setIO2_Color(QColor clr)
{
    this->pen.setColor(clr);
    this->IO_2->setPen(this->pen);
}

void Painter::setControlValue(QString value)
{
    this->Text["Control"]->setPlainText("Control=" + value);
}

void Painter::setDataBusValue(QString value)
{
    this->Text["Data"]->setPlainText("Data=" + value);
}

void Painter::setAddressBusValue(QString value)
{
    this->Text["Address"]->setPlainText("Address=" + value);
}

void Painter::checkPos(int x, int y)
{
    int X = this->CPU->scenePos().toPoint().rx();    int Y = this->CPU->scenePos().ry();
    int w = this->CPU->rect().width();  int h = this->CPU->rect().height();
    cout << "Pos=" << X << "," << Y << endl;
    if (x>=X && y >= Y && x <= X+w && y <= Y+h)
        this->CPU->setBrush(QBrush(Qt::white));
}
Path *Painter::newPath(vector<string> points)
{
    Path* temp = new Path(points);
    temp->setColor(QColor(INITIAL_COLOR));
    emit addnewItem(temp);
    return temp;
}
QGraphicsTextItem* Painter::newText(int x , int y, QString Text,bool small_text )
{
    QGraphicsTextItem* temp = new QGraphicsTextItem(Text);
    temp->setPos(x,y);
    if(small_text)
        temp->setFont(QFont("Arial",SMALL_FONT_SIZE,QFont::Bold));
    else
        temp->setFont(QFont("Arial",FONT_SIZE,QFont::Bold));
    temp->setDefaultTextColor(TEXT_COLOR);
    emit addnewItem(temp);
    return temp;
}
