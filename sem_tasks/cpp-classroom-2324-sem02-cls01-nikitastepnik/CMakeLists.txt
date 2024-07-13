cmake_minimum_required (VERSION 3.8)

project(clw-01)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O1 -g -fsanitize=address -fno-omit-frame-pointer")
endif()

add_executable(task-worker src/task_1/test.cpp)
add_executable(task-vector src/task_2/test.cpp)
add_executable(task-logger src/task_3/test.cpp)
