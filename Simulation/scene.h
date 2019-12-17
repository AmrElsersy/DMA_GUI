#ifndef SCENE_H
#define SCENE_H

#define MAX_TOP_LEFT_CORNER -984,-446


#include <QCoreApplication>

#include <fstream>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>
#include <QProgressBar>
#include <QGraphicsProxyWidget>

using namespace std;

#include "path.h"
#include "state.h"
#include "painter.h"

class myScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QGraphicsTextItem* cursor; // printing coordinates
    QTimer* timer;
    bool play;
    vector<string> code;

    // painter for our circut
    Painter* DMA_Painter;
    // states
    uint index;
    vector<State> states;
    // reading verilog data each clock cycle
    string verilogPath;
    ifstream verilog_file;
    vector<string> clocks_verilog;
    uint max_clocks;
    // ray2
    QImage image;
    QIcon icon;
    QProgressBar* progressBar;

public:
    explicit myScene(QWidget *parent = nullptr);
    void updateProgressBar();
    void updateStates(int);

private:
    void initColors();
    void initStates();
    void initButtons();
    void ReadClocks();
    vector<string> split_string(string s,string splitter);
    QString parasePC_Text(string pc);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
//    void drawBackground(QPainter *painter, const QRectF &rect) override;

public slots:
    void INIT_Scene(vector<string>);
    void rightButton();
    void leftButton();
    void playButton();
    void continuous_play();
    void addNewItem(QGraphicsItem * item);

};

#endif // SCENE_H
