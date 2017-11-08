#include<iostream>
#include<fstream>
#include "StackAr.h"
#include "QueueAr.h"

using namespace std;

struct Passenger
{
  int row,luggage;
  char seat;
};

class Row
{
public:
  int rownum;
  StackAr<Passenger> Left;
  StackAr<Passenger> Right;
  StackAr<Passenger> aisle;
};


int main(int argc, char* argv[]){
  ifstream inf(argv[1]);
  int i,end_line,finish,timer,derow4,time1,time2,time3,line;
  Passenger check,checkseat;
  Queue<Row*> board(48);
  end_line = 0;
  timer = 0;
  derow4 = 0;
  finish = 0;
  line = 0;

  for(i=48;i>=1;i--)
  {
    Row* row_1=new Row;
    row_1->rownum=i;
    board.enqueue(row_1);
  }
  Row* row3=new Row;
  Row* row4=new Row;

  for(i=1;i<150;i++)
  {
    row3=board.dequeue();
    row4=board.getFront();
    row3->aisle.push(check);
    board.enqueue(row3);
    cout<<row4<<"\n";
  }
}
