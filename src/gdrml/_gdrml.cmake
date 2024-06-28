add_library(godrml SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_gdrml.cpp"
        
        # Interfaces
        "${CMAKE_CURRENT_LIST_DIR}/GDRenderInterface.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDRenderInterface.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDSystemInterface.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDSystemInterface.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDFileInterface.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDFileInterface.hpp"

        # GDScript Bindings/Support
        "${CMAKE_CURRENT_LIST_DIR}/RmlUIGD.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/RmlUIGD.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDScriptEventListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDScriptEventListener.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDScriptEventListenerInstancer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/GDScriptEventListenerInstancer.hpp"

        # Nodes & Singletons
        "${CMAKE_CURRENT_LIST_DIR}/RmlUIController.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/RmlUIController.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/RmlNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/RmlNode.hpp"
)

# add rmlui library
find_package(RmlUi REQUIRED)

target_link_libraries(godrml PRIVATE RmlCore RmlDebugger)

gdrml_configure_library(godrml)
