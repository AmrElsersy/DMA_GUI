#ifndef STATE_H
#define STATE_H

#define INITIAL_COLOR QColor(70,70,70)
#define CPU_COLOR QColor(Qt::red)
#define DMA_COLOR QColor(Qt::yellow)
#define RAM_COLOR QColor(50,200,0)
#define IO1_COLOR QColor(Qt::blue)
#define IO2_COLOR QColor(Qt::green)

#define RAM_ADDRESS_START 0
#define RAM_ADDRESS_END 1023
#define IO1_ADDRESS_START 1024
#define IO1_ADDRESS_END 1056
#define IO2_ADDRESS_START 1057
#define IO2_ADDRESS_END 1089
#define DMA_ADDRESS_START 1090
#define DMA_ADDRESS_END 1115



#include <QWidget>
#include <QObject>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QRectF>
#include <QLabel>
#include <QPointF>
#include <QPainterPath>
#include <bits/stdc++.h>
#include <iostream>
#include <QImage>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>

class State
{
public:
    QColor MasterColor;
    QColor DataBusColor;

    QString ControlValue;
    QString AddressBusValue;
    QString DataBusValue;

    QColor Hold;
    QColor HoldAck;

    QColor DREQ_IO_1;
    QColor DREQ_IO_2;
    QColor DACK_IO_1;
    QColor DACK_IO_2;

    int PC;
    QString Instruction;
    State();
};

#endif // STATE_H
