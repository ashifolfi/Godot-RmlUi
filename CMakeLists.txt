cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Create project
project(godotrmlui
        VERSION "0.1.0"
)

include(cmake/boilerplate.cmake)

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
