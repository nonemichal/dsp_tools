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
set(LIB_SOURCES src/vector_csv.c)

# Build shared library
add_library(vector_csv SHARED ${LIB_SOURCES})
target_include_directories(vector_csv PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(
  vector_csv PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dsp_tools
                        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dsp_tools)

# Only build tests in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # Get all test source files in tests/ folder
  file(GLOB TEST_SOURCES "tests/*.c")

  foreach(test_file ${TEST_SOURCES})
    # Get filename without path and extension
    get_filename_component(test_name ${test_file} NAME_WE)

    # Create an executable for each test file
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${test_name} PRIVATE vector_csv)

    # Output directory for tests
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                  ${CMAKE_BINARY_DIR}/tests)
  endforeach()
endif()
