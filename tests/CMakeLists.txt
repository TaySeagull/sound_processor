# DOWNLOAD CATCH 2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

include(Catch) 

# EXECUTABLE
add_executable(sound_processor_tests
    test_waveform.cpp
    test_wav_reader.cpp
    test_wav_writer.cpp
    test_args_parser.cpp
    test_pipeline.cpp
    test_ampl_filter.cpp
    test_timestretch_filter.cpp
    test_sin_gen_filter.cpp
    test_silence_filter.cpp
    test_am_filter.cpp
    test_fm_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/waveform.cpp
    ${CMAKE_SOURCE_DIR}/src/wav_reader.cpp
    ${CMAKE_SOURCE_DIR}/src/wav_writer.cpp
    ${CMAKE_SOURCE_DIR}/src/argument_parser.cpp
    ${CMAKE_SOURCE_DIR}/src/pipeline.cpp
    ${CMAKE_SOURCE_DIR}/src/ampl_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/timestretch_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/sin_gen_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/silence_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/am_filter.cpp
    ${CMAKE_SOURCE_DIR}/src/fm_filter.cpp
)

# LINK BETWEEN CATCH 2 AND CODE
target_link_libraries(sound_processor_tests PRIVATE 
    Catch2::Catch2WithMain 
)

# TERGET
target_include_directories(sound_processor_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# CTEST
include(CTest)
catch_discover_tests(sound_processor_tests)