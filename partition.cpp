#include "partition.h"

Partition::Partition(){}
Partition::Partition(const Partition& inputPartition)
{
  value = inputPartition.value;
  length = inputPartition.length;
  largestPartition = inputPartition.largestPartition;
  partitionElement = inputPartition.partitionElement;
  width = inputPartition.width;
  partition = inputPartition.partition;
}

Partition::Partition(int inputValue, std::vector<int> inputPartition)
{
  value = inputValue;
  length = (int)inputPartition.size();
  largestPartition = inputPartition[0];
  width = largestPartition;
  partition = inputPartition;

  for(int i=0; i<length; i++)
  {
    std::vector<bool> singlePart(width);
    std::replace(singlePart.begin(), singlePart.begin()+partition[i], false, true);
    partitionElement.push_back(singlePart);
  }
}

int Partition::getLength()
{
  return length;
}
int Partition::getWidth()
{
  return width;
}


Partition Partition::move(int x, int y)
{
  Partition newPartition(*this);
  if(x>0)
  {
    for(int i=0; i<newPartition.length; i++)
    {
      for(int j=0; j<x; j++)
          newPartition.partitionElement[i].insert(newPartition.partitionElement[i].begin(), 0);
    }
  }
  newPartition.width += x;
  if(y > 0)
  {
    for(int k=0; k<y; k++)
    {
      std::vector<bool> emptyRow(newPartition.width);
      newPartition.partitionElement.insert(newPartition.partitionElement.begin(), emptyRow);
    }
  }
  newPartition.length += y;
  return newPartition;
}

QTableWidget* Partition::makeTable()
{
  QTableWidget* partTable = new QTableWidget(length, width);
  for(int i=0; i<length; i++)
  {
      for(int j=0; j<width; j++)
      {
          QTableWidgetItem* tempItem = new QTableWidgetItem;
          tempItem->setBackground(Qt::white);
          partTable->setItem(i, j, tempItem);
      }
  }

  for(int i=0; i<length; i++)
  {
      for(int j=0; j<width; j++)
      {
          if(partitionElement[i][j])
              partTable->item(i,j)->setBackground(Qt::black);
      }
  }

  return partTable;
}
