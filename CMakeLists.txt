cmake_minimum_required(VERSION 3.10)
project(sound_processor LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# EXECUTABLE
add_executable(sound_processor
    src/main.cpp
    src/waveform.cpp
    src/wav_reader.cpp
    src/wav_writer.cpp
    src/argument_parser.cpp
    src/pipeline.cpp
    src/ampl_filter.cpp
    src/timestretch_filter.cpp
    src/silence_filter.cpp
    src/sin_gen_filter.cpp
    src/am_filter.cpp
    src/fm_filter.cpp
    src/cmd_line_args_2_pipeline_converter.cpp
    src/filter_producers.cpp
    src/application.cpp
)

# TARGET
target_include_directories(sound_processor PRIVATE 
    src
    include
)

# TESTING
enable_testing()
add_subdirectory(tests)