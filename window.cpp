#include "window.h"
#include "helper.cpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    moveInput = new QLineEdit;
    moveButton = new QPushButton("Move");
    newInput = new QLineEdit;
    newButton = new QPushButton("New");
    shiftInput = new QLineEdit;
    shiftButton = new QPushButton("Shift");
    pGroup = new QGroupBox;
    tGroup = new QGroupBox;
    lLay = new QVBoxLayout;
    rLay = new QHBoxLayout;
    mLay = new QHBoxLayout;
    lSp = new QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tGroup->setSizePolicy(*lSp);

    connect(moveButton, SIGNAL(clicked()), SLOT(slotMoveExtractInput()));
    connect(newButton, SIGNAL(clicked()), SLOT(slotNewExtractInput()));
    connect(shiftButton, SIGNAL(clicked()), SLOT(slotShiftExtractInput()));

//  Layout stuff


    for(int i=0; i<(int)part.size(); i++)
        rLay->addWidget(part[i]->makeTable());
    lLay->addWidget(newInput);
    lLay->addWidget(newButton);
    lLay->addWidget(moveInput);
    lLay->addWidget(moveButton);
    lLay->addWidget(shiftInput);
    lLay->addWidget(shiftButton);

    tGroup->setLayout(lLay);
    pGroup->setLayout(rLay);

    mLay->addWidget(pGroup);
    mLay->addWidget(tGroup);

    setLayout(mLay);
}


void Window::refresh()
{
    rLay->addWidget(part.back()->makeTable());
    pGroup->setLayout(rLay);
    mLay->addWidget(pGroup);
    setLayout(mLay);
}


void Window::slotMoveExtractInput()
{
    std::string tempInput = (moveInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    Partition* after_move = new Partition(part.back()->move(inputVec[0], inputVec[1]));
    part.push_back(after_move);
    refresh();
}

void Window::slotNewExtractInput()
{
    std::string tempInput = (newInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    int inputInt = inputVec[0];
    inputVec.erase(inputVec.begin());

    part.push_back(new Partition(inputInt, inputVec));

    refresh();
}

void Window::slotShiftExtractInput()
{
    std::string tempInput = (shiftInput->text()).toStdString();
    std::vector<std::vector<int> > mat = Helper::strToMatrix(tempInput);
    Partition* after_shift = new Partition(part.back()->shift(mat));
    part.push_back(after_shift);
    refresh();
}
