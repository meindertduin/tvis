cmake_minimum_required(VERSION 3.20.5)

project(tvis)
set(CMAKE_CXX_STANDARD 20)
set(tvis_version 0.1)

set(PROJECT_VERSION ${tvis_version})
project(${PROJECT_NAME} VERSION ${tvis_version} LANGUAGES CXX C)
set(SOURCES src/main.cpp src/pulseaudio/PaSource.cpp src/BarSpectrumDataTransformer.cpp)
set(HEADERS src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -D__extern_always_inline=inline -D_XOPEN_SOURCE_EXTENDED")

include_directories(src)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER})
target_link_libraries(${PROJECT_NAME} pulse-simple pulse fftw3)
