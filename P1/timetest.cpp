#include <iostream>
#include <fstream>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"

vector<CursorNode <int> > cursorSpace(500001);


int getChoice() {
    int choice;
    cout << "\n";
    cout << "      ADT Menu" << "\n";
    cout << "0. Quit" << "\n";
    cout << "1. LinkedList" << "\n";
    cout << "2. CursorList" << "\n";
    cout << "3. StackAr" << "\n";
    cout << "4. StackLi" << "\n";
    cout << "5. QueueAr" << "\n";
    cout << "6. SkipList" << "\n";
    cout << "Your choice >> ";
    cin >> choice;
    return choice;
}
void RunList(string filename) {
    List <int> list;

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            list.insert(value,list.zeroth());
        }
        else if (command == 'd') {
            list.remove(value);
        }
    }
}

void RunCursorList(string filename) {
    CursorList <int>list(cursorSpace);

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            list.insert(value,list.zeroth());
        }
        else if (command == 'd') {
            list.remove(value);
        }
    }
}

void RunStackAr(string filename) {
    StackAr <int> stack(500001);

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            stack.push(value);
        }
        else if (command == 'd') {
            stack.pop();
        }
    }
}
void RunStackLi(string filename) {
    StackLi <int> stack;

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            stack.push(value);
        }
        else if (command == 'd') {
            stack.pop();
        }
    }
}

void RunQueueAr(string filename) {
    Queue <int>queue(500001);

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            queue.enqueue(value);
        }
        else if (command == 'd') {
            queue.dequeue();
        }
    }
}

void RunSkipList(string filename) {
    SkipList <int> list(-1,500001);

    ifstream inf(filename);
    char command;
    int value;
    inf.ignore(1000,'\n');

    while(inf >> command >> value){
        if (command == 'i') {
            list.insert(value);
        }
        else if (command == 'd') {
            list.deleteNode(list.find(value));
        }
    }
}

int main()
{
  string filename;
  cout<<"Filename >> ";
  cin>>filename;

  int choice;
  CPUTimer ct;
  do {
         choice = getChoice();
         ct.reset();
         switch (choice)
       {
          case 1: RunList(filename); break;
          case 2: RunCursorList(filename); break;
          case 3: RunStackAr(filename); break;
          case 4: RunStackLi(filename); break;
          case 5: RunQueueAr(filename); break;
          case 6: RunSkipList(filename); break;
       }
         cout << "CPU time: " << ct.cur_CPUTime() << endl;
     } while(choice > 0);
     return 0;

}
