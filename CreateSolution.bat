@echo off

call git submodule update --init --recursive

cd Dist/BuildScripts/Windows

call build-glfw.bat

cd ../../../Dist/BuildScripts/Windows

call build.bat

pause