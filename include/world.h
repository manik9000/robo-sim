#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <vector>
#include <utility>

#include "robot.h"
#include "common.h"
#include "renderer.h"


// Forward declaration
class Robot;
class Renderer;

// Define and implement the following class. Feel free to change the given
// interfaces and data structures to better match your design
class World {

 public:
  World(std::vector<std::vector<int>>& map, int ScreenHeight, int ScreenWidth);
  bool addRobot(int row, int col, int r, int g, int b, std::string name);
  bool moveRobot(Robot &robot);

  std::vector<Point> static_obstacleList;
  std::vector<Robot> robots;
  Pose getRobotLocation(std::string name);

  void updateRobotLocations(std::string& name, Pose& pose_);


 private:
  void populateObstacles();
  std::vector<std::vector<int>> map_;
  std::map<std::string, Pose> robotLocations;
  int ScreenWidth_;
  int ScreenHeight_;


};

#endif
