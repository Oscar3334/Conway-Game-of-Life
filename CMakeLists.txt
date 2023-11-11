cmake_minimum_required(VERSION 3.5)
project(ConwayGameOfLife)

add_compile_options(-Wall -Wno-sign-compare -O3 -std=c++20)
find_package(SDL2 REQUIRED)

add_executable(conway main.cpp grid.cpp camera.cpp)

target_include_directories(conway PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(conway PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(conway PRIVATE ${SDL2_LIBRARIES} SDL2main SDL2)
