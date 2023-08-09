cmake_minimum_required(VERSION 3.24)
project(MCU_Common_Code C)

set(CMAKE_C_STANDARD 11)

add_executable(
        MCU_Common_Code main.c
        sushizhou_common/su_common_fifo.h
        sushizhou_common/su_common_fifo.c
        sushizhou_common/su_common_typedef.h
        )
