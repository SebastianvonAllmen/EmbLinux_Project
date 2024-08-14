cmake_minimum_required(VERSION 3.5)
project(TcpServer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

include_directories(header)

add_executable(EmbLinux_Project main.c 
    source/gpio_control.c 
    source/tcp_helper.c 
    source/step_init.c 
    source/step_idle.c 
    source/step_search.c 
    source/step_choose.c
    source/step_stop.c
)

target_link_libraries(EmbLinux_Project ${GPIOD_LIBRARIES})

# Debug
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")