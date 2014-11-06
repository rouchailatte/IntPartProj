#ifndef PARTITION_H
#define PARTITION_H

#include <QtCore>
#include <QtWidgets>
#include <QTableWidget>
#include <vector>
#include <algorithm>
#include <string>
class Partition
{
public:
    Partition();
    Partition(const Partition&);
    Partition(int inputValue, std::vector<int> inputPartition);

    int getWidth();
    int getLength();

    QTableWidget* makeTable();
    Partition move(int, int);
private:
    int value;
    int length;
    int largestPartition;
    int width;
    std::vector<int> partition;
    std::vector<std::vector<bool> > partitionElement;
};

#endif // PARTITION_H
