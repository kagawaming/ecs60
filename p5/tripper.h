// Author Sean Davis
#ifndef _TRIPPER_H
#define	_TRIPPER_H

#include "RoadRunner.h"
#include "BinaryHeap.h"
//#include "StackAr.h"

class vertice {
public:
  int city;
  int pv;
  int dw;
//  int dw_const;
  bool kn;
  int count_adj;
  bool located;
  int road_num;
};

class vertice1 {
public:
  int city;
  int pv;
  int dw;
  bool kn;
  int road_num;

  bool operator< (vertice1 rhs) const
  {
    if (dw < rhs.dw)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

class Tripper {
public:
  Tripper(Road *roads, int numRoads, int size);
  int findPath(int city1, int city2, int path[], int *pathCount);
  ~Tripper();
private:
  vertice **adjacency_list;
  BinaryHeap<vertice1> heap;
}; // class Tripper



#endif	/* _TRIPPER_H */
