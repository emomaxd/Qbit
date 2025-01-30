# Building Qbit

## Instructions

Steps to build Qbit from scratch for each operating system.

- [on Windows](#building-qbit-on-windows)
- [on Linux](#building-qbit-on-linux)
- [on macOS](#building-qbit-on-macos) *(macOS support coming soon)*


## Build System

Qbit uses the CMake build system.


## Building Qbit on Windows

### Prerequisites

- CMake
- Python (3.x)
- Git
- Visual Studio (Tested on VS2022)

Qbit doesn't allow in-source builds, so it is recommended to create a folder - usually build\ - and follow the instructions.

It is important to use **cmd.exe** and not powershell or any other shell, the instructions may not work otherwise.

### Download Sources

Following build instructions use relative paths and assume you to you are in the correct directory in the **cmd.exe**, otherwise you may download the sources to another directory that you may not want to.

Clone the repository.
```shell
git clone https://github.com/emomaxd/qbit.git
```
This instruction creates a folder called "qbit".


Download libraries.
```shell
python build_scripts/util/configure.py
```
This script is gonna download the libraries according to the platform.

### Compile Qbit

Create build directory
```shell
mkdir build && cd build
```

Configure with CMake
```shell
cmake ..
```

Compile using CMake, Then in the following command just substitute [CONFIG] with one of the following options: Release, Debug, RelWithDebInfo
```shell
cmake --build . --target INSTALL --config [CONFIG]
```


## Building Qbit on Linux

**Coming soon**, really.

---

## Building Qbit on macOS

**macOS is not supported yet.**  
Support for macOS is planned for future releases. If you're interested in helping out or testing, feel free to contribute to the development or check back later for updates.

Alternatively, you may follow the instructions for Linux as a workaround if you want to try building on macOS with some adjustments.

NOTE: macOS support would really take **some** time.
