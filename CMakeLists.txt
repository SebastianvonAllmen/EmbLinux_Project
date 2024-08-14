cmake_minimum_required(VERSION 3.5)
project(TcpServer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

include_directories(header header/mcuLib/src header/mcuLib/config header/mcuLib/fonts header/mcuLib/config/fonts)

add_executable(EmbLinux_Project 
    main.c 
    source/gpio_control.c 
    source/per_display.c 
    source/tcp_helper.c 
    source/step_init.c 
    source/step_idle.c 
    header/mcuLib/src/McuI2cLib.c
    header/mcuLib/src/McuSSD1306.c
    header/mcuLib/src/McuGDisplaySSD1306.c
    header/mcuLib/src/McuFontDisplay.c
    header/mcuLib/fonts/McuFontHelv10Normal.c
    header/mcuLib/fonts/McuFontHelv12Normal.c
    header/mcuLib/fonts/McuFontHelv18Bold.c
)

target_link_libraries(EmbLinux_Project ${GPIOD_LIBRARIES})

# Debug
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")