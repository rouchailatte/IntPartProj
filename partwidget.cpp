#include "partwidget.h"

PartWidget::PartWidget(QWidget *parent) :
    QWidget(parent)
{
    mainLay = new QVBoxLayout;
    mainCheckBox = new QCheckBox("Check to operate on it.");
    mainTable = new QTableWidget;
    level = -1;
}

PartWidget::PartWidget(Partition* inputPartition)
{
    intPart = inputPartition;
    mainTable = new QTableWidget(intPart->makeTable());
    mainLay = new QVBoxLayout;
    mainCheckBox = new QCheckBox("Check to operate on it.");
    level = -1;
}

int PartWidget::getLevel()
{
    return level;
}

Partition* PartWidget::getPartition()
{
    return intPart;
}

void PartWidget::setLevel(int inputLevel)
{
    level = inputLevel;
}

void PartWidget::updateTable()
{
    mainTable = intPart->makeTable();
}

void PartWidget::setLay()
{
    mainTable = intPart->makeTable();
    mainLay->addWidget(mainTable);
    mainLay->addWidget(mainCheckBox);
    this->setLayout(mainLay);
}


