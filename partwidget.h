#ifndef PARTWIDGET_H
#define PARTWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <QTableWidget>
#include <vector>
#include "partition.h"

class PartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PartWidget(QWidget *parent = 0);
    PartWidget(Partition*);
    void updateTable();
    void setLevel(int);
    int getLevel();
    void setLay();

private:
    QVBoxLayout* mainLay;
    Partition* intPart;
    QCheckBox* mainCheckBox;
    QTableWidget* mainTable;
    int level;
    //which PartThread does it belong to
signals:

public slots:

};

#endif // PARTWIDGET_H
