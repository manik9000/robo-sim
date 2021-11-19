#ifndef COMMON_H_
#define COMMON_H_

#include <string>

struct Point{
  int x,y;
};

enum Heading {up, down, left, right} ;

struct Pose{
  int x,y =0;
  Heading heading = up;
};



#endif
