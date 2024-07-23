# Physics-Game-3D-Render-Engine-C++
## Overview

This project is a 3D engine implemented in C++. It demonstrates various computer graphics concepts, including rendering, lighting, and shadow mapping. The engine supports multiple types of lights, shaders, and textures, and includes a simple physics system for bounding volumes.

## Features

- **Rendering Engine**: Handles rendering of objects, applying shaders, and managing the rendering pipeline.
- **Lighting**: Supports ambient, directional, point, and spotlights with corresponding shaders.
- **Textures and Shaders**: Includes various shaders for different rendering effects and multiple textures for demonstration.
- **Physics**: Simple physics system for axis-aligned bounding boxes and bounding spheres.
- **Camera**: Includes implementations for free look and free move cameras.
- **Profiling**: Tools for profiling the performance of the engine.

## Getting Started

### Prerequisites

- A C++ compiler (GCC, Clang, MSVC)
- CMake
- Assimp, GLEW, and SDL2 libraries

### Building the Project

#### Unix

```bash
sh Unix-Build.sh
```

For a debug build:

```bash
sh Unix-BuildDebug.sh
```

To clean the build:

```bash

sh Unix-Clean.sh
```

#### windows

Double-click `Windows-GenVisualStudioProject.bat` to generate a Visual Studio project. Use `Windows-Clean.bat` to clean the build.

### Running the Project

After building, you can run the executable using:

```bash
./run
```

## Project Structure

### Root Directory

- `.gitattributes`, `.gitignore`: Git configuration files.
- `C++CodingStyleGuide.txt`: Coding style guide for C++.
- `CMakeLists.txt`: Main CMake configuration file.
- `LICENSE`: License file.
- `Makefile`: Makefile for building the project.
- `README.md`: This README file.
- `Unix-Build.sh`, `Unix-BuildDebug.sh`, `Unix-Clean.sh`, `Unix-GenCodeBlocksProject.sh`, `Unix-GitPull.sh`, `Unix-GitPush.sh`: Unix build and utility scripts.
- `Windows-Clean.bat`, `Windows-GenVisualStudioProject.bat`: Windows build and utility scripts.
- `run`: Executable file.

### `build/`

- `.gitignore`: Ensures build artifacts are not tracked by Git.

### `cmake/`

- `FindASSIMP.cmake`, `FindGLEW.cmake`, `FindSDL2.cmake`: CMake modules for dependencies.

### `lib/Assimp/include/assimp/`

- Assimp library headers.

### `res/shaders/`

- Various shader files for rendering effects (e.g., `filter-null.glsl`, `forward-ambient.glsl`).

### `res/textures/`

- Texture files used in the project (e.g., `bricks.jpg`, `defaultTexture.png`).

### `src/`

- `3DEngine.h`: Main engine header.
- `aabb.cpp`, `aabb.h`: Axis-Aligned Bounding Box collision detection.
- `boundingSphere.cpp`, `boundingSphere.h`: Bounding sphere collision detection.
- `camera.cpp`, `camera.h`: Camera functionality.
- `coreEngine.cpp`, `coreEngine.h`: Main game loop and engine core.
- `entity.cpp`, `entity.h`, `entityComponent.h`: Entity and component system.
- `freeLook.cpp`, `freeLook.h`: Free look camera control.
- `freeMove.cpp`, `freeMove.h`: Free move camera control.
- `game.cpp`, `game.h`: Game-specific logic.
- `input.cpp`, `input.h`: User input handling.
- `intersectData.h`: Intersection data for collision detection.
- `lighting.cpp`, `lighting.h`: Lighting effects.
- `main.cpp`: Application entry point.
- `mappedValues.cpp`, `mappedValues.h`: Mapped values for shaders.
- `material.cpp`, `material.h`: Material properties and textures.
- `math3d.cpp`, `math3d.h`: 3D mathematics (vectors, matrices).
- `mesh.cpp`, `mesh.h`: 3D model loading and management.
- `meshRenderer.h`: 3D mesh rendering.
- `profiling.cpp`, `profiling.h`: Performance profiling tools.
- `referenceCounter.h`: Reference counting.
- `renderingEngine.cpp`, `renderingEngine.h`: Rendering process and pipeline.
- `shader.cpp`, `shader.h`: Shader compilation and application.
- `simdaccel.h`, `simddefines.h`, `simdemulator.h`, `x86simdaccel.h`: SIMD acceleration and definitions.
- `stb_image.c`, `stb_image.h`: Image loading (stb_image library).
- `texture.cpp`, `texture.h`: Texture loading and management.
- `timing.cpp`, `timing.h`: Timing and frame rate management.
- `transform.cpp`, `transform.h`: Transformations (position, rotation, scale).
- `util.cpp`, `util.h`: Utility functions.
- `window.cpp`, `window.h`: Window management.

### Detailed Functions Overview

#### `3DEngine.h`

This file serves as the main header for the 3D engine, containing declarations for the core components.

- **Classes**:
  - `Engine`: The primary class managing the initialization, execution, and termination of the engine.
  - `EngineConfig`: Holds configuration parameters for the engine such as screen width, height, and title.

#### `aabb.cpp` and `aabb.h`

These files handle Axis-Aligned Bounding Box (AABB) collision detection.

- **Functions**:
  - `intersect(const AABB& other)`: Checks if this AABB intersects with another AABB.
  - `getMinExtents()`, `getMaxExtents()`: Get the minimum and maximum extents of the AABB.

#### `boundingSphere.cpp` and `boundingSphere.h`

These files handle bounding sphere collision detection.

- **Functions**:
  - `intersect(const BoundingSphere& other)`: Checks if this bounding sphere intersects with another bounding sphere.
  - `getCenter()`, `getRadius()`: Get the center and radius of the bounding sphere.

#### `camera.cpp` and `camera.h`

These files manage camera functionality.

- **Functions**:
  - `Camera()`: Constructor to initialize the camera.
  - `setPerspective()`, `setOrthographic()`: Set camera projection modes.
  - `getViewMatrix()`, `getProjectionMatrix()`: Get view and projection matrices.

#### `coreEngine.cpp` and `coreEngine.h`

These files contain the main game loop and engine core.

- **Functions**:
  - `start()`, `stop()`: Start and stop the engine.
  - `render()`, `update()`: Main render and update functions for the game loop.

#### `entity.cpp`, `entity.h`, and `entityComponent.h`

These files handle the entity-component system.

- **Functions**:
  - `addComponent(EntityComponent* component)`: Add a component to an entity.
  - `update()`, `render()`: Update and render the entity and its components.

#### `freeLook.cpp` and `freeLook.h`

These files implement the free look camera control.

- **Functions**:
  - `FreeLook()`: Constructor to initialize free look control.
  - `processInput()`: Process input for free look control.

#### `freeMove.cpp` and `freeMove.h`

These files implement the free move camera control.

- **Functions**:
  - `FreeMove()`: Constructor to initialize free move control.
  - `processInput()`: Process input for free move control.

#### `game.cpp` and `game.h`

These files contain game-specific logic.

- **Functions**:
  - `init()`, `update()`, `render()`: Initialize, update, and render game-specific elements.

#### `input.cpp` and `input.h`

These files handle user input.

- **Functions**:
  - `processInput()`: Process user input from keyboard/mouse.

#### `lighting.cpp` and `lighting.h`

These files manage lighting effects.

- **Functions**:
  - `addLight()`: Add a light source.
  - `updateLighting()`: Update lighting calculations.

#### `main.cpp`

This is the application entry point.

- **Functions**:
  - `main()`: Main function to start the application.

#### `material.cpp` and `material.h`

These files handle material properties and textures.

- **Functions**:
  - `setTexture()`, `getTexture()`: Set and get material textures.
  - `setShader()`, `getShader()`: Set and get shaders for materials.

#### `math3d.cpp` and `math3d.h`

These files handle 3D mathematics (vectors, matrices).

- **Functions**:
  - Various functions for vector and matrix operations (e.g., addition, multiplication).

#### `mesh.cpp` and `mesh.h`

These files handle 3D model loading and management.

- **Functions**:
  - `loadMesh()`, `renderMesh()`: Load and render 3D meshes.

#### `profiling.cpp` and `profiling.h`

These files contain performance profiling tools.

- **Functions**:
  - `startProfiling()`, `endProfiling()`: Start and end performance profiling.

#### `renderingEngine.cpp` and `renderingEngine.h`

These files manage the rendering process and pipeline.

- **Functions**:
  - `renderScene()`: Render the entire scene.
  - `setRenderTarget()`, `getRenderTarget()`: Set and get render targets.

#### `shader.cpp` and `shader.h`

These files handle shader compilation and application.

- **Functions**:
  - `compileShader()`, `applyShader()`: Compile and apply shaders.

#### `texture.cpp` and `texture.h`

These files handle texture loading and management.

- **Functions**:
  - `loadTexture()`, `bindTexture()`: Load and bind textures.

#### `timing.cpp` and `timing.h`

These files handle timing and frame rate management.

- **Functions**:
  - `startFrame()`, `endFrame()`: Start and end a frame for timing purposes.

#### `transform.cpp` and `transform.h`

These files manage transformations (position, rotation, scale).

- **Functions**:
  - `setPosition()`, `setRotation()`, `setScale()`: Set transformation properties.
  - `getMatrix()`: Get the transformation matrix.

#### `util.cpp` and `util.h`

These files contain utility functions.

- **Functions**:
  - Various helper functions for the engine (e.g., logging, error handling).

#### `window.cpp` and `window.h`

These files manage window creation and events.

- **Functions**:
  - `createWindow()`, `destroyWindow()`: Create and destroy the application window.
  - `processEvents()`: Process window events (e.g., resize, close).
