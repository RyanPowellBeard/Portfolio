# OpenGL Sphere Visualization

A 3D rotating sphere rendered in OpenGL using C++. The sphere is constructed from triangles and rotates continuously on all three axes.

## Features

- **Real-time 3D rendering** using OpenGL
- **Dynamic sphere** generated from triangle primitives
- **Smooth rotation animation** on X, Y, and Z axes
- **Depth testing** for proper 3D rendering
- **Window resizing support** with automatic viewport adjustment

## Requirements

- **C++11** or later
- **OpenGL 3.0+**
- **GLFW 3.x** - Window and input management
- **GLEW** - OpenGL Extension Wrangler Library

## Dependencies

Install required libraries on your system:

### Ubuntu/Debian
```bash
sudo apt-get install libglfw3-dev libglew-dev libgl1-mesa-dev
```

### macOS (with Homebrew)
```bash
brew install glfw3 glew
```

### Windows (MSVC)
Download pre-compiled binaries from:
- GLFW: https://www.glfw.org/download.html
- GLEW: http://glew.sourceforge.net/

## Building

### Linux/macOS
```bash
g++ -std=c++11 main.cpp -o sphere -lglfw -lGLEW -lGL -lGLU
```

### Windows (Visual Studio)
Link against: `glfw3.lib`, `glew32.lib`, `opengl32.lib`

## Running

```bash
./sphere
```

The window will open and display a rotating light blue sphere on a black background. Close the window to exit.

## How It Works

### Sphere Generation
The sphere is created by:
1. Iterating through latitude angles (0° to 180°)
2. Iterating through longitude angles (0° to 360°)
3. Creating triangles between adjacent angular points
4. Using spherical coordinates to calculate vertex positions

### Rendering Pipeline
- **Display function**: Clears buffers and calls render
- **Render function**: Sets up camera, applies rotations, and draws the sphere
- **Idle function**: Updates rotation angles each frame (0.1° per frame)
- **Reshape callback**: Handles window resizing and updates projection matrix

## Controls

- **Close window** - Exit the application
- No keyboard/mouse input currently implemented

## Performance Notes

- **Angle increment**: 10° (36×18 = 648 triangles)
- **Rotation speed**: 0.1° per frame (~36 FPS at 60Hz = 6°/second)

For finer detail, reduce the angle increment in `sphere()` function (currently 10°).

## Project Structure

```
├── README.md
├── main.cpp          # Main source file with complete implementation
└── sphere            # Compiled executable (after building)
```

## Future Enhancements

- Add lighting and shading (Phong/Gouraud)
- Enable user interaction (mouse/keyboard controls)
- Add normal vectors for better lighting
- Implement multiple rendering modes
- Add texture mapping

## License

This is a portfolio project. Feel free to use and modify as needed.
