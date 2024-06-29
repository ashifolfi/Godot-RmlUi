cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Create project
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
endif()
project(godotrmlui
        VERSION "0.1.0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CMake libraries
include(CheckIPOSupported)

# Set up variables
set(GDRML_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if (APPLE)
    set(GDRML_ARCH "universal")
endif()
set(GDRML_ADDON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/project/addons/${PROJECT_NAME}")
set(GDRML_BIN_DIR "${GDRML_ADDON_DIR}/bin")
set(GDRML_LIB_DIR "${CMAKE_SYSTEM_NAME}_${GDRML_ARCH}")

# Global CMake options
if(NOT PROJECT_IS_TOP_LEVEL)
    message(FATAL_ERROR "${PROJECT_NAME} must be built standalone!")
endif()

# Print a message
message(STATUS "Building ${PROJECT_NAME} for ${GDRML_ARCH} on ${CMAKE_SYSTEM_NAME}")

# Set proper runpath
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_INSTALL_RPATH $ORIGIN)

# Compile with PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compile with LTO if supported
set(GDRML_USE_LTO OFF)
if(NOT (CMAKE_BUILD_TYPE MATCHES "Debug"))
    check_ipo_supported(RESULT GODOTSOURCE_USE_LTO)
endif()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${GDRML_USE_LTO})

# Hide everything by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

include(cmake/CPM.cmake)

CPMAddPackage(
    GITHUB_REPOSITORY godotengine/godot-cpp
    GIT_TAG godot-4.2.2-stable
    OPTIONS
    "GODOT_CPP_SYSTEM_HEADERS ON"
)

include(cmake/gdextension.cmake)

CPMAddPackage(
    GITHUB_REPOSITORY mikke89/RmlUi
    GIT_TAG 5.1
    OPTIONS
    "RMLUI_FONT_ENGINE none"
    "NO_FONT_INTERFACE_DEFAULT ON"
)

add_custom_target(${PROJECT_NAME})

# Static helpers library
include("${CMAKE_CURRENT_SOURCE_DIR}/src/_helpers/_helpers.cmake")

include("${CMAKE_CURRENT_SOURCE_DIR}/src/gdrml/_gdrml.cmake")

# Configure plugin config
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/res/plugin.cfg.in" "${GDRML_ADDON_DIR}/plugin.cfg")
