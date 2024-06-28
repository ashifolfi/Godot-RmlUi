add_library(${PROJECT_NAME}_helpers STATIC
        "${CMAKE_CURRENT_LIST_DIR}/Conversion.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Conversion.h")

target_link_libraries(${PROJECT_NAME}_helpers PRIVATE godot::cpp)

target_include_directories(${PROJECT_NAME}_helpers PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
