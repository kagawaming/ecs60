#include <iostream>
#include "BinaryHeap.h"
#include "BinaryTree.h"
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{
  int i,j,flag,size,length,a;
  char buffer;
  string line;
  BinaryTree array[256];
  BinaryTree array1[256];
  size = 0;
  BinaryHeap<BinaryTree> heap(256);
  //BinaryTree temptree1,temptree2;
  //BinaryTree* temptree3;
  BinaryTree* left,*right;
  BinaryTree* tree;
  ifstream inf(argv[1]);
  while (!inf.eof())
  {
    getline(inf,line);
    if (!inf.eof())
    {
      length = line.length();
    for (i=0;i<length+1;i++)
    {
      if (i < length)
      {
        buffer = line[i];
      }
      if (i == length)
      {
        buffer = '\n';
      }
      flag = 0;
      if (size == 0)
      {
        array[0].setletter(buffer);
        array[0].addcount();
        size++;
        continue;
      }
      else
      {
        for (j=0;j<size;j++)
        {
          if (buffer == array[j].getletter())
          {
            array[j].addcount();
            flag = 1;
          }
        }
        if (flag == 0)
        {
          array[j].setletter(buffer);
          array[j].addcount();
          size++;
          continue;
        }

      }
    }
  }
  }

  for (i=0;i<size;i++)
  {
    heap.insert(array[i]);
  }
  /*for (i=0;i<size;i++)
  {
    *temptree1 = heap.findMin();
    heap.deleteMin();
    cout<<temptree1->getletter()<<" "<<temptree1->getcount()<<"\n";


  }*/
  i=0;

  while (!heap.isEmpty())
  {
    BinaryTree * temptree1 = new BinaryTree();
    heap.deleteMin(*temptree1);
    //tree = &temptree1;

    if (!heap.isEmpty())
    {
      BinaryTree * temptree2 = new BinaryTree();
      heap.deleteMin(*temptree2);
      a = temptree1->getcount()+temptree2->getcount();
      BinaryTree * temptree3 = new BinaryTree(a,temptree1,temptree2);
      heap.insert(*temptree3);
      tree = temptree3;
      i++;
      continue;
    }
    else
    {
      break;
    }
  }
  //cout<<tree->getcount()<<"  "<<tree->getleftchild()->getcount()<<"  "<<tree->getleftchild()->getleftchild()->getcount()<<"\n";

/*  for (i=0;i<6;i++)
  {
    cout<<array1[i].getletter()<<" "<<array1[i].getcount()<<"\n";
  }
  cout<< array1[5].getleftchild()->getcount()<<"  "<<array1[5].getcount()<<"  "<<array1[5].getrightchild()->getcount()<<"\n";
  cout<< array1[4].getleftchild()->getcount()<<"  "<<array1[4].getcount()<<"  "<<array1[4].getrightchild()->getcount()<<"\n";
  cout<< array1[3].getleftchild()->getcount()<<"  "<<array1[3].getcount()<<"  "<<array1[3].getrightchild()->getcount()<<"\n";

*/
string code;
  tree->printTree(tree,code);
 /*cout <<tree->getcount()<<"\n";
  cout <<tree->getleftchild()->getcount()<<"\n";
  cout <<tree->getrightchild()->getcount()<<"\n";
  tree = tree->getleftchild();

  cout <<tree->getleftchild()->getcount()<<"\n";
  cout <<tree->getrightchild()->getcount()<<"\n";*/

  return 0;
}
