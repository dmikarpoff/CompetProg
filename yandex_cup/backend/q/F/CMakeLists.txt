cmake_minimum_required(VERSION 3.5)

project(backend_F LANGUAGES CXX)

find_package(CURL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(backend_F main.cpp)

target_link_libraries(backend_F CURL::libcurl)
