#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include "partition.h"
#include <iostream>
#include <vector>
#include <string>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    void refresh();
private:
    QLineEdit* moveInput;
    QPushButton* moveButton;
    QLineEdit* newInput;
    QPushButton* newButton;
    QLineEdit* shiftInput;
    QPushButton* shiftButton;
    QLineEdit* stretchInput;
    QPushButton* stretchButton;
    QLineEdit* cutInput;
    QPushButton* cutButton;

    QPushButton* resetButton;
    QGroupBox* pGroup;
    QGroupBox* tGroup;
    QVBoxLayout* lLay;
    QHBoxLayout* rLay;
    QHBoxLayout* mLay;
    QSizePolicy* lSp;
    QSizePolicy* rSp;
    std::vector<Partition*> part;

signals:

public slots:
    void reset();
    void slotMove();
    void slotNew();
    void slotShift();
    void slotStretch();
    void slotCut();
};

#endif // WINDOW_H
