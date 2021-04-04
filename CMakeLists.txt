cmake_minimum_required(VERSION 3.10)

project(Teriyaki VERSION 1.0)


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(.)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(test)


include_directories(src)
include_directories(lib)
include_directories(test)

# # add_library(scanner-token)
# include_directories("${PROJECT_BINARY_DIR}/lib")
# add_subdirectory(lib)
# # target_link_libraries(${PROJECT_BINARY_DIR}/lib)
# #Define the entry point
# add_executable(${PROJECT_NAME} main.c)
# target_link_libraries(Teriyaki scanner-token)
# #Target the sources to be linked vvith.
# # include_directories(lib)


# # specify the C++ standard
# # set(CMAKE_CXX_STANDARD 11)
# # set(CMAKE_CXX_STANDARD_REQUIRED True)