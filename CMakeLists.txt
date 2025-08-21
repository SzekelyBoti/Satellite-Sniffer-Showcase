cmake_minimum_required(VERSION 4.0)
project(cpp_satelite_sniffer_cpp_kristofNyikes)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
include_directories(src)

add_executable(cpp_satelite_sniffer_cpp_kristofNyikes main.cpp
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
        include/PyEphemConverter.h
        include/GPSPosition.h
        include/UpdateManager.h
        include/UpdateMode.h
        include/UIController.h
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
        src/PyEphemConverter.cpp
        src/GPSPosition.cpp
        src/UpdateManager.cpp
        src/UIController.cpp
)
