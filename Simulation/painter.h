#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QWidget>
#include "path.h"
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

class Painter : public QObject
{
    Q_OBJECT
private:
    QGraphicsRectItem* CPU;
    QGraphicsRectItem* DMA;
    QGraphicsRectItem* RAM;
    QGraphicsRectItem* IO_1;
    QGraphicsRectItem* IO_2;

    QColor color;
    QPen pen;
    QPainterPath painter;
    map<string,Path*> Paths;
    map<string,Path*> Data_Bus;
    map<string,Path*> Address_Bus;
    map<string,Path*> Control;
    map<string,QGraphicsTextItem*> Text;

    void init_Modules();
    void init_BUSs();
    void init_Text();

    Path* newPath(vector<string> points);
    QGraphicsTextItem* newText(int x , int y , QString Text,bool small_text = false);
public:
    Painter(QObject *parent);
    // BUS
    void setDataBusColor(QColor);
    void setAddressBusColor(QColor);
    void setControlBusColor(QColor);
    // Other Paths
    void setHOLD_Color(QColor);
    void setHOLD_ACK_Color(QColor);
    void setDREQ_IO1_Color(QColor);
    void setDREQ_IO2_Color(QColor);
    void setDACK_IO1_Color(QColor);
    void setDACK_IO2_Color(QColor);
    // Modules
    void setCPU_Color(QColor);
    void setDMA_Color(QColor);
    void setRAM_Color(QColor);
    void setIO1_Color(QColor);
    void setIO2_Color(QColor);
signals:
    void addnewItem(QGraphicsItem*);

public slots:
};

#endif // PAINTER_H
