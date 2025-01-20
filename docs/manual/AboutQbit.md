# About Qbit
Welcome to Qbit! Qbit is a free, open-source, cross-platform 2D/3D game engine. While the engine is still in its **early development** phase, core systems are actively being built, and many advanced features are planned for future releases.

## Architecture
Qbit's engine is structured as a **static library**, with the **Editor** being the main executable that utilizes the engine as a library. The Editor provides an interface for game development, making it easier to interact with the engine’s core features.

**Qbit-ScriptCore** acts as a bridge, marshaling the engine's C++ functions into the C# environment of Qbit. This allows game logic and scripting to be written in C# while leveraging the performance of the underlying C++ engine.

Previously, the development used a **Sandbox** executable as a primary testing tool, but it has now been deprecated in favor of the Editor.

## Current Features
- **Editor**: A powerful and user-friendly editor for building and managing your game.
- **Flexible Rendering System**: The rendering architecture is designed to be adaptable, with plans to integrate advanced APIs like Vulkan for improved performance and flexibility.
- **Scripting Support**: The engine uses a dynamic scripting system with C# for enhanced versatility and ease of development.

## Planned & Under Development Features
- **Vulkan Support**: Vulkan integration for advanced rendering capabilities and better performance.
- **3D Support**: Full 3D rendering and game mechanics are under development.
- **Cross-Platform Support**: Expanding compatibility across multiple platforms to ensure broader deployment.
- **Asset Manager**: A robust asset management system for importing and exporting assets.
- **Game Distribution**: Tools and features to help distribute your game for different platforms.

Development is ongoing, and contributions are welcome. Check out our [contribution guidelines](../../CONTRIBUTING.md) to get involved!