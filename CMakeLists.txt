cmake_minimum_required(VERSION 3.10)

project(Teriyaki VERSION 1.0)

configure_file(./lib/TeriyakiConfig.h.in ./lib/TeriyakiConfig.h)

#Define the entry point
add_executable(${PROJECT_NAME} main.cpp)
#Target the sources to be linked vvith.
target_include_directories(Teriyaki PUBLIC
                           "${PROJECT_BINARY_DIR}/lib"
                           )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)