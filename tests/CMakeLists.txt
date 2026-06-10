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
    ${CMAKE_SOURCE_DIR}/src/waveform.cpp
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