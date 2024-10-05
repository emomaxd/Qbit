@echo off
setlocal

cd ..

REM Directories to clean
set "dirs=.\ .\Engine .\Editor .\Sandbox"

REM Files and directories to delete
set "vs_files=*.sln *.vcxproj *.vcxproj.filters *.vcxproj.user"
set "vs_dirs=.vs Debug Release x64 .\Qbit-ScriptCore\bin .\Qbit-ScriptCore\obj .\Engine\vendor\assimp\code\Debug .\Engine\Release .\Engine\MinSizeRel .\Engine\RelWithDebInfo .\Engine\vendor\glfw\install .\Engine\Engine.dir .\Editor\Editor.dir .\Sandbox\Sandbox.dir .\Sandbox\MinSizeRel .\Sandbox\Release .\Sandbox\Debug"
set "cmake_files=CMakeCache.txt cmake_install.cmake Sandbox\*.json"
set "cmake_dirs=CMakeFiles"

for %%d in (%dirs%) do (
    pushd %%d
    echo Cleaning %%d

    REM Delete Visual Studio files
    for %%f in (%vs_files%) do (
        if exist %%f (
            echo Deleting %%f
            del /f /q %%f
        )
    )

    REM Delete Visual Studio directories
    for %%d in (%vs_dirs%) do (
        if exist %%d (
            echo Deleting directory %%d
            rmdir /s /q %%d
        )
    )

    REM Delete CMake files
    for %%f in (%cmake_files%) do (
        if exist %%f (
            echo Deleting %%f
            del /f /q %%f
        )
    )

    REM Delete CMake directories
    for %%d in (%cmake_dirs%) do (
        if exist %%d (
            echo Deleting directory %%d
            rmdir /s /q %%d
        )
    )

    popd
)

echo Cleanup complete.
endlocal
pause
