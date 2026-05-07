$asciiRoot = "D:\deep_tide_workspace"
$exePath = "$asciiRoot\build\DeepTideStation.exe"

if (-not (Test-Path $exePath)) {
    Write-Error "Executable not found. Run .\build-qt.ps1 first."
}

Start-Process -FilePath $exePath
