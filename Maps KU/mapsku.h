#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mapsku.h"
#include <QFile>
#include <stack>
#include <QGraphicsPixmapItem>
#include <qpixmap.h>
#include <qpainter.h>
#include <QPainter>
#include <qtimer.h>
#include <qtimeline.h>
#include <qgraphicsitemanimation.h>
#include <qline>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QMessageBox>

//#include <QtGui>
using namespace std;

class MapsKU : public QMainWindow 
{
    Q_OBJECT

public:
    MapsKU(QWidget *parent = nullptr);
    void set_adjacencyList();
    ~MapsKU();
    int* indegree(int **array,int size);
    int smallest_array(int* arr, int size, bool* known);
    void node_to_node_path(int from, int to, int* arr, int size);
    int* djikstra(int start, int** arr, int size);
    int **adjacencyList;
    int vertices;
    QString** data;
public slots:
    void on_calculate_path_clicked();

private:
    stack<int> s;
    Ui::MapsKUClass ui;
    QGraphicsScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsPixmapItem* item;
    QTimer* time;
    QGraphicsItem* ball;
    QTimeLine* timer;
    QGraphicsItemAnimation* animation;
    QGraphicsLineItem* line;
    QPropertyAnimation* anim;
};

