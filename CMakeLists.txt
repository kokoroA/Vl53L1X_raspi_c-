cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Altitude_kalman C CXX ASM)
set(CMAKE_C_STNDARD 11)
set(CMAKE_CXX_STANDARD 17)

# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_executable(Altitude_kalman
  test.c
  vl53l1_platform.c
  VL53L1X_api.c
  VL53L1X_calibration.c
)

target_link_libraries(Altitude_kalman
  hardware_i2c
  hardware_spi 
  hardware_pwm 
  hardware_uart 
  pico_stdlib
  pico_multicore)

pico_enable_stdio_usb(Altitude_kalman 1)
pico_enable_stdio_uart(Altitude_kalman 0)

pico_add_extra_outputs(Altitude_kalman)