#ifndef SCENE_H
#define SCENE_H

#define MAX_TOP_LEFT_CORNER -984,-446
#define XX -1
#define ZZ -2

#include <QCoreApplication>

#include <fstream>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>
#include <QProgressBar>
#include <QGraphicsProxyWidget>
#include "tree_widget.h"

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
    QProgressBar* progressBar;

    // painter for our circut
    Painter* myPainter;
    // states
    uint index;
    vector<State> states;

    // reading verilog data each clock cycle
    string verilogPath;
    string ramPath;
    string IO1Path;
    string IO2Path;
    string DMAPath;

    ifstream verilog_file;
    vector<string> clocks_verilog;
    vector<string> clocks_ram;
    vector<string> clocks_IO1;
    vector<string> clocks_IO2;
    vector<string> clocks_DMA;
    uint max_clocks;
    // ray2
    QImage image;
    QIcon icon;

    Tree_Widget* DMA_Widget;
    Tree_Widget* RAM_Widget;
    Tree_Widget* IO1_Widget;
    Tree_Widget* IO2_Widget;

public:
    explicit myScene(QWidget *parent = nullptr);
    void ReadClocks();
    void ReadRamClocks();
    void ReadDMAClocks();
    void ReadIO1Clocks();
    void ReadIO2Clocks();
    void initStates();
    void updateStates(int);

private:
    void initColors();
    void initButtons();
    void updateProgressBar();
    vector<string> split_string(string s,string splitter);
    QString parasePC_Text(string pc);
    int string_to_int(string);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *event) override;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
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
