@echo off

cd Dist/BuildScripts/Windows

call build-glfw.bat

cd ../../../Dist/BuildScripts/Windows

call build.bat

pause