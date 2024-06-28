# Godot RmlUi
A GDExtension port of RmlUi to Godot 4.2+



**Current Progress:**
- Basic rendering on Canvas layers
- Integration with Godot Filesystem
- Texture support via Godot Texture Resource
- Full input via `_gui_input`
- Event binding in GDScript
- Inline GDScript in RML files
- Support for translating strings using Godot's Translation System

**ToDo:**
- GDScript Element Modification
- Integration with Godot Font System
- Editor Document rendering and modification

## Screenshots

![](.github/screenshots/3ddemo.png)
![](.github/screenshots/2ddemo.png)

## Build Instructions

### Prerequisites
- CMake 3.25+
- vcpkg
- Godot 4.2+
- git

### Windows

#### Visual Studio
- Clone the project and its submodules
- Open the directory as a CMake project within Visual Studio
- Build `godrml.dll`

That is all.

#### CLion
TODO

### macOS
TODO

### Linux
TODO