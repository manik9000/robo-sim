cmake_minimum_required(VERSION 3.1)
project(roboagents)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package (Threads)
find_package(SDL2 REQUIRED)

include_directories(
  include/
  ${SDL2_INCLUDE_DIRS}
  src
)

add_executable(roboagents
  src/main.cpp
  src/robot.cpp
  src/world.cpp
  src/renderer.cpp
  src/randomcolor.cpp
)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries (roboagents ${CMAKE_THREAD_LIBS_INIT} ${SDL2_LIBRARIES})
