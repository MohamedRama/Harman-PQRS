cmake_minimum_required(VERSION 3.10)
project(VideoProcessorCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

# --- Include directories ---
include_directories(
    ${PROJECT_SOURCE_DIR}/include     # for VideoProcessor.hpp
    ${PROJECT_SOURCE_DIR}             # for Constants.hpp, Logger.hpp
    ${OpenCV_INCLUDE_DIRS}            # OpenCV headers
)

set(SRC
    src/main.cpp
    src/VideoProcessor.cpp
)

add_executable(video_processor_cpp ${SRC})

target_link_libraries(video_processor_cpp PRIVATE ${OpenCV_LIBS})

add_executable(TestsVideoProcessor
    tests/TestsVideoProcessor.cpp
    src/VideoProcessor.cpp
)

target_link_libraries(TestsVideoProcessor PRIVATE ${OpenCV_LIBS})
