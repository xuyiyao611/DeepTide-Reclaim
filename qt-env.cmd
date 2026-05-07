@echo off
set "QTDIR=D:\AppGallery\Qt\6.11.0\mingw_64"
set "Qt6_DIR=%QTDIR%\lib\cmake\Qt6"
set "CMAKE_PREFIX_PATH=%QTDIR%"
set "PATH=D:\AppGallery\Qt\Tools\CMake_64\bin;D:\AppGallery\Qt\Tools\mingw1310_64\bin;%QTDIR%\bin;D:\AppGallery\Qt\Tools\QtCreator\bin;%PATH%"
echo Qt development environment loaded.
echo QTDIR=%QTDIR%
echo Qt6_DIR=%Qt6_DIR%
cmd /k
