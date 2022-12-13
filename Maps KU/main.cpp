#include "mapsku.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapsKU w;
    w.set_adjacencyList();
    w.indegree(w.adjacencyList, w.vertices);
    w.show();
    return a.exec();
}
