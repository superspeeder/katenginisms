cmake_minimum_required(VERSION 3.20)

add_executable(testapp main.cpp main.h)
target_include_directories(testapp PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(testapp katengine)