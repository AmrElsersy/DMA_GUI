#include "scene.h"

myScene::myScene(QWidget *parent) : QGraphicsScene(MAX_TOP_LEFT_CORNER,1900,1000,parent)
{
    QString image_path = QCoreApplication::applicationDirPath()+"/../../DMA_GUI/DMA.png";
    this->image = QImage(image_path);

    // cursor for printing points coordinates
    this->cursor = new QGraphicsTextItem();
    this->cursor->setPos(600,-350);
    this->addItem(this->cursor);
    // MIPS Pipeline Image

    this->initText();
    this->initColors();

    this->index = 0;

    this->setBackgroundBrush(QBrush(QColor(Qt::black)));
//    this->initButtons();

}

void myScene::updateColorsClocks(int direction)
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


    this->progressBar->setValue(this->index);
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
    this->ReadClocks(); // read pc.txt
    this->initStates();

    this->index = 0;
    this->progressBar->setRange(0,this->max_clocks-2);
}


void myScene::initStates()
{
    for (uint i = 0 ; i < this->clocks_verilog.size() ; i++)
    {
        State state ;
        vector<string> data = split_string(clocks_verilog[i]," ");
        int PC  = stoi(data[0]);
        QString Instruction = QString::fromStdString(data[1]);
        int ControlValue = stoi(data[2]);
        int AddressBusValue =stoi(data[3]);
        int DataBusValue =stoi(data[4]);
        int Hold = stoi(data[5]);
        int HoldAck = stoi(data[6]);

        state.ControlValue = QString::fromStdString(to_string(ControlValue));
        state.AddressBusValue = QString::fromStdString(to_string(AddressBusValue));
        state.DataBusValue = QString::fromStdString(to_string(DataBusValue));

        if(HoldAck) // DMA
        {
            state.MasterColor = DMA_COLOR;
            state.Hold = DMA_COLOR;
            state.HoldAck = CPU_COLOR;
        }
        else if (!HoldAck)
        {
            state.MasterColor = CPU_COLOR;
            if(Hold)
            {
                state.Hold = DMA_COLOR;
                state.HoldAck = INITIAL_COLOR;
            }
            else
            {
                state.Hold = INITIAL_COLOR;
                state.HoldAck = INITIAL_COLOR;
            }
        }


        if(AddressBusValue >= RAM_ADDRESS_START && AddressBusValue <= RAM_ADDRESS_END)
        {
            state.DataBusColor = RAM_COLOR;
        }
        else if(AddressBusValue >= IO1_ADDRESS_START && AddressBusValue <= IO1_ADDRESS_END)
        {
            state.DataBusColor = IO1_COLOR;
        }
        else if(AddressBusValue >= IO2_ADDRESS_START && AddressBusValue <= IO2_ADDRESS_END)
        {
            state.DataBusColor = IO2_COLOR;
        }
        else if(AddressBusValue >= DMA_ADDRESS_START && AddressBusValue <= DMA_ADDRESS_END)
        {
            state.DataBusColor = DMA_COLOR;
        }


        this->states.push_back(state);
    }
}
void myScene::rightButton()
{
    if(this->timer->isActive())
        this->timer->stop();
    this->updateColorsClocks(1);
}
void myScene::leftButton()
{
    if(this->timer->isActive())
        this->timer->stop();
    this->updateColorsClocks(-1);
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
    this->updateColorsClocks(1);
}
void myScene::ReadClocks()
{
    this->verilog_file.open(this->verilogPath);
    string s;
    while (getline(this->verilog_file,s))
    {
        if (s == "" || s == " ")
            continue;
        this->clocks_verilog.push_back(s);
    }

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
void myScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    // string the point
    QString s = QString::number(point.x()) + "," + QString :: number(point.y()) ;
    this->cursor->setPlainText(s);
    // print the QGraphicText Item on the Scene
    //    this->cursor->setPos(QPointF(point.x()+10,point.y())); // +10 for visualization only
    //    cout << "Scene(" << point.x() << "," << point.y() << ")" << endl;
}
void myScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    QString s = QString::number(point.x()) + "," + QString :: number(point.y()) ;
    this->cursor->setPlainText(s);
    this->cursor->setPos(QPointF(point.x()+10,point.y())); // +10 for visualization only
    cout << point.x() << "," << point.y() << endl ;
}
void myScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawImage(QRectF(-1000,-475,1800,1000),this->image);
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
