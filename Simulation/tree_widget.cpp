#include "tree_widget.h"

Tree_Widget::Tree_Widget(QString type) : QTreeWidget()
{
    this->color.setRgb(COLOR);
    this->flag_color = 1;
    this->centerAlign = false;
    this->warning = false;
    this->Type = type;
    this->setColumnCount(2);
    if (Type == "Memory")
        this->init_Memory();
    else if (Type == "DMA")
        this->init_DMA();
}

void Tree_Widget::addItem()
{
    QTreeWidgetItem * item = new QTreeWidgetItem(QStringList());
    this->setColor(item);
    this->addTopLevelItem(item);

    this->Items.push_back(item);
}

void Tree_Widget::addItem(QStringList s)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(s);

    this->addTopLevelItem(item);
    this->Items.push_back(item);
    this->setColor(item);

    if (this->centerAlign)
        for(int i =0 ; i< item->columnCount(); i++)
            item->setTextAlignment(0,Qt::AlignCenter);

    if (this->warning)
    {
        item->setIcon(1,this->warning_icon);
        item->setTextAlignment(0,Qt::AlignCenter);
    }
}

void Tree_Widget::setColor(QTreeWidgetItem *item)
{
    if (this->flag_color)
    {
        for (int i =0;i <item->columnCount();i++) {
            item->setBackground(i,this->color);
        }
        this->flag_color = 0;
    }
    else {
        this->flag_color = 1;
    }
    for (int i =0;i <item->columnCount();i++)
        item->setTextColor(i,QColor(Qt::white));

}

void Tree_Widget::setTreeColor(QColor clr)
{
    this->color = clr;
}

void Tree_Widget::setAlignCenter(bool center)
{
    this->centerAlign = center;
}

void Tree_Widget::setWarning(bool Warning)
{
    this->warning = Warning;
}

void Tree_Widget::SetHeaderLabels(QTreeWidgetItem *item)
{
    this->setHeaderItem(item);
    if (this->centerAlign)
        for(int i =0 ; i< item->columnCount(); i++)
            item->setTextAlignment(0,Qt::AlignCenter);
}

void Tree_Widget::Clear()
{
    this->clear();
    this->Items.clear();
}

void Tree_Widget::init_DMA()
{
    this->setHeaderLabels({"Register", "Value"});

    this->addItem({"Command","0"});
    this->addItem({"Mask","0"});
    this->addItem({"Request","0"});
    this->addItem({"Status","0"});
    this->addItem({"Mode","0"});

    this->addItem({"BaseAddress_1","0"});
    this->addItem({"currentBaseAddress_1","0"});
    this->addItem({"BaseCount_1","0"});
    this->addItem({"currentBaseCount_1","0"});
    this->addItem({"BaseAddress_2","0"});
    this->addItem({"currentBaseAddress_2","0"});
    this->addItem({"BaseCount_2","0"});
    this->addItem({"currentBaseCount_2","0"});
}

void Tree_Widget::init_Memory()
{
    this->setHeaderLabels({"Address", "Value"});
    for (uint i =RAM_ADDRESS_START ; i< RAM_ADDRESS_END ; i++)
    {
        this->addItem({QString::number(i),"0"});
    }
}

void Tree_Widget::update(vector<string> values)
{
    cout << "values_size =" << values.size() << endl;
    cout << "Items_size =" << Items.size() << endl;

    for (uint i =RAM_ADDRESS_START ; i< RAM_ADDRESS_END-1 ; i++)
        this->Items[i]->setText(1,QString::fromStdString(values[i]));
}
