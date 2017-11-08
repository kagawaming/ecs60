// Author Sean Davis
#include<iostream>
#include "tripper.h"
#include "RoadRunner.h"
using namespace std;

Tripper::Tripper(Road *roads, int numRoads, int size) : heap(50000)
{
  adjacency_list = new vertice* [size*size];
  for(int i=0; i<size*size; i++)
  {
    adjacency_list[i] = new vertice[9];
  }
  for(int i=0; i<9; i++)
  {
    adjacency_list[i][0].located = false;
    adjacency_list[i][0].count_adj = 0;
  }
  for(int i=0; i<numRoads; i++)
  {
    if(adjacency_list[roads[i].city1][0].located == false)
    {
      adjacency_list[roads[i].city1][0].city = roads[i].city1;
      adjacency_list[roads[i].city1][0].located = true;
    }
    int j = ++adjacency_list[roads[i].city1][0].count_adj;
    adjacency_list[roads[i].city1][j].city = roads[i].city2;
    //adjacency_list[roads[i].city1][j].dw = adjacency_list[roads[i].city1][j].dw_const = roads[i].distance;
    adjacency_list[roads[i].city1][j].dw = roads[i].distance;
    adjacency_list[roads[i].city1][j].pv = roads[i].city1;
    adjacency_list[roads[i].city1][j].road_num = roads[i].num;
  }
} // Tripper()



Tripper::~Tripper()
{
  for(int i=0; i<10000; i++)
  {
    delete [] adjacency_list[i];
  }
  delete [] adjacency_list;
} // ~Tripper()


int Tripper::findPath(int city1, int city2, int path[], int *pathCount)
{
  /*for(int i=0; i<9; i++)
  {
    for(int j=0; j<9; j++)
    {
      cout<<adjacency_list[i][j].dw<<" ";
    }
    cout<<endl;
  }*/
  //StackAr <int> stack(8000);
  vertice1 min_vertice, insert_vertice,array[10000];
  int previous_city = city2;
  int count;
  min_vertice.city = city1;



  for(int i=0; i<10000; i++)
  {
    array[i].kn = false;
    array[i].dw = 0;
  }



  array[city1].kn = true;
  array[city1].pv = city1;

  while (min_vertice.city != city2)
  {
    int j = 1;
    while (j<= adjacency_list[min_vertice.city][0].count_adj)
    {
      if (array[adjacency_list[min_vertice.city][j].city].kn != true)
      {
        //adjacency_list[min_vertice.city][j].dw += adjacency_list[min_vertice.city][0].dw;
        insert_vertice.dw = adjacency_list[min_vertice.city][j].dw + array[min_vertice.city].dw;
        insert_vertice.pv = adjacency_list[min_vertice.city][j].pv;
        insert_vertice.city = adjacency_list[min_vertice.city][j].city;
        insert_vertice.road_num = adjacency_list[min_vertice.city][j].road_num;

        heap.insert(insert_vertice);
      }
      j++;
    }
    heap.deleteMin(min_vertice);
    while (array[min_vertice.city].kn == true)
    {
      heap.deleteMin(min_vertice);
    }
    array[min_vertice.city].dw = min_vertice.dw;
    array[min_vertice.city].kn = true;
    array[min_vertice.city].pv = min_vertice.pv;
    array[min_vertice.city].road_num = min_vertice.road_num;
  }




  int i = 0;
  int x;
  while(previous_city !=city1)
  {
    path[i] = array[previous_city].road_num;
    previous_city = array[previous_city].pv;
    i++;
  }
  count =i;
  for(i=0;i<count/2;i++)
  {
    x = path[i];
    path[i] = path[count-1 - i];
    path[count-1 - i] = x;
  }


  /*for(i=0; i<count; i++)
  {
    cout<<path[i]<<" ";
  }

  cout<<endl;*/





  /*while (previous_city != city1)
  {
    stack.push(adjacency_list[previous_city][0].road_num);
    previous_city = adjacency_list[previous_city][0].pv;
  }
  //stack.push(city1);
  int i = 0;
  while (!stack.isEmpty())
  {
    path[i] = stack.topAndPop();


    cout<<path[i]<<"  ";


    i++;
  }
  //cout<<path[0]<<"  "<<path[1]<<endl;
  count = i;*/






  pathCount = &count;
  int distance = array[city2].dw;
  /*for(i=0; i<9; i++)
  {
    adjacency_list[i][0].kn = false;
    adjacency_list[i][0].dw = 0;
  }*/
  heap.makeEmpty();


//  cout<<endl;

//cout<<"distance = "<<distance<<endl;
  return distance;  // to avoid warning for now
}  // findPath()
