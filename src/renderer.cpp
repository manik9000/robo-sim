#include "renderer.h"
#include <iostream>
#include <string>
#include <vector>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height){

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Robot Simulator", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  // render obstacles
  RenderObstacles(obstacleList);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::setObstacleList(std::vector<Point> obstacleList_){
  obstacleList = obstacleList_;
}

// render robots
void Renderer::RenderRobots(std::vector<Robot> robots) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 00, 00, 00, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //render obstacles
  RenderObstacles(obstacleList);

  //render robots
  for (int k=0; k < robots.size(); k++){
    block.x = robots[k].currentPose.x*block.w;
    block.y = robots[k].currentPose.y*block.h;

    SDL_SetRenderDrawColor(sdl_renderer, robots[k].r, robots[k].g, robots[k].b, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &block);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

// render obstacles
void Renderer::RenderObstacles(std::vector<Point> obstacleList) {
  SDL_Rect block;
  block.w = (screen_width / grid_width);
  block.h = (screen_height / grid_height);

  for(auto obstacle : obstacleList){
    block.x = obstacle.x;
    block.y = obstacle.y;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &block);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


bool Renderer::clean_up() {
	SDL_Quit();
	return true;
}
