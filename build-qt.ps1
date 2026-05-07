$ErrorActionPreference = "Stop"

$workRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$asciiRoot = "D:\deep_tide_workspace"
$qtDir = "D:\AppGallery\Qt\6.11.0\mingw_64"

if (-not (Test-Path $asciiRoot)) {
    cmd /c "mklink /J ""$asciiRoot"" ""$workRoot""" | Out-Null
}

$env:QTDIR = $qtDir
$env:Qt6_DIR = "$qtDir\lib\cmake\Qt6"
$env:CMAKE_PREFIX_PATH = $qtDir
$env:PATH = "D:\AppGallery\Qt\Tools\CMake_64\bin;D:\AppGallery\Qt\Tools\mingw1310_64\bin;$qtDir\bin;$env:PATH"

Get-Process DeepTideStation -ErrorAction SilentlyContinue | Stop-Process -Force
Remove-Item -Recurse -Force "$asciiRoot\build" -ErrorAction SilentlyContinue

& "D:\AppGallery\Qt\Tools\CMake_64\bin\cmake.exe" `
    -S $asciiRoot `
    -B "$asciiRoot\build" `
    -G "MinGW Makefiles" `
    -DCMAKE_CXX_COMPILER="D:/AppGallery/Qt/Tools/mingw1310_64/bin/g++.exe"

& "D:\AppGallery\Qt\Tools\CMake_64\bin\cmake.exe" --build "$asciiRoot\build"
