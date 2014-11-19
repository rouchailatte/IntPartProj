#include "partthread.h"

PartThread::PartThread(QWidget *parent) :
    QWidget(parent)
{
    mainLay = new QHBoxLayout;
    maxLevel = -1;
}

PartThread::PartThread(PartWidget* inputPartWidget)
{
    // This is usually for the new operation

    // set its level to be 0
    inputPartWidget->setLevel(0);

    mainLay = new QHBoxLayout;
    partWidgets.push_back(inputPartWidget);
    maxLevel = 0;

    //meaning contain 1 level(vboxlayout)
    partLayouts.resize(maxLevel+1);
    partBoxes.resize(maxLevel+1);
    partLayouts[0] = new QVBoxLayout;
    partBoxes[0] = new QGroupBox;

}

int PartThread::getMaxLevel()
{
    return maxLevel;
}

void PartThread::incrementMaxLevel()
{
    ++maxLevel;
}

void PartThread::addPart(PartWidget* inputPartWidget)
{
    partWidgets.push_back(inputPartWidget);

    // update the numbers of layout and groupbox according to the level
    while(maxLevel > (int)partLayouts.size() - 1)
    {
        partLayouts.push_back(new QVBoxLayout);
        partBoxes.push_back(new QGroupBox);
    }
}

void PartThread::setLay()
{
    for(int i=0; i < (int)partLayouts.size(); ++i)
    {
        for(int j=0; j < (int)partWidgets.size(); ++j)
        {
            if(partWidgets[j]->getLevel() == i)
            {
                partLayouts[i]->addWidget(partWidgets[j]);
            }
        }
        // set this layout to this group box
        partBoxes[i]->setLayout(partLayouts[i]);
        mainLay->addWidget(partBoxes[i]);
    }
    this->setLayout(mainLay);
}

void PartThread::reset()
{
    maxLevel = -1;
    partWidgets.clear();
    partLayouts.clear();
    partBoxes.clear();
}
