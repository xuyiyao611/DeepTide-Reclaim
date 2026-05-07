@echo off
setlocal

set "ASCIIROOT=D:\deep_tide_workspace"
set "EXE=%ASCIIROOT%\build\DeepTideStation.exe"

if not exist "%EXE%" (
    echo Executable not found. Run build-qt.cmd first.
    exit /b 1
)

start "" "%EXE%"
exit /b 0
