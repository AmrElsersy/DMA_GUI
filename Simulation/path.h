#ifndef PATH_H
#define PATH_H
#define PATH_WIDTH 4
#define TEXT_COLOR Qt::white
#define SMALL_FONT_SIZE 10
#define FONT_SIZE 14

#include <QPointF>
#include <QPoint>
#include <QPainterPath>
#include <QPen>
#include <QColor>
#include <bits/stdc++.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <iostream>
#include <stdarg.h>
#include "state.h"
using namespace std;

class Path :  public QObject, public QGraphicsPathItem
{
    Q_OBJECT
private:
    QGraphicsTextItem* textValue;
    QPen pen;
    QColor color;

    vector<QPointF> convert_strings_Points(vector<string>);
    vector<string>  split_string(string s,string splitter);

public:
    explicit Path(vector<string> points);
    void setColor(QColor clr , int Width = PATH_WIDTH );
    void setWidth(int Width);
    void setTextValue(int value);

signals:
    void addTextItem();
public slots:
};

#endif // PATH_H
