@echo off

:: Navigate to the parent directory
cd ..

:: Update submodules recursively
call git submodule update --init --recursive

:: Navigate to Assimp vendor directory
cd Engine/vendor/assimp
    
:: Configure and build Assimp in release mode
call cmake -DASSIMP_BUILD_ZLIB=ON -DBUILD_SHARED_LIBS=OFF CMakeLists.txt
call cmake --build .

:: Navigate back to the root directory
cd ..
cd ..
cd ..

:: Navigate to the GLFW build script directory
cd Dist/BuildScripts/Windows

:: Call the GLFW build script
call build-glfw.bat

:: Navigate to the main build script directory
cd ../../../Dist/BuildScripts/Windows

:: Call the main build script
call build.bat

:: Pause to keep the window open
pause
