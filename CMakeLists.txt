cmake_minimum_required(VERSION 3.5)
project(TcpServer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)


# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -include header/per_IncludeMcuLibConfig.h")

# Define the directory containing the header file
set(MCU_SOURCE_DIR ${CMAKE_SOURCE_DIR}/header/mcuLib/src)
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/header)

include_directories(header header/mcuLib header/mcuLib/src header/mcuLib/config header/mcuLib/fonts header/mcuLib/config/fonts)

# Collect all .c files in the source directory
file(GLOB SOURCE_FILES ${MCU_SOURCE_DIR}/*.c)
# Add missing source file explicitly if it is not included in the glob
list(APPEND SOURCE_FILES header/mcuLib/src/McuGenericI2C.c)  # Add this line

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
    header/mcuLib/src/McuSSD1306.c
    header/mcuLib/src/McuGenericI2C.c
    header/mcuLib/src/McuWait.c # Include the file with McuWait_Waitms
   
)
#${SOURCE_FILES}

target_link_libraries(EmbLinux_Project ${GPIOD_LIBRARIES})


# Debug
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -include ${HEADER_DIR}/per_IncludeMcuLibConfig.h")
#target_compile_options(EmbLinux_Project PRIVATE "-include ${HEADER_DIR}/per_IncludeMcuLibConfig.h")
