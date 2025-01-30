# About Qbit
Qbit is a free, open-source, cross-platform 2D/3D game engine. While the engine is still in its **early development** phase, core systems are actively being built, and many advanced features are planned for future releases.

## Architecture
Qbit's engine is structured as a **static library** and named as qbit, and Qbit's editor named as creator being the main executable that utilizes the engine as a library. The Editor provides an interface for game development, making it easier to interact with the engine’s core features.

All of the source files are located in source/ directory, Qbit follows modular approach for building purposes, sub-directories treated as different modules and compiled individually with different cmake files, that makes it easy to modify the included libraries in the executable.

Third party libraries are located in lib/ and extern/ folder, lib folder holds precompiled libraries for each platform for some bigger libraries, and the other libraries that are relatively small and easy to build are located inside extern/ folder and added as a module to our cmake build.

## Current Features
- **Creator**: A powerful and user-friendly editor for building and managing your game.
- **Void**: The real-time rendering engine of the Qbit, designed as a platform agnostic API to work with multiple graphics APIs, has backend support for OpenGL and Vulkan.
- **Qcs**: Qbit CSharp, the engine uses C# as a scripting language to easily communicate with the core of the Qbit and manipulate the game logic.

## Planned & Under Development Features
- **Vulkan Support**: Vulkan integration for advanced rendering capabilities and better performance.
- **3D Support**: Full 3D rendering and game mechanics are under development.
- **Cross-Platform Support**: Expanding compatibility across multiple platforms to ensure broader deployment.
- **Asset Manager**: A robust asset management system for importing and exporting assets.
- **Game Distribution**: Tools and features to help distribute your game for different platforms.

Development is ongoing, and contributions are welcome. Check out our [contribution guidelines](../../CONTRIBUTING.md) to get involved!
