cmake_minimum_required(VERSION 3.20)
project(SatelliteTracker)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(SatelliteTracker
        main.cpp
        src/SDLRenderer.cpp
        src/MapRenderer.cpp
)

target_link_libraries(SatelliteTracker PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)








