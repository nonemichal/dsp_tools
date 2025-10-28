cmake_minimum_required(VERSION 4.1)

# Project name and languages
project(dsp_tools LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Enable compiler warnings
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow)

# Library sources
set(LIB_SOURCES src/vector_csv.c src/vector_complex.c src/fourier.c)

# Build shared library
add_library(dsp_tools SHARED ${LIB_SOURCES})
target_include_directories(dsp_tools PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(dsp_tools PRIVATE m)

# Generate compile_commands.json for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only build tests in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # Get all test source files recursively in tests/ folder
  file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.c")

  foreach(test_file ${TEST_SOURCES})
    # Get filename without path and extension
    get_filename_component(test_name ${test_file} NAME_WE)

    # Create an executable for each test file
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${test_name} PRIVATE dsp_tools m)

    # Output directory for tests
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                  ${CMAKE_BINARY_DIR}/tests)
  endforeach()
endif()
