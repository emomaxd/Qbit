@echo off

cd ..

call git submodule update --init --recursive

cd Engine/vendor/assimp

call cmake -DASSIMP_BUILD_ZLIB=ON CMakeLists.txt
call cmake --build .

copy bin\Debug\assimp-vc143-mtd.dll ..\..\..\Engine

cd ..
cd ..
cd ..

cd Dist/BuildScripts/Windows

call build-glfw.bat

cd ../../../Dist/BuildScripts/Windows

call build.bat

pause
