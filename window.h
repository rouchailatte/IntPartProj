#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include "partition.h"
#include <iostream>
#include <vector>
#include <string>
#include "partthread.h"
#include "partwidget.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    void refresh();
    std::vector<Partition*> getInputPartition();
    int getInputLevel();
    void toggleCheckBoxes();
private:
    QLineEdit* moveInput;
    QPushButton* moveButton;
    QLineEdit* newInput;
    QPushButton* newButton;
    QLineEdit* shiftInput;
    QPushButton* shiftButton;
    QPushButton* shredButton;
    QLineEdit* stretchInput;
    QPushButton* stretchButton;
    QLineEdit* cutInput;
    QPushButton* cutButton;
    QPushButton* pasteButton;
    QPushButton* shiftLeftButton;
    QPushButton* shiftUpButton;
    QPushButton* shiftLeftUpButton;
    QPushButton* transposeButton;

    QPushButton* resetButton;
    QGroupBox* pGroup;
    QGroupBox* tGroup;
    QGroupBox* t2Group;
    QVBoxLayout* lLay;
    QVBoxLayout* l2Lay;
    QHBoxLayout* rLay;
    QHBoxLayout* mLay;
    QSizePolicy* lSp;
    QSizePolicy* rSp;
//    std::vector<Partition*> part;
    PartThread* p;

signals:

public slots:
    void reset();
    void slotMove();
    void slotNew();
    void slotShift();
    void slotShred();
    void slotStretch();
    void slotCut();
    void slotPaste();
    void slotShiftLeft();
    void slotTranspose();
    void slotShiftUp();
    void slotShiftLeftUp();
};

#endif // WINDOW_H
