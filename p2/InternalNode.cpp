#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

void InternalNode::updatekey()
{
  if (count>0)
  {
    for (int i=0;i<=(count-1);i++)
    {
      keys[i]=children[i]->getMinimum();
    }
  }

}


int InternalNode::getMaximum()const
{
  if (count>0)
  {
    int i = count-1;
    int max = keys[i];
    return max;
  }
  else
  {
    return 0;
  }
}

BTreeNode* InternalNode::put(int value)//count<leafsize ;
{
  int i;
  if (count>0)
  {
    for (i=count-1;i>=0;i--)
    {
      if (keys[i]<value)
      {
        BTreeNode* child = children[i]->insert(value);
        updatekey();
        return child;
      }
      if ((i==0) && (value<keys[0]))
      {

        BTreeNode* child = children[0]->insert(value);
        updatekey();
        return child;
      }
    }
  }
  else
  {
    BTreeNode* child = children[0]->insert(value);
    updatekey();
    return child;
  }
  return NULL;

}

void InternalNode::addtoleft(BTreeNode* child)
{
  static_cast<InternalNode*>(leftSibling)->insert(children[0]);
  for(int i=0;i<count-1;i++)
  {
    keys[i]=keys[i+1];
    children[i]=children[i+1];
  }
  count--;
  this->insert(child);
}


void InternalNode::addtoright(BTreeNode* child)
{
  int mini=child->getMinimum();
  if(mini>keys[count-1])
  {
    static_cast<InternalNode*>(rightSibling)->insert(child);
    return;
  }
  else
  {
    static_cast<InternalNode*>(rightSibling)->insert(children[count-1]);
    count--;
  }
  this->insert(child);
}

InternalNode* InternalNode::split(BTreeNode* child,InternalNode *p,InternalNode *left,InternalNode *right)
{
  InternalNode* newsplitInt = new InternalNode(internalSize,leafSize,p, left, right);
  if (rightSibling!= NULL)
  {
    rightSibling->setLeftSibling(newsplitInt);
  }
  this->setRightSibling(newsplitInt);
  if (child->getMinimum()>keys[count-1])
  {
    newsplitInt->insert(child);
  }
  else
  {
    newsplitInt->insert(children[count-1]);
    count--;
    this->insert(child);
  }
  while (count>(internalSize+1)/2)
  {
    newsplitInt->insert(children[count-1]);
    count--;
  }
  return newsplitInt;
}




InternalNode* InternalNode::insert(int value)
{
  if (count<internalSize)
  {
    BTreeNode* child = put(value);
    if (child != NULL)
    {
      this->insert(child);
    }
    return NULL;
  }
  if (count==internalSize)
  {
    BTreeNode* child = put(value);
    if (child != NULL)
    {
      if (leftSibling!=NULL && leftSibling->getCount()<internalSize)
      {
        addtoleft(child);
        return NULL;
      }
      else if (rightSibling!=NULL && rightSibling->getCount()<internalSize)
      {
        addtoright(child);
        return NULL;
      }
      else
      {
        InternalNode* node2 = split(child,parent,this,static_cast<InternalNode*>(rightSibling));
        return node2;
      }
    }
    return NULL;
  }
  return NULL;
  // students must write this
 // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{
  children[0]=oldRoot;
  children[1]=node2;
  keys[0]=children[0]->getMinimum();
  keys[1]=children[1]->getMinimum();
  children[0]->setParent(this);
  children[1]->setParent(this);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[0]->setLeftSibling(NULL);
  children[1]->setRightSibling(NULL);
  count=2;// Node must be the root, and node1
  // students must write this
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  newNode->setParent(this);
  int newNodeMini = newNode->getMinimum();
  if (count==0)
  {
    keys[0]=newNodeMini;
    children[0]=newNode;
    count++;
    if(parent)
    {
      parent->updatekey();
    }
    return;
  }
  else if (newNodeMini>keys[count-1])
  {
    keys[count]=newNodeMini;
    children[count]=newNode;
    newNode->setLeftSibling(children[count-1]);
    children[count-1]->setRightSibling(newNode);
    count++;
    if(parent)
    {
      parent->updatekey();
    }
    return;
  }
  int i=count-1;
  while(newNodeMini<keys[i])
  {
    keys[i+1]=keys[i];
    children[i+1]=children[i];
    if(i==0 && newNodeMini<keys[0])
    {
      keys[0]=newNodeMini;
      children[0]=newNode;
      newNode->setRightSibling(children[1]);
      children[1]->setLeftSibling(newNode);
      count++;
      break;
    }
    i--;
  }
  i++;
  if (i>0 && newNodeMini>keys[0])
  {
    keys[i]=newNodeMini;
    children[i]=newNode;
    newNode->setLeftSibling(children[i-1]);
    newNode->setRightSibling(children[i+1]);
    children[i-1]->setRightSibling(newNode);
    children[i+1]->setLeftSibling(newNode);
    count++;
    if(parent)
    {
      parent->updatekey();
    }
    return;
  }
  if(parent)
  {
    parent->updatekey();
  }
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()
