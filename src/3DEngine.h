#ifndef __3DENGINE_H_INCLUDED
#define __3DENGINE_H_INCLUDED

// This header file includes all necessary headers for using the 3D engine.
// By including this file, users get access to all the core components needed for the engine.

#include "mesh.h"        // Includes definitions for mesh data and operations
#include "shader.h"      // Includes shader programs and related functions
#include "transform.h"   // Includes transformation matrices and operations
#include "camera.h"      // Includes camera setup and manipulation
#include "lighting.h"    // Includes lighting setup and calculations
#include "entity.h"      // Includes entity management and properties
#include "meshRenderer.h"// Includes rendering operations for meshes
#include "window.h"      // Includes window management and related functions
#include "coreEngine.h"  // Includes core engine functionalities and initialization
#include "game.h"        // Includes game-specific logic and setup

// SDL2 defines a macro named 'main', which can conflict with other definitions
// This line ensures that 'main' is not defined by SDL2, allowing the compiler to find the main function
#undef main

#endif // __3DENGINE_H_INCLUDED
