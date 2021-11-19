#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"
#include "robot.h"
#include "SDL.h"
#include <vector>
#include <string>

class Robot;

class Renderer {

 public:

  Renderer(const std::size_t screen_width, const std::size_t screen_height,
                    const std::size_t grid_width, const std::size_t grid_height);

  ~Renderer();

  void RenderObstacles(std::vector<Point> obstacleList);

  void setObstacleList(std::vector<Point> obstacleList_);

  void RenderRobots(std::vector<Robot> robots);

  bool clean_up();

  std::vector<Point> obstacleList;

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
