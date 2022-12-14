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
    //ellipse = scene->addEllipse(3, 2, 100, 3, bluepen, redBrush);
  

    for (int i = 0; i < 12; i++)
    {
        this->data[i] = new QString[3];
    }
    this->data[0][0] = "Ubit"; data[0][1] = "24.945613, 67.115243"; data[0][2] = "275,70";
    this->data[1][0] = "Chemistry Canteen"; data[1][1] = "24.942762, 67.121296"; data[1][2] = "375,198"; //turn(283,204) 
    this->data[2][0] = "Mehmood HAssan Library"; data[2][1] = "24.939636, 67.121223"; data[2][2] = "330,279";//turn (286,250)and(330,250)
    this->data[3][0] = "Pharmacy Department"; data[3][1] = "24.944090, 67.115438"; data[3][2] = "280,120";
    this->data[4][0] = "Arts"; data[4][1] = "24.937694, 67.119783"; data[4][2] = "320,303";//turn (290,303)
    this->data[5][0] = "IBA"; data[5][1] = "24.940204, 67.115175"; data[5][2] = "215,205";//turn (283,204)
    this->data[6][0] = "Gymnasium Hall"; data[6][1] = "24.937921, 67.118324"; data[6][2] = "288,273";
    this->data[7][0] = "Mathematics Department"; data[7][1] = "24.940104, 67.121523"; data[7][2] = "357, 258";//turn (286,250) nad (354,252)
    this->data[8][0] = "Buisness School"; data[8][1] = "24.938317, 67.111457"; data[8][2] = "128,220";//turn(283,204)
    this->data[9][0] = "Law Department"; data[9][1] = "24.937368, 67.109826"; data[9][2] = "90, 231";
    this->data[10][0] = "BioChemistry"; data[10][1] = "24.940158, 67.118221"; data[10][2] = "287,240";
    this->data[11][0] = "Uni Chowrangi"; data[10][1] = "24.940862, 67.117081"; data[11][2] = "283,204";
    for (int i = 0; i < 12; i++)
    {
        ui.source->addItem(data[i][0]);
        ui.destination->addItem(data[i][0]);
    }
}
void MapsKU::on_calculate_path_clicked()

{//----
    int indsrc = ui.source->currentIndex();
    int inddes = ui.destination->currentIndex();
    


   
      

    //-------
    node_to_node_path(ui.source->currentIndex(), ui.destination->currentIndex(), djikstra(0, adjacencyList, vertices), vertices);
    QPen bluepen(Qt::blue);
    int xs;
    int ys;
    int xd;
    int yd;
    for (size_t i = 0; i < 10; i++)
    {
        if (data[i][0] == ui.source->currentText()) {
            QStringList pieces = data[i][2].split(",");
            xs = pieces.value(pieces.length() - 2).toInt();
            ys = pieces.value(pieces.length() - 1).toInt();
        }
        if (data[i][0] == ui.destination->currentText()) {
            QStringList pieces = data[i][1].split(",");
            xd = pieces.value(pieces.length() - 2).toInt();
            yd = pieces.value(pieces.length() - 1).toInt();
        }
    }
    scene->addLine(xs, ys, xd, yd, bluepen);
    //while (roadcount == 0) {
     //   scene->addLine()
   // }
   // scene->addLine(128 , 220, 283, 204, bluepen);
    scene->addLine(275, 70, 283, 204, bluepen);
    scene->addLine(283, 204, 90, 231, bluepen);
   // scene->addLine(data[indexsource][2], data[indexsource][2], data[indexdes][2], data[indexdes][2], bluepen);
    ball = new QGraphicsEllipseItem(275, 73, 10, 10);
    timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);

    animation = new QGraphicsItemAnimation;
    animation->setItem(ball);
    animation->setTimeLine(timer);

    for (int i = 0; i < 120; ++i) {

        animation->setPosAt(i / 120.0, QPointF(0, i));
    }
    scene->addItem(ball);
    timer->start();
    QString latSource;
    QString lonSource;
    QString latDestination;
    QString lonDestination;
    for (size_t i = 0; i < 10; i++)
    {
        if (data[i][0] == ui.source->currentText()) {
            QStringList pieces = data[i][1].split(",");
            latSource = pieces.value(pieces.length() - 2);
            lonSource = pieces.value(pieces.length() - 1);
        }
        if (data[i][0] == ui.destination->currentText()) {
            QStringList pieces = data[i][1].split(",");
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
    vertices= pieces.value(1).toInt();
    adjacencyList = new int* [vertices];
    for (int i = 0; i < vertices; i++)
    {
        adjacencyList[i] = new int[vertices];
    }
    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
        {
            adjacencyList[i][j]=0;

        }
    }
    QDebug dbg(QtDebugMsg);

    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
        {
            dbg << adjacencyList[i][j] << ' ';
        }
        dbg << '\n';
    }
    for (size_t i = 2; i < pieces.length(); i++)
    {
        QStringList smaller = pieces.value(i).split(',');
        qDebug() << "1 " << smaller.value(0) << " 2 " << smaller.value(1) << " 3 " << smaller.value(2);
        adjacencyList[smaller.value(0).toInt()][smaller.value(1).toInt()] = smaller.value(2).toInt();
    }
    file.close();
    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
        {
            dbg << adjacencyList[i][j]<<' ';
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
    int min;
    for (int i = 0; i < size - 1; i++)
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
    int* stack=new int[size];
    int top = to;
    while (top != from)
    {
        s.push(arr[top]);
        top = arr[top];
    }
    while (!s.empty())
    {
        qDebug() << data[s.top()][0] << " ";
        s.pop();
    }
    qDebug() << data[to][0];
}

int* MapsKU::djikstra(int start, int** arr, int size)
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
    while (t < size)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[start][i] != 0)
            {
                if (distance[i] > distance[start] + arr[start][i])
                {
                    previous[i] = start;
                    distance[i] = distance[start] + arr[start][i];
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

