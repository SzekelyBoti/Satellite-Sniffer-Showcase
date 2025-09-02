cmake_minimum_required(VERSION 4.0)
project(cpp_satelite_sniffer_cpp_kristofNyikes)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
include_directories(src)
include_directories(include/sgp4/libsgp4)

find_library(SGP4_LIBRARY NAMES sgp4 libsgp4)
if(SGP4_LIBRARY)
    message(STATUS "Found system libsgp4: ${SGP4_LIBRARY}")
else()
    message(STATUS "Using local libsgp4")
    add_subdirectory(include/sgp4/libsgp4)
    set(SGP4_LIBRARY sgp4)
endif()

add_executable(cpp_satelite_sniffer_cpp_kristofNyikes
        main.cpp

        include/Application.h
        include/IRenderer.h
        include/SDLRenderer.h
        include/RenderEngine.h
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
        include/UIController.h
        include/SGP4Converter.h

        src/Application.cpp
        src/SDLRenderer.cpp
        src/RendererEngine.cpp
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
        src/UIController.cpp
        src/SGP4Converter.cpp
)

if(SGP4_LIBRARY)
    target_link_libraries(cpp_satelite_sniffer_cpp_kristofNyikes ${SGP4_LIBRARY})
else()
    target_link_libraries(cpp_satelite_sniffer_cpp_kristofNyikes sgp4)
endif()

target_include_directories(cpp_satelite_sniffer_cpp_kristofNyikes PRIVATE
        include
        src
        include/sgp4/libsgp4
)

