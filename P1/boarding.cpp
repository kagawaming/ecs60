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


int main(int argc, char** argv){
  ifstream inf(argv[1]);
  int i,end_line,finish,timer,derow4,time1,time2,time3,line;
  Passenger check,checkseat,A;
  Queue<Row*> board(49);
  end_line = 0;
  timer = 0;
  derow4 = 0;
  finish = 0;
  line = 0;
  for(i=48;i>=0;i--)
  {
    Row* row_1=new Row;
    row_1->rownum=i;
    board.enqueue(row_1);
  }



  Row* row2=new Row;
  Row* row3=new Row;
  Row* row4=new Row;
  while(line!=3)
  {
    i++;
    row3 = board.dequeue();

    if (row3->rownum == 0)
    {
      timer +=5;
    }

    if (row3->aisle.isEmpty())//1
    {
      finish++;
      if (row3->rownum == 0)//2
      {
        end_line++;
        if (end_line > 288)
        {
          if (finish >= 49 && line == 0)
          {
            time1=timer-10;
            line++;
            row2=row3;
            board.enqueue(row3);
            end_line=0;
            timer=0;
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
            timer=0;
            board.makeEmpty();
            end_line=0;
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
            timer=0;
            end_line=0;
            break;
          }




          board.enqueue(row3);
          continue;
        }

        A.luggage = 0;
        inf >> A.row;
        inf >> A.seat;
        finish = 0;
        row3->aisle.push(A);
        row2=row3;
        board.enqueue(row3);//3
        continue;
      }
      else//4
      {
        row2=row3;
        board.enqueue(row3);
        continue;

      }
    }
    if (!row3->aisle.isEmpty())//10
    {


      finish = 0;
      check = row3->aisle.top();

      if (check.row == row3->rownum)//12
      {
        check = row3->aisle.topAndPop();
        if (check.luggage < 2)
        {

          check.luggage++;
          row3->aisle.push(check);
          board.enqueue(row3);
          row2=row3;

          continue;
        }
        if (check.luggage == 2)
        {


          if (check.seat == 'A')
          {
            if (!row3->Left.isEmpty())
            {
              row3->aisle.push(row3->Left.topAndPop());
              row3->aisle.push(check);
              board.enqueue(row3);
              row2=row3;
            }
            else{

              row3->Left.push(check);
              board.enqueue(row3);
              row2=row3;

            }
          }
          if (check.seat == 'B')
          {
            if (!row3->Left.isEmpty())
            {
              checkseat = row3->Left.topAndPop();
              if (checkseat.seat == 'A')
              {
                row3->Left.push(checkseat);
                row3->Left.push(check);
                board.enqueue(row3);
                row2=row3;
                continue;
              }
              if (checkseat.seat == 'C')
              {
                row3->aisle.push(checkseat);
                row3->aisle.push(check);
                board.enqueue(row3);
                row2=row3;
                continue;
              }
            }
            else
            {

              row3->Left.push(check);
              board.enqueue(row3);
              row2=row3;
              continue;
            }

          }
          if (check.seat == 'C')
          {
            row3->Left.push(check);
            board.enqueue(row3);
            row2=row3;
            continue;
          }
          if (check.seat == 'F')
          {
            if (!row3->Right.isEmpty())
            {
              row3->aisle.push(row3->Right.topAndPop());
              row3->aisle.push(check);
              board.enqueue(row3);
              row2=row3;
            }
            else{

              row3->Right.push(check);
              board.enqueue(row3);
              row2=row3;

            }
          }
          if (check.seat == 'E')
          {
            if (!row3->Right.isEmpty())
            {
              checkseat = row3->Right.topAndPop();
              if (checkseat.seat == 'F')
              {
                row3->Right.push(checkseat);
                row3->Right.push(check);
                board.enqueue(row3);
                row2=row3;
                continue;
              }
              if (checkseat.seat == 'D')
              {
                row3->aisle.push(checkseat);
                row3->aisle.push(check);
                board.enqueue(row3);
                row2=row3;
                continue;
              }
            }
            else
            {

              row3->Right.push(check);
              board.enqueue(row3);
              row2=row3;
              continue;
            }

          }
          if (check.seat == 'D')
          {
            row3->Right.push(check);
            board.enqueue(row3);
            row2=row3;
            continue;
          }

        }
      }
      else//11
      {
        if (row2->aisle.isEmpty())
        {
          row2->aisle.push(row3->aisle.topAndPop());

          row2=row3;
          board.enqueue(row3);
          if (row3->rownum == 0 && end_line<288)
          {
            end_line++;
            A.luggage = 0;
            inf >> A.row;
            inf >> A.seat;
            finish = 0;
            row3->aisle.push(A);
          }

          continue;
        }
        else
        {
          row2=row3;
          board.enqueue(row3);
          continue;

        }
      }
    }
  }

  cout << "Back to front: " <<time1 <<"\n";
  cout << "Random: " << time2 <<"\n";
  cout << "Outside in: " <<time3 <<"\n";
  return 0;
}
