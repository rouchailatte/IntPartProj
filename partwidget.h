#ifndef PARTWIDGET_H
#define PARTWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <QTableWidget>
#include <vector>
#include "partition.h"
#include <iostream>

class PartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PartWidget(QWidget *parent = 0);
    PartWidget(Partition*);
    Partition* getPartition();
    void updateTable();
    void setLevel(int);
    int getLevel();
    void setLay();
    QCheckBox* mainCheckBox;

private:
    QVBoxLayout* mainLay;
    Partition* intPart;
    QTableWidget* mainTable;
    int level;
    //which PartThread does it belong to
signals:

public slots:

};

#endif // PARTWIDGET_H
