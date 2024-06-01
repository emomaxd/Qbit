# Qbit

Qbit is a lightweight game engine designed for learning purposes. It's built with a mission to achieve high performance, modularity, readability, and memory safety. Qbit aims to provide a clear and structured codebase for understanding game engine development concepts.

## Build Instructions

### Windows:

1. Run `build-glfw.bat` to compile GLFW.
2. Run `build.bat` to generate the Visual Studio Solution.
3. After running the scripts:
    - Open `Qbit.sln` in the `build/` directory.
    - Set `Engine` as the Startup project.
    - Run the project.

### Linux:

1. Run `build-glfw.sh` to compile GLFW.
2. Run `build-glew.sh` to compile GLEW.
3. Run `build-cmake.sh` to build the project.

## Project Structure

Qbit's project structure is designed to promote clarity and organization:

- **Engine**: The core library of the engine, containing essential components and functionalities.
- **Editor**: Provides the editor layer of the engine.
- **src**: Contains the source code of the engine.
- **vendor**: Third-party dependencies are stored here.
- **sandbox**: Provides a sandbox application for testing the engine.

## Features

- **High Performance**: Qbit is optimized for performance, ensuring smooth gameplay experiences.
- **High Modularity**: The engine is divided into modules, allowing for easy extension and customization.
- **High Readability**: Codebase is structured and documented for readability, facilitating comprehension and collaboration.
- **Memory Safety**: Qbit prioritizes memory safety to prevent common programming errors and improve stability.

## Contributing

Contributions to Qbit are welcome! Whether you're a beginner looking to learn or an experienced developer wanting to enhance the engine, feel free to fork the repository and submit pull requests.

## License

Qbit is licensed under the [MIT License](LICENSE), allowing for free use and modification.

## Acknowledgments

Qbit draws inspiration from various game engines and learning resources, including the [Hazel](https://github.com/TheCherno/Hazel) Engine by TheCherno.

## Follow the progress : 
[Trello](https://trello.com/b/8og3yTb4/engine)
---
![Alt Text](GithubResources/engine_demo.png)
![Alt Text](GithubResources/cascaded_shadow_map.gif)
![Alt Text](GithubResources/lighting_demo4-diffuse_map.gif)
![Alt Text](GithubResources/lighting_demo3-diffuse_map-specular_map.gif)