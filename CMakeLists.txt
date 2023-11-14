cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(vl53l1x_Altitude C CXX ASM)
set(CMAKE_C_STNDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_executable(vl53l1x_Altitude
  vl53l1_platform.c
  VL53L1X_api.c
  VL53L1X_calibration.c
  control.cpp
)

target_link_libraries(vl53l1x_Altitude
  hardware_i2c
  hardware_spi 
  hardware_pwm 
  hardware_uart 
  pico_stdlib
  pico_multicore)

pico_enable_stdio_usb(vl53l1x_Altitude 1)
pico_enable_stdio_uart(vl53l1x_Altitude 0)

pico_add_extra_outputs(vl53l1x_Altitude)