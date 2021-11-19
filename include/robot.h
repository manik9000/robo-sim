#ifndef ROBOT_H_
#define ROBOT_H_


#include "world.h"
#include "common.h"
#include "renderer.h"


// Forward declaration
class World;

// Define and implement the following class
class Robot {
 public:
   Pose currentPose;
   int r,g,b;

   Robot(int x, int y, Heading heading, std::string name);
   Robot(Pose pose, std::string name);
   void setRobotcolor(int r, int g, int b){ r=r; g=g;  b=b;}
   bool setRobotName(std::string name);
   std::string getRobotName();

private:
  std::string robotName;

};
#endif
