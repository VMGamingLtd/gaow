cp C:\bin\vcpkg\installed\x64-windows\bin\uv.dll .\uv.dll
$Env:WITH_ZLIB='0'
$ENV:WITH_LTO='0'
$Env:CC='clang'
$ENV:CFLAGS='-I C:\bin\vcpkg\installed\x64-windows\include'
$ENV:LDFLAGS='-L C:\bin\vcpkg\installed\x64-windows\lib'
$ENV:CXX='clang++'
$ENV:EXEC_SUFFIX='.exe'
$ENV:WITH_LIBUV='1'
$ENV:WITH_OPENSSL='1'
nmake
