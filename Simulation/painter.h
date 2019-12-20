#ifndef PAINTER_H
#define PAINTER_H

#define OFF_COLOR QColor(70,70,70)
#define CPU_COLOR QColor(Qt::blue)
#define DMA_COLOR QColor(Qt::darkCyan)
#define RAM_COLOR QColor(Qt::darkRed)
#define IO1_COLOR QColor("#808000")
#define IO2_COLOR QColor("#483D8B")

#define RAM_ADDRESS_START 16
#define RAM_ADDRESS_END 599
#define IO1_ADDRESS_START 600
#define IO1_ADDRESS_END 632
#define IO2_ADDRESS_START 633
#define IO2_ADDRESS_END 665
#define DMA_ADDRESS_START 0
#define DMA_ADDRESS_END 16

#include <QObject>
#include <QWidget>
#include "path.h"
#include "state.h"
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
    // Values
    void setControlValue(QString);
    void setDataBusValue(QString);
    void setAddressBusValue(QString);
    // CPU Data
    void setPC(QString);
    void setInstruction(QString);
    // Colors for CPU talking
    void setRAMTextColor(QColor);
    void setKeyboardTextColor(QColor);
    void setPrinterTextColor(QColor);
    // ray2
    void checkPos(int x , int y);
signals:
    void addnewItem(QGraphicsItem*);

public slots:
};

#endif // PAINTER_H
