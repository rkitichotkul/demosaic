cmake_minimum_required(VERSION 3.10)
project(demosaic)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS} include)

# Find LibRaw
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(LibRaw REQUIRED)

# Add source files for main_rawgen
add_executable(main_rawgen
    app/main_rawgen.cpp
    src/image_io.cpp
    src/bayer_pattern.cpp
)

# Add source files for main_loadraw
add_executable(main_loadraw
    app/main_loadraw.cpp
    src/image_io.cpp
    src/bayer_pattern.cpp
)

# Link OpenCV and LibRaw libraries
target_link_libraries(main_rawgen ${OpenCV_LIBS} ${LIBRAW_LIBRARIES})
target_link_libraries(main_loadraw ${OpenCV_LIBS} ${LIBRAW_LIBRARIES})