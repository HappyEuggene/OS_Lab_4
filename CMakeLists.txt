cmake_minimum_required(VERSION 3.27)
project(OS_Lab_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(OS_Lab_4 MemoryMonitor.cpp
        ProcessMemoryReader.cpp
        HOOK.cpp)
