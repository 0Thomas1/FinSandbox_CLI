cmake_minimum_required(VERSION 3.10)
project(FinSandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create the executable
add_executable(finsandbox ${SOURCES})
