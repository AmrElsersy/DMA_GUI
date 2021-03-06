#ifndef STATE_H
#define STATE_H

#define INITIAL_COLOR QColor(25,25,25)

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
    QColor CPUColor;
    QColor DMAColor;
    QColor RAMColor;
    QColor IO1Color;
    QColor IO2Color;

    QColor AddressBusColor;
    QColor ControlBusColor;
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

    QColor RamTextColor;
    QColor KeyboardTextColor;
    QColor PrinterTextColor;


    int PC;
    QString Instruction;
    State();
};

#endif // STATE_H
