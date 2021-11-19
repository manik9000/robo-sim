#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>

#include <iostream>
#include <random>
#include <thread>
#include <time.h>


#include "robot.h"
#include "world.h"
#include "renderer.h"
#include "randomcolor.h"



void moveRobotThread(World& world, Robot& robot){
  bool success = world.moveRobot(robot);
  if(success){
    // get robot locations data in world
    Pose pose__ = world.getRobotLocation("A");
  }
}


int main(int argc, char** argv) {
  // You should customize this data structure and the World constructor to
  // match your chosen data structure.
  // int map[7][7] = {
  //   {1, 1, 1, 1, 1, 1, 1},
  //   {1, 0, 0, 0, 0, 0, 1},
  //   {1, 0, 0, 0, 0, 0, 1},
  //   {1, 0, 0, 1, 1, 0, 1},
  //   {1, 0, 0, 1, 1, 0, 1},
  //   {1, 0, 0, 0, 0, 0, 1},
  //   {1, 1, 1, 1, 1, 1, 1},
  // };

  int numberOfRobots = 3;

  std::vector<std::vector<int>> map = {
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };




  // setup graphics
  SDL_Event event;
  const std::size_t FramesPerSecond{60};
  const std::size_t MsPerFrame{1000 / FramesPerSecond};
  const std::size_t ScreenWidth{640};
  const std::size_t ScreenHeight{640};
  const std::size_t mapWidth = map.size();
  const std::size_t mapHeight = map[0].size();

  World world(map,ScreenWidth, ScreenHeight);

  // populate the obstacleList -- boundry = obstacle

  Renderer renderer(ScreenWidth, ScreenHeight, mapWidth, mapHeight);
  renderer.setObstacleList(world.static_obstacleList);


  std::vector<std::string> nameLookupTable = {"A","B","C","D","E","F","G","H","I","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

  RandomColor randomColor;

  bool quit = false;

  // add robots to our world map
  for(int i=0;i<numberOfRobots;i++){
      std::random_device dev; // obtain a random number from hardware
      std::mt19937 engine(dev()); // seed the generator
      std::uniform_int_distribution<> random_w(1, static_cast<int>(mapWidth - 2)); // define the range
      std::uniform_int_distribution<> random_h(1, static_cast<int>(mapHeight - 2)); // define the range

      //random initialization for robot location
      int x = random_w(engine);
      int y = random_h(engine);

      //
      int r = randomColor.generate();
      int g = randomColor.generate();
      int b = randomColor.generate();

      std::string robotName = nameLookupTable[i];
      world.addRobot(x,y, r,g,b, robotName);
    }

  while(quit == false){
    //Handle events on queue
    while( SDL_PollEvent( &event ) != 0 )
    {
        //User requests quit
        if( event.type == SDL_QUIT || event.type == SDL_KEYDOWN )
        {
            quit = true;
        }
        // do the intended function
        else{

          //spawn robot
          renderer.RenderRobots(world.robots);

          // move each robot in or map every 1 second
          std::thread thread1(moveRobotThread, std::ref(world),std::ref(world.robots[0]));
          std::thread thread2(moveRobotThread, std::ref(world),std::ref(world.robots[1]));
          std::thread thread3(moveRobotThread, std::ref(world),std::ref(world.robots[2]));

          thread1.join();
          thread2.join();
          thread3.join();

          sleep(1);
      }
    }
  }
	renderer.clean_up();
  return 0;
}
