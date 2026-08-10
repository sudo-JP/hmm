cmake_minimum_required(VERSION 3.21...3.25)
project(hmm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

find_package(Vulkan REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hmm
    src/main.cpp
)

target_link_libraries(hmm PRIVATE Vulkan::Vulkan)
