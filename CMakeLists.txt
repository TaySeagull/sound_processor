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
    src/cmd_line_args_2_pipeline_converter.cpp
    src/application.cpp
    src/filters/ampl_filter.cpp
    src/filters/timestretch_filter.cpp
    src/filters/silence_filter.cpp
    src/filters/generator_filter.cpp
    src/filters/normalize_filter.cpp
    src/filters/lowpass_filter.cpp
    src/filters/filter_producers.cpp
)

# TARGET
target_include_directories(sound_processor PRIVATE 
    src
    include
)

# TESTING
enable_testing()
add_subdirectory(tests)