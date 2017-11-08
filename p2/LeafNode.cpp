#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

int LeafNode::getMaximum()const
{
  if (count>0)
  {
    int i = count-1;
    int max = values[i];
    return max;
  }
  else
  {
    return 0;
  }
}

void LeafNode::position(int v)//count<leafsize
{
  int i = count-1;
  if (count>0){
    if (v>values[count-1])
    {
      values[count]=v;
    }
    while(v<values[i])
    {
      values[i+1] = values[i];
      values[i] = v;
      i--;
      if(i==-1)
      {
        break;
      }
    }
  }
  else
  {
    values[0] = v;
  }
  if(parent)
  {
    parent->updatekey();
  }
}

void LeafNode::addtoleft(int value)
{
  leftSibling->insert(values[0]);
  for(int i=1;i<count;i++)
  {
    values[i-1]=values[i];
  }
  count--;
  insert(value);
  if(parent)
  {
    parent->updatekey();
  }
}


void LeafNode::addtoright(int value)
{
  if(value>values[count-1])
  {
    rightSibling->insert(value);
  }
  else
  {
    rightSibling->insert(values[count-1]);
    count--;
    insert(value);
  }
  if(parent)
  {
    parent->updatekey();
  }
}

LeafNode* LeafNode::split(int lsize,InternalNode *p,BTreeNode *left, BTreeNode *right, int value)
{
  LeafNode* newsplitleaf = new LeafNode(lsize, p, left, right);
  if (rightSibling!= NULL)
  {
    rightSibling->setLeftSibling(newsplitleaf);
  }
  if (values[count-1]<value)
  {
    newsplitleaf->insert(value);
  }
  else
  {
    newsplitleaf->insert(values[count-1]);
    count--;
    insert(value);
  }

  while (count>(leafSize+1)/2)
  {
    newsplitleaf->insert(values[count-1]);
    count--;
  }
  return newsplitleaf;
}

LeafNode* LeafNode::insert(int value)
{
  if (count==leafSize)
  {
    if (leftSibling!=NULL && leftSibling->getCount()<leafSize)
    {
      addtoleft(value);
      return NULL;
    }
    else if (rightSibling!=NULL && rightSibling->getCount()<leafSize)
    {
      addtoright(value);
      return NULL;
    }
    else
    {
      LeafNode* newsplitleaf=split(leafSize,parent,this,rightSibling,value);
      this->setRightSibling(newsplitleaf);
      return newsplitleaf;
    }
  }
  if (count<leafSize)
  {
    position(value);
    count++;

    return NULL;
  }
  return NULL;
  // students must write this
 // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()
