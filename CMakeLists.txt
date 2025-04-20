cmake_minimum_required(VERSION 3.20)

project(1830)
# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add the "cmake" directory to the module path so we can include files from it later on here.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()
include(Common)

add_executable(MAIN "src/main.cpp" "src/Game.cpp")
target_include_directories(MAIN PUBLIC "include")

# Sample invocation of the parse test file
# parse_test_file(FILENAME "${CMAKE_SOURCE_DIR}/test/Dir/File.cpp" INCLUDES "include" LIBRARIES MyLibrary)
