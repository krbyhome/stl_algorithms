cmake_minimum_required(VERSION 3.0.0)
project(lab11 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories ("${PROJECT_SOURCE_DIR}/lib")

enable_testing()
add_subdirectory(tests)