INCLUDE_DIRECTORIES(/home/dbaston/dev/postgis/liblwgeom)
LINK_DIRECTORIES(/home/dbaston/dev/postgis/liblwgeom/.libs)

cmake_minimum_required(VERSION 3.5)
project(lwgeom_boost)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lwgeom_boost ${SOURCE_FILES})

target_link_libraries(lwgeom_boost lwgeom)
