#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Window* w = new Window;
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}
