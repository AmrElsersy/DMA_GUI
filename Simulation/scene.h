#ifndef SCENE_H
#define SCENE_H

#define MAX_TOP_LEFT_CORNER -984,-446
#define WIDTH_MUX 1
#define MUXs_SIZE 6

#define fetch 0
#define decode 1
#define ex 2
#define memory 3
#define wb 4

#define PC_POS 0
#define STALL 1
#define FLUSH 2
#include <QCoreApplication>
#include "path.h"

#include <fstream>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <QProgressBar>

using namespace std;

#include "state.h"

class myScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QGraphicsTextItem* cursor; // printing coordinates
    QTimer* timer;
    bool play;
    vector<string> code;

    uint index; // state index
    vector<State> states;


    string verilogPath;
    ifstream verilog_file;

    vector<string> clocks_verilog;
    uint max_clocks;

    QImage image;
    QIcon icon;

    QProgressBar* progressBar;

public:
    explicit myScene(QWidget *parent = nullptr);
    void updateProgressBar();
    void updateColorsClocks(int);

private:
    void initColors();
    void initText();
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
    void drawBackground(QPainter *painter, const QRectF &rect) override;

public slots:
    void INIT_Scene(vector<string>);
    void rightButton();
    void leftButton();
    void playButton();
    void continuous_play();

};

#endif // SCENE_H
