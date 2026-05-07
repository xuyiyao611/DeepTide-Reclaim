@echo off
setlocal

set "WORKROOT=D:\大作业"
set "ASCIIROOT=D:\deep_tide_workspace"
set "QTDIR=D:\AppGallery\Qt\6.11.0\mingw_64"
set "Qt6_DIR=%QTDIR%\lib\cmake\Qt6"
set "CMAKE_PREFIX_PATH=%QTDIR%"
set "PATH=D:\AppGallery\Qt\Tools\CMake_64\bin;D:\AppGallery\Qt\Tools\mingw1310_64\bin;%QTDIR%\bin;%PATH%"

if not exist "%ASCIIROOT%" (
    mklink /J "%ASCIIROOT%" "%WORKROOT%"
)

if exist "%ASCIIROOT%\build" (
    rmdir /S /Q "%ASCIIROOT%\build"
)

cmake -S "%ASCIIROOT%" -B "%ASCIIROOT%\build" -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="D:/AppGallery/Qt/Tools/mingw1310_64/bin/g++.exe"
if errorlevel 1 exit /b 1

cmake --build "%ASCIIROOT%\build"
exit /b %errorlevel%
