#ifndef BinaryTreeH
#define BinaryTreeH
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class BinaryTree
{
private:
  int count;
  char letter;
  string code;
  BinaryTree *Parent;
  const BinaryTree *LeftChild;
  const BinaryTree *RightChild;


public:
  BinaryTree()
  {
    count = 0;
    Parent = NULL;
    LeftChild = NULL;
    RightChild = NULL;
  }
  BinaryTree(int c, const BinaryTree *left, const BinaryTree *right)
  {
    count = c;
    LeftChild = left;
    RightChild = right;
  }
  void setcount (int f)
  {
    count = f;
  }
  void setletter (char l)
  {
    letter = l;
  }
  void addcount()
  {
    count++;
  }
  void setcode(int i,char x)
  {
    code[i]=x;
  }
  int getcount() const
  {
    return count;
  }
  char getletter() const
  {
    return letter;
  }
  string getcode()
  {
    return code;
  }
  bool operator< (const BinaryTree rhs) const
  {
    if (count < rhs.getcount())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  const BinaryTree* getleftchild () const
  {
      return LeftChild;
  }
  const BinaryTree* getrightchild () const
  {
      return RightChild;
  }
  void setleftchild (const BinaryTree left)
  {
    LeftChild = &left;
  }
  void setrightchild (const BinaryTree right)
  {
    RightChild = &right;
  }
  void printTree (const BinaryTree* n, string code) const
  {
    if (n == NULL)
    {
      return;
    }
    code.append("0");
    printTree(n->LeftChild, code);
    if (n->getletter())
    {
      code.pop_back();
      cout << n->letter<<setw(5)<<n->count<<" "<<code<<"\n";
    }
    code.pop_back();
    code.append("1");
    printTree(n->RightChild, code);
  }
};

#endif
