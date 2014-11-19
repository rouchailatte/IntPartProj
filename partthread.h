#ifndef PARTTHREAD_H
#define PARTTHREAD_H

#include <QWidget>
#include <QtCore>
#include <QtWidgets>
#include <QTableWidget>
#include <vector>
#include "partwidget.h"

class PartThread : public QWidget
{
    Q_OBJECT
public:
    explicit PartThread(QWidget *parent = 0);
    PartThread(PartWidget*);
    void addPart(PartWidget*);
    void setLay();

    // put everything together, can also serve as refresh

    // when cut, shift, shred, stretch are performed, maxLevel++, and set next
    // incoming partWidget level to be the maxLevel
private:
   QHBoxLayout* mainLay;
   int maxLevel;
   std::vector<PartWidget*> partWidgets;
   std::vector<QVBoxLayout*> partLayouts;
   std::vector<QGroupBox*> partBoxes;
signals:

public slots:

};

#endif // PARTTHREAD_H
