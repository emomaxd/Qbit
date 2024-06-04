@echo off

cd BuildScripts/Windows

call build-glfw.bat

cd ../../../BuildScripts/Windows

call build.bat

pause