if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CMake libraries
include(CheckIPOSupported)

# Set up variables
set(GDRML_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if (APPLE)
    set(GDRML_ARCH "universal")
endif()

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
    check_ipo_supported(RESULT GDRML_USE_LTO)
endif()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${GDRML_USE_LTO})
