#include "robot.h"
#include <iostream>


/*
There are two ways we can initialize robot. Following two functions
*/

Robot::Robot(Pose pose, std::string name) {
  Robot(pose.x, pose.y, pose.heading, name);
}

Robot::Robot(int x, int y, Heading heading, std::string name){
  currentPose.x=x;
  currentPose.y=y;
  currentPose.heading = heading;
  setRobotName(name);
 }

bool Robot::setRobotName(std::string name)
  {robotName = name; return true;}

std::string Robot::getRobotName(){ return robotName;}
