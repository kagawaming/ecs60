#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  int getMaximum()const;
  void position(int v);
  void addtoleft(int value);
  void addtoright(int value);
  LeafNode* split(int lsize,InternalNode *p,BTreeNode *left, BTreeNode *right, int value);
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  // else NULL
  void print(Queue <BTreeNode*> &queue);
}; //LeafNode class

#endif
