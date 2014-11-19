#include "partition.h"

Partition::Partition(){}
Partition::Partition(const Partition& inputPartition)
{
  value = inputPartition.value;
  length = inputPartition.length;
  partitionElement = inputPartition.partitionElement;
  width = inputPartition.width;
  partition = inputPartition.partition;
}

Partition::Partition(int inputValue, std::vector<int> inputPartition)
{
  value = inputValue;
  length = (int)inputPartition.size();
  width = inputPartition[0];
  partition = inputPartition;

  for(int i=0; i<length; i++)
  {
    std::vector<bool> singlePart(width);
    std::replace(singlePart.begin(), singlePart.begin()+partition[i], false, true);
    partitionElement.push_back(singlePart);
  }
}

Partition::Partition(std::vector<std::vector<int> > inputPart)
{
    std::vector<int> row(inputPart[0]);
    std::vector<int> col(inputPart[1]);
    //row and col starts with index 0, need to change that in shift, since i and j start from 1
    //find the max of i and j first to determine the size of the matrix
    length = *std::max_element(row.begin(), row.end()) + 1;
    width = *std::max_element(col.begin(), col.end()) + 1;
    value = row.size();

    std::vector<std::vector<bool> > resultVec;

    std::vector<bool> singlePart(width);
    for(int i=0; i<length; i++)
        partitionElement.push_back(singlePart);

    for(int i=0; i<(int)row.size(); i++)
        std::replace(partitionElement[row[i]].begin()+col[i], partitionElement[row[i]].begin()+col[i]+1, false, true);
}

int Partition::getLength()
{
  return length;
}
int Partition::getWidth()
{
  return width;
}

std::vector<std::vector<int> > Partition::getPos()
{
    std::vector<int> row;
    std::vector<int> col;
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(partitionElement[i][j])
            {
                row.push_back(i);
                col.push_back(j);
            }
        }
    }
    std::vector<std::vector<int> > result;
    result.push_back(row);
    result.push_back(col);
    return result;
}



Partition Partition::move(int x, int y)
{
    std::vector<int> row(getPos()[0]);
    std::vector<int> col(getPos()[1]);

    for(int i=0; i<(int)row.size(); i++)
    {
        row[i] += y;
        col[i] += x;
    }

    std::vector<std::vector<int> > tempVec;
    tempVec.push_back(row);
    tempVec.push_back(col);
    Partition resultPart(tempVec);
    return resultPart;
}

Partition Partition::stretch(int k, int l)
{
    std::vector<int> row(getPos()[0]);
    std::vector<int> col(getPos()[1]);

    for(int i=0; i<(int)row.size(); i++)
    {
        ++row[i];
        ++col[i];
    }
    for(int i=0; i<(int)row.size(); i++)
    {
        row[i] *= k;
        col[i] /= l;
    }
    for(int i=0; i<(int)row.size(); i++)
    {
        --row[i];
        --col[i];
    }

    std::vector<std::vector<int> > tempVec;
    tempVec.push_back(row);
    tempVec.push_back(col);
    Partition resultPart(tempVec);
    return resultPart;
}

Partition Partition::shift(std::vector<std::vector<int> > inputMat)
{
    std::vector<int> row(getPos()[0]);
    std::vector<int> col(getPos()[1]);

    //need to increment every element in row and col by 1, since the matrix multiplication starts at 1
    for(int i=0; i<(int)row.size(); i++)
    {
        ++row[i];
        ++col[i];
    }

    // do the matrix multiplication and store row and col in new vectors
    std::vector<int> newRow;
    std::vector<int> newCol;

    for(int i=0; i<(int)row.size(); i++)
    {
        int newRowElem = row[i]*inputMat[0][0] + col[i]*inputMat[1][0];
        int newColElem = row[i]*inputMat[0][1] + col[i]*inputMat[1][1];
        newRow.push_back(newRowElem);
        newCol.push_back(newColElem);
    }

    // need to decrement every element in newRow and newCol since the Partition constructor needs it starting from 0 instead of 1
    for(int i=0; i<(int)newRow.size(); i++)
    {
        if(newRow[i] != 0 && newCol[i] != 0)  // cannot decrement 0 by 1, if 0 then 0
        {
            --newRow[i];
            --newCol[i];
        }
    }

    std::vector<std::vector<int> > tempVec;
    tempVec.push_back(newRow);
    tempVec.push_back(newCol);
    Partition resultPart(tempVec);
    return resultPart;
}

std::vector<Partition*> Partition::cut(int a, int b, int c)
{
    std::vector<int> row(getPos()[0]);
    std::vector<int> col(getPos()[1]);

    for(int i=0; i<(int)row.size(); i++)
    {
        ++row[i];
        ++col[i];
    }

    std::vector<int> lowerRow;
    std::vector<int> lowerCol;
    std::vector<int> upperRow;
    std::vector<int> upperCol;

    for(int i=0; i<(int)row.size(); i++)
    {
        if(a*row[i] + b*col[i] <= c)
        {
            upperRow.push_back(row[i]);
            upperCol.push_back(col[i]);
        }
        else
        {
            lowerRow.push_back(row[i]);
            lowerCol.push_back(col[i]);
        }
    }

    for(int i=0; i<(int)lowerRow.size(); i++)
    {
        --lowerRow[i];
        --lowerCol[i];
    }
    for(int i=0; i<(int)upperRow.size(); i++)
    {
        --upperRow[i];
        --upperCol[i];
    }
    std::vector<std::vector<int> > tempUpper;
    tempUpper.push_back(upperRow);
    tempUpper.push_back(upperCol);
    Partition* resultUpper = new Partition(tempUpper);

    std::vector<std::vector<int> > tempLower;
    tempLower.push_back(lowerRow);
    tempLower.push_back(lowerCol);
    Partition* resultLower = new Partition(tempLower);

    std::vector<Partition*> resultPart;
    resultPart.push_back(resultUpper);
    resultPart.push_back(resultLower);

    return resultPart;
}

Partition Partition::paste(Partition* prevPart)
{
    std::vector<int> row(getPos()[0]);
    std::vector<int> col(getPos()[1]);
    std::vector<int> prevRow(prevPart->getPos()[0]);
    std::vector<int> prevCol(prevPart->getPos()[1]);

    for(int i=0; i<(int)prevRow.size(); i++)
    {
        row.push_back(prevRow[i]);
        col.push_back(prevCol[i]);
    }

    std::vector<std::vector<int> > tempVec;
    tempVec.push_back(row);
    tempVec.push_back(col);
    Partition resultPart(tempVec);
    return resultPart;
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

  for(int i=0; i<length; i++)
    partTable->setRowHeight(i, 10);

  for(int i=0; i<width; i++)
    partTable->setColumnWidth(i, 10);

  partTable->horizontalHeader()->hide();
  partTable->verticalHeader()->hide();
  return partTable;
}
