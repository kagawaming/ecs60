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

  for(i=1;i<3;i++)
  {
    row3=board.dequeue();
    row4=board.getFront();
    row3->aisle.push(check);
    board.enqueue(row3);
    cout<<row3->rownum<<"\n";
  }
  row3->rownum=999;
  row4->rownum=1111;
  for(i=1;i<50;i++)
  {
    row3=board.dequeue();
    row4=board.getFront();
    row3->aisle.push(check);
    board.enqueue(row3);
    cout<<row3->rownum<<"\n";
  }
}

/*if (end_line > 288)
{
  if (finish == 48 && line == 0)
  {
    time1=timer-5;
    board.makeEmpty();
    for(i=48;i>=1;i--)
    {
      Row* row_2=new Row;
      row_2->rownum=i;
      board.enqueue(row_2);
    }
    line++;
    finish = 0;
    timer = 0;
    end_line = 0;
  }
  if (finish == 48 && line == 1)
  {
    time2=timer-5;
    board.makeEmpty();
    for(i=48;i>=1;i--)
    {
      Row* row_3=new Row;
      row_3->rownum=i;
      board.enqueue(row_3);
    }
    line++;
    finish = 0;
    timer = 0;
    end_line = 0;
  }
  if (finish == 48 && line == 2)
  {
    time3=timer-5;
    line++;
  }
  continue;
}*/

if (end_line > 7)
{

  if (finish >= 49 && line == 0)
  {
    time1=timer-5;
    line++;
    row2=row3;
    board.enqueue(row3);
    break;
  }
  board.enqueue(row3);
  continue;
}














if (finish >= 49 && line == 0)
{
  time1=timer-10;
  line++;
  row2=row3;
  board.enqueue(row3);
break;
}
board.enqueue(row3);
continue;







if (finish >= 49 && line == 0)
{
  time1=timer-10;
  line++;
  row2=row3;
  board.enqueue(row3);
  board.makeEmpty();
  for(i=48;i>=0;i--)
  {
    Row* row_2=new Row;
    row_2->rownum=i;
    board.enqueue(row_2);
  }
  continue;
}
if (finish >= 49 && line == 1)
{
  time2=timer-10;
  line++;
  row2=row3;
  board.enqueue(row3);
  board.makeEmpty();
  for(i=48;i>=0;i--)
  {
    Row* row_3=new Row;
    row_3->rownum=i;
    board.enqueue(row_3);
  }
  continue;
}
if (finish >= 49 && line == 2)
{
  time3=timer-10;
  line++;
  row2=row3;
  board.enqueue(row3);
  break;
}
