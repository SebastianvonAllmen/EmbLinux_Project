cmake_minimum_required(VERSION 3.5)
project(TcpServer)

add_executable(TcpServer main.c)

# Debug
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")