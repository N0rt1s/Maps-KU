#include "mapsku.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

MapsKU::MapsKU(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);


    scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen bluepen(Qt::blue);
    bluepen.setWidth(3);
    item = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/maplegends-02.png"));
    scene->addItem(item);
  
    this->data = new QString*[10];
    for (int i = 0; i < 10; i++)
    {
        this->data[i] = new QString[3];
    }
    this->data[0][0] = "Ubit"; this->data[0][1] = "24.945613, 67.115243"; this->data[0][2] = "275,70";
    this->data[1][0] = "Chemistry Canteen"; this->data[1][1] = "24.942762, 67.121296"; this->data[1][2] = "375,198"; //turn(283,204) 
    this->data[2][0] = "Pharmacy Department"; this->data[2][1] = "24.944090, 67.115438"; this->data[2][2] = "280,120";
    this->data[3][0] = "Arts"; this->data[3][1] = "24.937694, 67.119783"; this->data[3][2] = "320,303";//turn (290,303)
    this->data[4][0] = "IBA"; this->data[4][1] = "24.940204, 67.115175"; this->data[4][2] = "215,205";//turn (283,204)
    this->data[5][0] = "Gymnasium Hall"; this->data[5][1] = "24.937921, 67.118324"; this->data[5][2] = "288,273";
    this->data[6][0] = "Buisness School"; this->data[6][1] = "24.938317, 67.111457"; this->data[6][2] = "128,220";//turn(283,204)
    this->data[7][0] = "Law Department"; this->data[7][1] = "24.937368, 67.109826"; this->data[7][2] = "90, 231";
    this->data[8][0] = "BioChemistry"; this->data[8][1] = "24.940158, 67.118221"; this->data[8][2] = "287,240";
    this->data[9][0] = "Uni Chowrangi"; this->data[9][1] = "24.940862, 67.117081"; this->data[9][2] = "283,204";
    for (int i = 0; i < 10; i++)
    {
        ui.source->addItem(this->data[i][0]);
        ui.destination->addItem(this->data[i][0]);
    }
}
void MapsKU::on_calculate_path_clicked()

{
    int indsrc = ui.source->currentIndex();
    int inddes = ui.destination->currentIndex();
    //

    node_to_node_path(indsrc, inddes, djikstra(indsrc, inddes, this->adjacencyList, this->vertices), this->vertices);
// //HEAD
//    //while (roadcount == 0) {
//     //   scene->addLine()
//   // }
//   // scene->addLine(128 , 220, 283, 204, bluepen);
//    scene->addLine(275, 70, 283, 204, bluepen);
//    scene->addLine(283, 204, 90, 231, bluepen);
//   // scene->addLine(this->data[indexsource][2], this->data[indexsource][2], this->data[indexdes][2], this->data[indexdes][2], bluepen);
////=======
   


    QString latSource;
    QString lonSource;
    QString latDestination;
    QString lonDestination;
    for (size_t i = 0; i < 10; i++)
    {
        if (this->data[i][0] == ui.source->currentText()) {
            QStringList pieces = this->data[i][1].split(",");
            latSource = pieces.value(pieces.length() - 2);
            lonSource = pieces.value(pieces.length() - 1);
        }
        if (this->data[i][0] == ui.destination->currentText()) {
            QStringList pieces = this->data[i][1].split(",");
            latDestination = pieces.value(pieces.length() - 2);
            lonDestination = pieces.value(pieces.length() - 1);
        }
    }
    QString text=ui.source->currentText() + ": Lat " + latSource + " Lon " + lonSource + '\n' +
                 ui.destination->currentText() + ": Lat " + latDestination + " Lon " + lonDestination  ;
    ui.textEdit->setText(text);
    
   
}

void MapsKU :: set_adjacencyList() {
    QString data;
    QString fileName(":/new/prefix1/graph.txt");
    QFile file(fileName);
    !file.open(QIODevice::ReadOnly);
    data = file.readAll();
    data= data.replace(" ", "");
    QStringList pieces = data.split("\r\n");
    this->vertices= pieces.value(1).toInt();
    this->adjacencyList = new int* [this->vertices];
    for (int i = 0; i < this->vertices; i++)
    {
        this->adjacencyList[i] = new int[this->vertices];
    }
    for (size_t i = 0; i < this->vertices; i++)
    {
        for (size_t j = 0; j < this->vertices; j++)
        {
            this->adjacencyList[i][j]=0;

        }
    }
    QDebug dbg(QtDebugMsg);

    for (size_t i = 0; i < this->vertices; i++)
    {
        for (size_t j = 0; j < this->vertices; j++)
        {
            dbg << this->adjacencyList[i][j] << ' ';
        }
        dbg << '\n';
    }
    for (size_t i = 2; i < pieces.length(); i++)
    {
        QStringList smaller = pieces.value(i).split(',');
        qDebug() << "1 " << smaller.value(0) << " 2 " << smaller.value(1) << " 3 " << smaller.value(2);
        this->adjacencyList[smaller.value(0).toInt()][smaller.value(1).toInt()] = smaller.value(2).toInt();
    }
    file.close();
    for (size_t i = 0; i < this->vertices; i++)
    {
        for (size_t j = 0; j < this->vertices; j++)
        {
            dbg << this->adjacencyList[i][j]<<' ';
        }
        dbg << '\n';
    }
}
int* MapsKU::indegree(int **array,int size) {
    int* IN = new int[size];
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
        {
            if (array[j][i] != 0)
            {
                count++;
            }
        }
        IN[i] = count;
    }
    /*for (size_t i = 0; i < size; i++)
    {
        qDebug() << IN[i];
    }*/
    return IN;
}
int MapsKU::smallest_array(int* arr, int size, bool* known)
{
    QDebug dbg(QtDebugMsg);
    int min;
    for (size_t i = 0; i < size; i++)
    {
        dbg <<arr[i];
    }
    for (int i = 0; i < size ; i++)
    {
        if (arr[i] < 999999 && known[i] != true)
        {
            min = i;
        }
    }
    return min;
}
void MapsKU::node_to_node_path(int from, int to, int* arr, int size)
{
    int indsrc = ui.source->currentIndex();
    int inddes = ui.destination->currentIndex();
    QPen bluepen(Qt::blue);
    int xs;
    int ys;
    int xd;
    int yd;
  /*  ball = new QGraphicsEllipseItem(275, 73, 10, 10);
    timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);

    animation = new QGraphicsItemAnimation;
    animation->setItem(ball);
    animation->setTimeLine(timer);*/
    /*for (int i = 0; i < 120; ++i) {

        animation->setPosAt(i / 120.0, QPointF(0, i));
    }
    scene->addItem(ball);
    timer->start();*/
    while (!lineList.isEmpty()) {
        delete lineList.takeFirst();
    }
    int* stack=new int[size];
    int top = to;
    int i = 0;
    while (top != from)
    {
        s.push(arr[top]);
        top = arr[top];
    }
    while (!s.empty())
    {
        qDebug() << this->data[s.top()][0] << " ";
        QStringList pieces = this->data[s.top()][2].split(",");
        xs = pieces.value(pieces.length() - 2).toInt();
        ys = pieces.value(pieces.length() - 1).toInt();

        s.pop();
        if (s.empty()) {
            QStringList piecesdes = this->data[to][2].split(",");
            xd = piecesdes.value(piecesdes.length() - 2).toInt();
            yd = piecesdes.value(piecesdes.length() - 1).toInt();
            lineList<<scene->addLine(xs, ys, xd, yd, bluepen);
        }
        else {
            QStringList piecesdes = this->data[s.top()][2].split(",");
            xd = piecesdes.value(piecesdes.length() - 2).toInt();
            yd = piecesdes.value(piecesdes.length() - 1).toInt();
            lineList << scene->addLine(xs, ys, xd, yd, bluepen);
        }
    }
    qDebug() << this->data[to][0];
}

int* MapsKU::djikstra(int start,int end, int** arr, int size)
{
    int t = 0;
    bool* known=new bool[size];
    int* distance=new int[size];
    int* previous = new int[size];
    previous[start] = -1;
    for (int i = 0; i < size; i++)
    {
        if (i == start)
        {
            known[i] = true;
            distance[i] = 0;
        }
        else
        {
            known[i] = false;
            distance[i] = 9999999;
        }
    }
    while (start != end)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[start][i] != 0)
            {
                if (distance[i] > distance[start] + arr[start][i])
                {
                    previous[i] = start;
                    distance[i] = distance[start] + arr[start][i];
                    qDebug() << distance[i] << " at " << i;
                }
            }
        }
        start = smallest_array(distance, size, known);
        known[start] = true;
        t++;
    }
    return previous;
}

MapsKU::~MapsKU()
{}

