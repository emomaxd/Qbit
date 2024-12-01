@echo off

cd ..

:: Check if the build directory exists
if not exist "build" (
    echo Build directory does not exist. Creating it now...
    mkdir build
)

rem Set the source and destination directories
set SOURCE_DIR=%CD%\Editor
set DEST_DIR=%CD%\build\Editor

rem Debugging: Print the source and destination directories
echo Source Directory: %SOURCE_DIR%
echo Destination Directory: %DEST_DIR%

rem Check if the destination directory exists, create it if not
if not exist "%DEST_DIR%" (
    mkdir "%DEST_DIR%"
    mkdir "%DEST_DIR%\mono"
    mkdir "%DEST_DIR%\Resources"
    mkdir "%DEST_DIR%\assets"
    mkdir "%DEST_DIR%\bin"
)

rem Copy .dll and .pdb files from Editor\bin to build\Editor
echo Copying .dll and .pdb files...
xcopy /s /y /d "%SOURCE_DIR%\bin\*.dll" "%DEST_DIR%\bin\"
xcopy /s /y /d "%SOURCE_DIR%\bin\*.pdb" "%DEST_DIR%\bin\"

rem Copy the assets directory from Editor to build\Editor
echo Copying assets directory...
xcopy /s /y "%SOURCE_DIR%\assets" "%DEST_DIR%\assets"

rem Copy the Resources directory from Editor to build\Editor
echo Copying Resources directory...
xcopy /s /y "%SOURCE_DIR%\Resources" "%DEST_DIR%\Resources"

rem Copy the mono directory from Editor to build\Editor
echo Copying mono directory...
xcopy /s /y "%SOURCE_DIR%\mono" "%DEST_DIR%\mono"

rem Copy the imgui.ini file from Editor to build\Editor
echo Copying imgui.ini file...
echo F|xcopy /F /y "%SOURCE_DIR%\imgui.ini" "%DEST_DIR%\imgui.ini"

rem End of copy operations
echo File copy operation completed.

:: Change to the build directory
cd build

:: Call cmake to configure the project
call cmake -S .. -B .

:: Pause to keep the window open
pause
