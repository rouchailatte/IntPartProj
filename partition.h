#ifndef PARTITION_H
#define PARTITION_H

#include <QtCore>
#include <QtWidgets>
#include <QTableWidget>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
class Partition
{
public:
    Partition();
    Partition(const Partition&);
    Partition(int inputValue, std::vector<int>);
    Partition(std::vector<std::vector<int> >);

    int getWidth();
    int getLength();

    std::vector<std::vector<int> > getPos();

    QTableWidget* makeTable();
    Partition move(int, int);
    Partition shift(std::vector<std::vector<int> > inputMat);
private:
    int value;
    int length;
    int width;
    std::vector<int> partition;
    std::vector<std::vector<bool> > partitionElement;
};

#endif // PARTITION_H
