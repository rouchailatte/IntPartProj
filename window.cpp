#include "window.h"
#include "helper.cpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    moveInput = new QLineEdit;
    moveButton = new QPushButton("Move");
    newInput = new QLineEdit;
    newButton = new QPushButton("New");
    pGroup = new QGroupBox;
    tGroup = new QGroupBox;
    lLay = new QVBoxLayout;
    rLay = new QHBoxLayout;
    mLay = new QHBoxLayout;
    lSp = new QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tGroup->setSizePolicy(*lSp);

    connect(moveButton, SIGNAL(clicked()), SLOT(slotMoveExtractInput()));
    connect(newButton, SIGNAL(clicked()), SLOT(slotNewExtractInput()));

//  Layout stuff


    for(int i=0; i<(int)part.size(); i++)
        rLay->addWidget(part[i]->makeTable());
    lLay->addWidget(newInput);
    lLay->addWidget(newButton);
    lLay->addWidget(moveInput);
    lLay->addWidget(moveButton);

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
    std::cout << part.size() << std::endl;
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
