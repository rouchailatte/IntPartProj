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
    stretchInput = new QLineEdit;
    stretchButton = new QPushButton("Stretch");
    cutInput = new QLineEdit;
    cutButton = new QPushButton("Cut");
    pasteButton = new QPushButton("Paste");

    resetButton = new QPushButton("Reset");
    pGroup = new QGroupBox;
    tGroup = new QGroupBox;
    lLay = new QVBoxLayout;
    rLay = new QHBoxLayout;
    mLay = new QHBoxLayout;
    lSp = new QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tGroup->setSizePolicy(*lSp);

    connect(moveButton, SIGNAL(clicked()), SLOT(slotMove()));
    connect(newButton, SIGNAL(clicked()), SLOT(slotNew()));
    connect(shiftButton, SIGNAL(clicked()), SLOT(slotShift()));
    connect(stretchButton, SIGNAL(clicked()), SLOT(slotStretch()));
    connect(cutButton, SIGNAL(clicked()), SLOT(slotCut()));
    connect(pasteButton, SIGNAL(clicked()), SLOT(slotPaste()));
    connect(resetButton, SIGNAL(clicked()), SLOT(reset()));

//  Layout stuff


    for(int i=0; i<(int)part.size(); i++)
        rLay->addWidget(part[i]->makeTable());
    lLay->addWidget(newInput);
    lLay->addWidget(newButton);
    lLay->addWidget(moveInput);
    lLay->addWidget(moveButton);
    lLay->addWidget(shiftInput);
    lLay->addWidget(shiftButton);
    lLay->addWidget(stretchInput);
    lLay->addWidget(stretchButton);
    lLay->addWidget(cutInput);
    lLay->addWidget(cutButton);
    lLay->addWidget(pasteButton);

    lLay->addWidget(resetButton);
    tGroup->setLayout(lLay);
    pGroup->setLayout(rLay);

    mLay->addWidget(pGroup);
    mLay->addWidget(tGroup);

    setLayout(mLay);
}


void Window::refresh()
{
    QLayoutItem *child;
    while ((child = rLay->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }
    for(int i=0; i<(int)part.size(); i++)
        rLay->addWidget(part[i]->makeTable());

    pGroup->setLayout(rLay);
    mLay->addWidget(pGroup);
    setLayout(mLay);
}


void Window::slotMove()
{
    std::string tempInput = (moveInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    Partition* after_move = new Partition(part.back()->move(inputVec[0], inputVec[1]));
    part.push_back(after_move);
    moveInput->setText("");

    refresh();
}

void Window::slotNew()
{
    std::string tempInput = (newInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    int inputInt = inputVec[0];
    inputVec.erase(inputVec.begin());

    part.push_back(new Partition(inputInt, inputVec));
    newInput->setText("");

    refresh();
}

void Window::slotShift()
{
    std::string tempInput = (shiftInput->text()).toStdString();
    std::vector<std::vector<int> > mat = Helper::strToMatrix(tempInput);
    Partition* after_shift = new Partition(part.back()->shift(mat));
    part.push_back(after_shift);
    shiftInput->setText("");

    refresh();
}

void Window::slotStretch()
{
    std::string tempInput = (stretchInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    Partition* after_stretch = new Partition(part.back()->stretch(inputVec[0], inputVec[1]));
    part.push_back(after_stretch);
    stretchInput->setText("");

    refresh();
}

void Window::slotCut()
{
    std::string tempInput = (cutInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);

    std::vector<Partition*> after_cut = part.back()->cut(inputVec[0], inputVec[1], inputVec[2]);
    part.push_back((after_cut[0]));
    part.push_back((after_cut[1]));
    cutInput->setText("");

    refresh();
}

void Window::slotPaste()
{
    Partition* inputPart = part[part.size()-2];
    Partition* after_paste = new Partition(part.back()->paste(inputPart));
    part.push_back(after_paste);

    refresh();
}

void Window::reset()
{
    part.clear();
    refresh();
}

// construct part Widget in here, not in the actual computation function
// keep things as they are in Partition.cpp

/*
 * Example
 * PartThread p;
 * // in new
 * // don't forget to setLay() for partWidget in every transformation
 * p = new PartThread(after_new_partWidget);
 * p.setLay();
 *
 * // in cut
 *
 * for(int i=0; i<p.partWidgets.size(); ++i)
 * {
 *  if(partWidgets[i].mainCheckButton.ischecked())
 *      partWidget* inputPartWidget = new partWidget(partWidgets[i]);
 * }
 *
 * partWidget* upper = after_cut[0];
 * partWidget* lower = after_cut[1];
 *
 * ++p.maxLevel;
 * upper.setLevel(p.maxLevel);
 * lower.setLevel(p.maxLevel);
 *
 * p.addPart(upper);
 * p.addPart(lower);
 *
 * p.setLay();
 *
 */
