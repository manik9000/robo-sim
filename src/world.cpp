#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <thread>
#include <random>
#include <chrono>
#include <iostream>
#include <string>

#include "world.h"
#include "SDL.h"
#include "common.h"


/*
this function setsup our visualizer
*/
World::World(std::vector<std::vector<int>>& map, int ScreenWidth, int ScreenHeight) {
  ScreenWidth_ = ScreenWidth;
  ScreenHeight_ = ScreenHeight;

  map_ = map;
  populateObstacles();

}

/*
  This Function reads the provided map - a 2D array and populate obstacles into a list.
  Assumption - in given map, any valuse other than a 0 represents a obstacle
  Note that there are some parameters like block_h, block_w that are used to handle the graphics visualization.
*/
void World::populateObstacles(){
  Point obstacle;

  int mapWidth = map_.size();
  int mapHeight = map_[0].size();

  double block_w = (ScreenWidth_ / mapWidth);
  double block_h = (ScreenHeight_ / mapHeight);
  for(int i=0; i<mapWidth; i++){
    for(int j=0; j<mapHeight; j++){
      if(map_[i][j]!=0){
        Point obstacle;
        obstacle.x = j*block_w;
        obstacle.y = i*block_h;
        static_obstacleList.push_back(obstacle);
      }
    }
  }

}

/*
This function creates and adds a robot in the map
*/

bool World::addRobot(int row, int col, int r, int g, int b, std::string name) {
  // map_[row][col] = 'A';
  Robot robot(row,col,up, name);
  robot.setRobotcolor(r,g,b);

  // this list gets updated every time move function is called
  robots.push_back(robot);

  // this gets updated only when thr move is successful
  robotLocations.insert(std::make_pair<std::string&, Pose&>(name,robot.currentPose));

  return true;
}


/*
This function is responsible for moving the robot in our map.
If the move is not successful then this function changes the heading of the robot
by randomly assigning one direction out of 4 options.

if move is successful then it updates the robotCurrentLocation database.
*/
bool World::moveRobot(Robot& robot){

  // for(std::map<std::string, Pose>::const_iterator it = robotLocations.begin();
  //   it != robotLocations.end(); ++it)
  //   {
  //       std::cout << it->first << " " << it->second.x << " " << it->second.y << "\n";
  //   }


  Pose new_pose;
  //make potential move
  if(robot.currentPose.heading == up){
    new_pose = robot.currentPose;
    new_pose.y++;
  }
  if(robot.currentPose.heading == down){
    new_pose = robot.currentPose;
    new_pose.y--;
  }
  if(robot.currentPose.heading == left){
    new_pose = robot.currentPose;
    new_pose.x++;
  }
  if(robot.currentPose.heading == right){
    new_pose = robot.currentPose;
    new_pose.x--;
  }

  //if new pose is within map
  if(new_pose.x < map_[0].size() && new_pose.x >= 0 &&
     new_pose.y < map_[0].size() && new_pose.y >= 0){
       // if new_pose is not obstacle
       if(map_[new_pose.y][new_pose.x]!=1){
         robot.currentPose = new_pose;

         std::string name = robot.getRobotName();

         updateRobotLocations(name, new_pose);

         return true;
       }
       else{
         std::cout<<"Changing Direction"<<std::endl;
         //change the heading of robot
         static std::vector<Heading> ALL_DIRECTIONS({up, down, left, right});
         static std::random_device rd;
         static std::mt19937 gen(rd());
         std::uniform_int_distribution<size_t> dis(0, ALL_DIRECTIONS.size() - 1);
         new_pose.heading = ALL_DIRECTIONS[dis(gen)];
         robot.currentPose = robot.currentPose;
         robot.currentPose.heading = new_pose.heading;

         return false;
       }
     }


}

/*
This function returns the location of a robot in map.
*/
Pose World::getRobotLocation(std::string name){
  Pose pose_;

  std::map<std::string,Pose>::iterator itr;
  itr = robotLocations.find(name);
  if (itr != robotLocations.end()){
      // found
      std::cout<< "robot "<< name<< " Current position - \t";
      pose_ = itr->second;
      std::cout<< "("<< pose_.x <<", "
                     << pose_.y <<", "
                     << pose_.heading << ")"<<std::endl;
   }else{
      // not found
      std::cout<< "robot "<< name<< " not found..."<<std::endl;
  }
  return(pose_);
}

/*
This function updates the robot current location database
*/
void World::updateRobotLocations(std::string& name, Pose& pose_){
  std::map<std::string,Pose>::iterator itr;
  itr = robotLocations.find(name);
  if (itr != robotLocations.end()){
    itr->second = pose_;
   }

}
