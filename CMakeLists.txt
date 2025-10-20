cmake_minimum_required(VERSION 3.20)
project(SatelliteTracker)

set(CMAKE_CXX_STANDARD 20)

# ================= SDL2 =================
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

# ================= SGP4 =================
find_library(SGP4_LIBRARY NAMES sgp4 libsgp4)
if(SGP4_LIBRARY)
    message(STATUS "Found system libsgp4: ${SGP4_LIBRARY}")
else()
    message(STATUS "Using local libsgp4")
    add_subdirectory(include/sgp4/libsgp4)
    set(SGP4_LIBRARY sgp4)
endif()

# ================= Library =================
add_library(satellite_lib
        include/Application.h
        include/IRenderer.h
        include/SDLRenderer.h
        include/MapRenderer.h
        include/SatelliteRenderer.h
        include/SatelliteIcon.h
        include/EarthMap.h
        include/TLEParser.h
        include/SatelliteData.h
        include/Satellite.h
        include/SatelliteManager.h
        include/TLEtoGPSConverter.h
        include/GPSPosition.h
        include/UpdateManager.h
        include/UpdateMode.h
        include/SGP4Converter.h
        include/UIManager.h
        include/RenderableAsset.h

        src/Application.cpp
        src/SDLRenderer.cpp
        src/MapRenderer.cpp
        src/SatelliteRenderer.cpp
        src/SatelliteIcon.cpp
        src/EarthMap.cpp
        src/TLEParser.cpp
        src/SatelliteData.cpp
        src/Satellite.cpp
        src/SatelliteManager.cpp
        src/GPSPosition.cpp
        src/UpdateManager.cpp
        src/SGP4Converter.cpp
        src/UIManager.cpp
        src/ReadableAsset.cpp
)

target_include_directories(satellite_lib
        PUBLIC
        include
        include/sgp4/libsgp4
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(satellite_lib
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        ${SGP4_LIBRARY}
)

# ================= Executable =================
add_executable(SatelliteTracker main.cpp)
target_link_libraries(SatelliteTracker PRIVATE satellite_lib)

# ================= GoogleTest =================
enable_testing()
add_subdirectory(googletest)

add_subdirectory(tests)
