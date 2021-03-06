#include "window.h"
#include "helper.cpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    p = new PartThread;

//    std::vector<int> x;
//    std::vector<int> y;
//    x.push_back(0);
//    x.push_back(1);
//    y.push_back(0);
//    y.push_back(0);
//    std::vector<std::vector<int> >m;
//    m.push_back(x);
//    m.push_back(y);
//    Partition* temP = new Partition(m);
//    PartWidget* temPw = new PartWidget(temP);
//    p->incrementMaxLevel();
//    temPw->setLevel(p->getMaxLevel());

//    p->addPart(temPw);
//    p->setLay();


    moveInput = new QLineEdit;
    moveButton = new QPushButton("Move");
    newInput = new QLineEdit;
    newButton = new QPushButton("New");
    shiftInput = new QLineEdit;
    shiftButton = new QPushButton("Shift");
    shredButton = new QPushButton("Shred");
    stretchInput = new QLineEdit;
    stretchButton = new QPushButton("Stretch");
    cutInput = new QLineEdit;
    cutButton = new QPushButton("Cut");
    pasteButton = new QPushButton("Paste");
    shiftLeftButton = new QPushButton("Shift Left");
    transposeButton = new QPushButton("Transpose");
    shiftUpButton = new QPushButton("Shift Up");
    shiftLeftUpButton = new QPushButton("Shift Left Up");

    resetButton = new QPushButton("Reset");
    pGroup = new QGroupBox;
    tGroup = new QGroupBox;
    t2Group = new QGroupBox;
    lLay = new QVBoxLayout;
    l2Lay = new QVBoxLayout;
    rLay = new QHBoxLayout;
    mLay = new QHBoxLayout;
    lSp = new QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tGroup->setSizePolicy(*lSp);
    t2Group->setSizePolicy(*lSp);

    connect(moveButton, SIGNAL(clicked()), SLOT(slotMove()));
    connect(newButton, SIGNAL(clicked()), SLOT(slotNew()));
    connect(shiftButton, SIGNAL(clicked()), SLOT(slotShift()));
    connect(shredButton, SIGNAL(clicked()), SLOT(slotShred()));
    connect(stretchButton, SIGNAL(clicked()), SLOT(slotStretch()));
    connect(cutButton, SIGNAL(clicked()), SLOT(slotCut()));
    connect(pasteButton, SIGNAL(clicked()), SLOT(slotPaste()));
    connect(resetButton, SIGNAL(clicked()), SLOT(reset()));
    connect(shiftLeftButton, SIGNAL(clicked()), SLOT(slotShiftLeft()));
    connect(shiftUpButton, SIGNAL(clicked()), SLOT(slotShiftUp()));
    connect(shiftLeftUpButton, SIGNAL(clicked()), SLOT(slotShiftLeftUp()));
    connect(transposeButton, SIGNAL(clicked()), SLOT(slotTranspose()));
//  Layout stuff

    rLay->addWidget(p);
//    for(int i=0; i<(int)part.size(); i++)
//        rLay->addWidget(part[i]->makeTable());
    lLay->addWidget(newInput);
    lLay->addWidget(newButton);
    lLay->addWidget(moveInput);
    lLay->addWidget(moveButton);
    lLay->addWidget(shiftInput);
    lLay->addWidget(shiftButton);
    lLay->addWidget(shredButton);
    lLay->addWidget(stretchInput);
    lLay->addWidget(stretchButton);
    lLay->addWidget(cutInput);
    lLay->addWidget(cutButton);
    lLay->addWidget(pasteButton);
    l2Lay->addWidget(shiftLeftButton);
    l2Lay->addWidget(shiftUpButton);
    l2Lay->addWidget(shiftLeftUpButton);
    l2Lay->addWidget(transposeButton);
    l2Lay->addWidget(resetButton);

    l2Lay->setSpacing(8);

    tGroup->setLayout(lLay);
    t2Group->setLayout(l2Lay);
    pGroup->setLayout(rLay);

    tGroup->setTitle("Basic Transformation");
    t2Group->setTitle("Helper Transformation");
    tGroup->setFixedWidth(120);
    t2Group->setFixedWidth(120);

    pGroup->setTitle("Integer Partitions");

    mLay->addWidget(pGroup);
    mLay->addWidget(tGroup);
    mLay->addWidget(t2Group);

    setLayout(mLay);
}


//void Window::refresh()
//{
//    QLayoutItem *child;
//    while ((child = rLay->takeAt(0)) != 0)
//    {
//        delete child->widget();
//        delete child;
//    }
////    for(int i=0; i<(int)part.size(); i++)
////        rLay->addWidget(part[i]->makeTable());
////    rLay->addWidget(p);

//    pGroup->setLayout(rLay);
//    mLay->addWidget(pGroup);
//    setLayout(mLay);
//}

std::vector<Partition*> Window::getInputPartition()
{
    std::vector<Partition*> tempVec;

    for(int i=0; i<(int)p->partWidgets.size(); ++i)
    {
        if(p->partWidgets[i]->mainCheckBox->isChecked())
            tempVec.push_back(p->partWidgets[i]->getPartition());

    }
    return tempVec;
}

int Window::getInputLevel()
{
    for(int i=0; i<(int)p->partWidgets.size(); ++i)
        if(p->partWidgets[i]->mainCheckBox->isChecked())
            return p->partWidgets[i]->getLevel();
}

void Window::toggleCheckBoxes()
{
    for(int i=0; i<(int)p->partWidgets.size(); ++i)
    {
        if(p->partWidgets[i]->mainCheckBox->isChecked())
            p->partWidgets[i]->mainCheckBox->toggle();
    }
}

void Window::slotNew()
{
    std::string tempInput = (newInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
    int inputInt = inputVec[0];
    inputVec.erase(inputVec.begin());


    PartWidget* newPw = new PartWidget(new Partition(inputInt, inputVec));
    newPw->setLay();
    p->incrementMaxLevel();
    newPw->setLevel(p->getMaxLevel());

    p->addPart(newPw);
    p->setLay();

//    part.push_back(new Partition(inputInt, inputVec));
    newInput->setText("");
//    refresh();
    this->update();

}


void Window::slotMove()
{
    std::string tempInput = (moveInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);

//    Partition* after_move = new Partition(part.back()->move(inputVec[0], inputVec[1]));
    Partition* tempPart = this->getInputPartition()[0];
    Partition* tempTwo = tempPart->move(inputVec[0], inputVec[1]);

    PartWidget* after_move_pw = new PartWidget(tempTwo);
    // ++p.maxLevel
    after_move_pw->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_move_pw->setLevel(selectedLevel+1);


    p->addPart(after_move_pw);

    p->setLay();

//    part.push_back(after_move);
    moveInput->setText("");
    this->toggleCheckBoxes();
    this->update();
}


void Window::slotShift()
{
    std::string tempInput = (shiftInput->text()).toStdString();
    std::vector<std::vector<int> > mat = Helper::strToMatrix(tempInput);
//    Partition* after_shift = new Partition(part.back()->shift(mat));

    PartWidget* after_shift_pw = new PartWidget(this->getInputPartition()[0]->shift(mat));

    after_shift_pw->setLay();
    // ++p.maxLevel
    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_shift_pw->setLevel(selectedLevel+1);

    p->addPart(after_shift_pw);
    p->setLay();
//    part.push_back(after_shift);
    shiftInput->setText("");
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotShred()
{
    std::vector<Partition*> after_shred = this->getInputPartition()[0] -> shred();

    PartWidget* upper = new PartWidget(after_shred[0]);
    PartWidget* lower = new PartWidget(after_shred[1]);

    upper->setLay();
    lower->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    upper->setLevel(selectedLevel+1);
    lower->setLevel(selectedLevel+1);

    p->addPart(upper);
    p->addPart(lower);

    p->setLay();

    this->toggleCheckBoxes();
    this->update();
}

void Window::slotStretch()
{
    std::string tempInput = (stretchInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);
//    Partition* after_stretch = new Partition(part.back()->stretch(inputVec[0], inputVec[1]));

    PartWidget* after_stretch_pw = new PartWidget(this->getInputPartition()[0]->stretch(inputVec[0], inputVec[1]));
    after_stretch_pw->setLay();
    // ++p.maxLevel
    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_stretch_pw->setLevel(selectedLevel+1);

    p->addPart(after_stretch_pw);
    p->setLay();

//    part.push_back(after_stretch);
    stretchInput->setText("");
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotCut()
{
    std::string tempInput = (cutInput->text()).toStdString();
    std::vector<int> inputVec = Helper::inputParser(tempInput);

//    std::vector<Partition*> after_cut = part.back()->cut(inputVec[0], inputVec[1], inputVec[2]);

    std::vector<Partition*> after_cut = this->getInputPartition()[0]->cut(inputVec[0], inputVec[1], inputVec[2]);
    PartWidget* upper = new PartWidget(after_cut[0]);
    PartWidget* lower = new PartWidget(after_cut[1]);
    upper->setLay();
    lower->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    upper->setLevel(selectedLevel+1);
    lower->setLevel(selectedLevel+1);

    p->addPart(upper);
    p->addPart(lower);

    p->setLay();

//    part.push_back((after_cut[0]));
//    part.push_back((after_cut[1]));
    cutInput->setText("");
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotPaste()
{
//    Partition* inputPart = part[part.size()-2];
//    Partition* after_paste = new Partition(part.back()->paste(inputPart));
    Partition* tempPartOne = new Partition(*(this->getInputPartition()[0]));
    Partition* tempPartTwo = new Partition(*(this->getInputPartition()[1]));

    PartWidget* after_past_pw = new PartWidget(tempPartOne->paste(tempPartTwo));
//    part.push_back(after_paste);
    after_past_pw->setLay();
    p->incrementMaxLevel();
    after_past_pw->setLevel(p->getMaxLevel());

    p->addPart(after_past_pw);
    p->setLay();
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotShiftLeft()
{
    PartWidget* after_shift_left = new PartWidget(this->getInputPartition()[0]->shiftLeft());
    after_shift_left->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_shift_left->setLevel(selectedLevel+1);

    p->addPart(after_shift_left);
    p->setLay();
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotShiftUp()
{
    PartWidget* after_shift_up = new PartWidget(this->getInputPartition()[0]->shiftUp());
    after_shift_up->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_shift_up->setLevel(selectedLevel+1);

    p->addPart(after_shift_up);
    p->setLay();
    this->toggleCheckBoxes();
    this->update();
}


void Window::slotShiftLeftUp()
{
    PartWidget* after_shift_left_up = new PartWidget(this->getInputPartition()[0]->shiftLeftUp());
    after_shift_left_up->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_shift_left_up->setLevel(selectedLevel+1);

    p->addPart(after_shift_left_up);
    p->setLay();
    this->toggleCheckBoxes();
    this->update();
}

void Window::slotTranspose()
{
    PartWidget* after_transpose = new PartWidget(this->getInputPartition()[0]->transpose());
    after_transpose->setLay();

    int selectedLevel = this->getInputLevel();
    if(selectedLevel == p->getMaxLevel())
        p->incrementMaxLevel();
    after_transpose->setLevel(selectedLevel+1);

    p->addPart(after_transpose);
    p->setLay();

    this->toggleCheckBoxes();

    this->update();
}

void Window::reset()
{
//    part.clear();
    p->reset();
    p->setLay();
    this->update();
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
