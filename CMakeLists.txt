cmake_minimum_required(VERSION 3.5)

project(CPP-2020-2021-HW11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CPP-2020-2021-HW11 main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(CPP-2020-2021-HW11 Threads::Threads)
