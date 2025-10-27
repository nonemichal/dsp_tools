cmake_minimum_required(VERSION 4.1)

# Project name and languages
project(dsp_tools LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Enable compiler warnings
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow)

# List of library source files
set(LIB_SOURCES src/vector_csv.c)

# List of test source files
set(TEST_SOURCES tests/print_and_save.c)

# Build shared library
add_library(vector_csv SHARED ${LIB_SOURCES})
target_include_directories(vector_csv PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Build test executable
add_executable(print_and_save ${TEST_SOURCES})
target_include_directories(print_and_save PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(print_and_save PRIVATE vector_csv)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set_target_properties(
  vector_csv PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dsp_tools
                        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dsp_tools)
set_target_properties(print_and_save PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                ${CMAKE_BINARY_DIR}/tests)
