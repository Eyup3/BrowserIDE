cmake_minimum_required(VERSION 3.23)
project(Editor C)

set(CMAKE_C_STANDARD 99)

add_executable(Editor main.c mynclib.h mynclib.c)
target_link_libraries(${PROJECT_NAME} -lncursesw)