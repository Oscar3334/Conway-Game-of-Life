cmake_minimum_required(VERSION 3.5)
project(ConwayGameOfLife)

find_package(SDL2 REQUIRED)

add_executable(conway main.cpp)

target_include_directories(conway PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(conway PRIVATE ${SDL2_LIBRARIES} SDL2main SDL2)
