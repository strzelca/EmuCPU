cmake_minimum_required(VERSION 3.27)
project(EmuCPU C)

set(CMAKE_C_STANDARD 11)


add_executable(EmuCPU main.c
        lib/mem.c
        lib/mem.h
        lib/cpu.c
        lib/cpu.h
        lib/logicb.c
        lib/logicb.h
        lib/utils.c
        lib/utils.h
        lib/isa.c
        lib/isa.h)

target_link_libraries(EmuCPU m)