cmake_minimum_required(VERSION 3.5)
project(TcpServer)

# Find and link libgpiod
find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

# Find and link libmicrohttpd
pkg_check_modules(MICROHTTPD REQUIRED libmicrohttpd)

# Include directories
include_directories(header ${GPIOD_INCLUDE_DIRS} ${MICROHTTPD_INCLUDE_DIRS})

# Add the executable
add_executable(EmbLinux_Project 
    main.c 
    source/tcp_helper.c 
    source/step_controller.c
    source/rest_controller.c
    source/file_helper.c
    source/per_axis.c
)

# Link the necessary libraries
target_link_libraries(EmbLinux_Project ${GPIOD_LIBRARIES} ${MICROHTTPD_LIBRARIES} pthread)

# Debugging flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
