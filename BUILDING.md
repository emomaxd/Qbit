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
- Git
- VulkanSDK
- Visual Studio (Tested on VS2022)

Qbit doesn't allow in-source builds, so it is recommended to create a folder - usually build\ - and follow the instructions. The instructions have that command also, don't worry about it.

It is important to use **cmd.exe** and not powershell or any other shell, the instructions may not work otherwise.

### Download Sources

Following build instructions use relative paths and assume you to you are in the correct directory in the **cmd.exe**, otherwise you may download the sources to another directory that you may not want to.

Clone the repository.
```shell
git clone --recursive https://github.com/emomaxd/Qbit.git
```
This instruction creates a folder called "Qbit".


Download the libraries. (Use it when Qbit cloned without **recursive** option)
```shell
git submodule update --init --recursive
```

### Compile Qbit

Move into the scripts/ directory and run the script.
```shell
cd Qbit/scripts
CreateSolution.bat
```

Start developing by opening the **Qbit.sln**.
```shell
cd ../build
Qbit.sln
```


## Building Qbit on Linux

**Coming soon**, really.

---

## Building Qbit on macOS

**macOS is not supported yet.**  
Support for macOS is planned for future releases. If you're interested in helping out or testing, feel free to contribute to the development or check back later for updates.

Alternatively, you may follow the instructions for Linux as a workaround if you want to try building on macOS with some adjustments.

NOTE: macOS support would really take **some** time.