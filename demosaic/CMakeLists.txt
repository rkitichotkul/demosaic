cmake_minimum_required(VERSION 3.10)
project(demosaic)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS} include)

# Add source files
add_executable(main_rawgen
    app/main_rawgen.cpp
    src/image_io.cpp
    src/bayer_pattern.cpp
)

# Link OpenCV libraries
target_link_libraries(main_rawgen ${OpenCV_LIBS})