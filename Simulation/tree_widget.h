#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#define REGISTER "registers"
#define EXECUTE "Execute"
#define DATA_MEMORY "data_memory"
#define ADDRESS 0
#define CODE 1
#define INSTRUCTION 2
#define RegisterValue 2
#define RegisterName 0
#define COLOR 3,92,112

#include <bits/stdc++.h>
#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QIcon>
#include <QCoreApplication>
#include "painter.h"

#define ICON_PATH "/home/amrelsersy/warning-icon.png"
using namespace std;

class Tree_Widget : public QTreeWidget
{
    Q_OBJECT
protected:
    QIcon warning_icon;
    bool centerAlign;
    bool warning;
    QColor color;
    bool flag_color;
    vector<QTreeWidgetItem*> Items ;
    QString Type;

public:
    Tree_Widget(QString type_ray2);
    void addItem();
    void addItem(QStringList);
    void setColor(QTreeWidgetItem*item);
    void setTreeColor(QColor);
    void setAlignCenter(bool);
    void setWarning(bool);
    void SetHeaderLabels(QTreeWidgetItem*item); // not useds
    void Clear();

    void init_DMA();
    void init_Memory();
    void update(vector<string>);
};

#endif // TREE_WIDGET_H
