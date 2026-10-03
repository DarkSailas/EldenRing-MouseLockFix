$ErrorActionPreference = "Stop"

$outDll = "MouseLockFix.dll"

Write-Host "Compiling $outDll with g++..."

& g++ -std=c++20 -O2 -shared -DNDEBUG -fno-exceptions -fno-rtti -static -static-libgcc -static-libstdc++ -s `
    src/dllmain.cpp `
    -o $outDll `
    -luser32 -lkernel32

if ($LASTEXITCODE -ne 0) {
    Write-Error "Compilation failed!"
    exit 1
}

Write-Host "Build successful: $outDll"
$dllItem = Get-Item $outDll
Write-Host "Size: $($dllItem.Length) bytes"
