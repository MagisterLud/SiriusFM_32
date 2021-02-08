cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")

set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")


project(SiriusFM)			

set(SOURCE main.cpp IRProviderConst.cpp prog.h)		

add_executable(prog ${SOURCE})	

target_link_libraries(prog)		