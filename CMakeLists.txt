cmake_minimum_required(VERSION 3.10)
project(sound_processor LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# EXECUTABLE
add_executable(sound_processor
    src/main.cpp
    src/waveform.cpp
)

# TARGET
target_include_directories(sound_processor PRIVATE 
    src
    include
)

# TESTING
enable_testing()
add_subdirectory(tests)