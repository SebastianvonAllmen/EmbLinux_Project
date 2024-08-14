cmake_minimum_required(VERSION 3.5)
project(TcpServer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

include_directories(header)

add_executable(EmbLinux_Project main.c scource/gpio_control.c)

target_link_libraries(EmbLinux_Project ${GPIOD_LIBRARIES})

# Debug
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")