# Macro to set up many things at once for a given GDExtension
function(godot_configure_library TARGET)
    # Define DEBUG macro
    target_compile_definitions(${TARGET} PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

    # Set optimization flags
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        # Build with debug friendly optimizations and debug symbols (MSVC defaults are fine)
        if(UNIX OR MINGW)
            target_compile_options(${TARGET} PRIVATE -Og -g)
        endif()
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT MSVC)
            target_compile_options(${TARGET} PRIVATE -fno-limit-debug-info)
        endif()
    else()
        # Build with optimizations and don't omit stack pointer for debugging (MSVC defaults are fine)
        if(UNIX OR MINGW)
            target_compile_options(${TARGET} PRIVATE -O2 -fno-omit-frame-pointer)
        endif()
    endif()

    # Set output directory
    set(${TARGET}_OUT_DIR "${GDRML_BIN_DIR}/${TARGET}/${GDRML_LIB_DIR}")
    set_target_properties(${TARGET} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${${TARGET}_OUT_DIR}
            RUNTIME_OUTPUT_DIRECTORY ${${TARGET}_OUT_DIR})
    message(STATUS "${TARGET} output directory is set to \"${${TARGET}_OUT_DIR}\"")

    # Remove lib prefix on MinGW
    if(MINGW)
        set_target_properties(${TARGET} PROPERTIES PREFIX "")
    endif()

    # Set debug postfix
    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX "d")
    endif()

    # Copy template files
    if(NOT ((CMAKE_BUILD_TYPE MATCHES "Debug") OR (CMAKE_BUILD_TYPE MATCHES "Release")))
        message(FATAL_ERROR "Build type must be Debug or Release!")
    endif()
    add_custom_target(${TARGET}_gdextension SOURCES
            "${CMAKE_CURRENT_SOURCE_DIR}/res/bin/Debug.gdextension.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/res/bin/Release.gdextension.in")
    add_dependencies(${TARGET} ${TARGET}_gdextension)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/res/bin/${CMAKE_BUILD_TYPE}.gdextension.in" "${${TARGET}_OUT_DIR}/../${TARGET}.gdextension")

    # Link to helpers and godot-cpp
    target_link_libraries(${TARGET} PRIVATE ${PROJECT_NAME}_helpers godot::cpp)

    # Add to project target
    add_dependencies(${PROJECT_NAME} ${TARGET})
endfunction()
