#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include "partition.h"
#include <iostream>
#include <string>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
private:
    QLineEdit* moveInput;
    QPushButton* moveButton;
    Partition* part;

signals:

public slots:
    void slotMoveExtractInput();
};

#endif // WINDOW_H
