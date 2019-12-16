#ifndef VIEW_H
#define VIEW_H

#include <bits/stdc++.h>
#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include "scene.h"
#include <QSpinBox>
#include <QObject>

using namespace  std;
class View :public QGraphicsView
{
    Q_OBJECT
public:
    myScene *      my_scene;
    View(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // VIEW_H
