## Install Depemdencies (windows only)

Note: when in windows commands are run using [git-bash](https://git-scm.com/downloads) terminal or powershell terminal.

### Install vcpkg (windows only)

In git-bash terminal run:

```
> cd /c/w1
> git clone https://github.com/microsoft/vcpkg.git
> cd vcpkg
> ./bootstrap-vcpkg.bat
```

### Install libraries (windows only)

In git-bash terminalC run:

```
> /c/w1/vcpkg/vcpkg install libuv:x64-windows
> /c/w1/vcpkg/vcpkg install zlib:x64-windows
> /c/w1/vcpkg/vcpkg install jwt-cpp:x64-windows
> /c/w1/vcpkg/vcpkg install openssl:x64-windows
```
### Install mariadb connector (windows only)

Im windows follow instructions on this [link](https://mariadb.com/downloads/connectors/connectors-data-access/cpp-connector/)

### Install MS Visual Studio Community and ensure it has clang compiler installed (windows only)

Open MS Visual Studio Installer  and verify that clang is installed.

![ msva installerc settings ](doc/img/msvc_installer_settings_clang.jpg)


### Build Micro websockets (windows only)

[also see](https://github.com/uNetworking/uWebSockets/actions/runs/8217383674/workflow)


Clone the [repository](https://github.com/uNetworking/uWebSockets.git) inside the project root.


```
> cd /c/w1/gaow
> git clone --recursive https://github.com/uNetworking/uWebSockets.git
> cd uWebSockets
> git checkout 01058d90e9d092c2d6551956d7e0785e0e94ff21
```

Open  'x64 tools command prompt' terminal which was installed as part of visual studio installation and run:

```
> cd \w1\gaow
> cd .\uWebSockets\
> powershell
> ..\scripts\uWebSockets_build.ps1

```

### Build protobuf (windows only)

To build and install `protobuf` follow instrusction in `README.md` in `gaob` project.

## Build gaow project (windows only)

We build project using [clang platform toolset](https://learn.microsoft.com/en-us/gaming/gdk/_content/gc/tools-pc/visualstudio/gr-vs-clang),
[also see CMAKE_GENERATOR_TOOLSET](https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html).

In powershell terminal:

```
> mkdir /w1/gaow_build
> cd /w1/gaow_build
> cmake -T clangcl ../gaow
> cmake --build .
```

In `git-bash` terminal:
```
> cp /c/w1/vcpkg/installed/x64-windows/bin/*.dll /c/w1/gaow_build/Debug
> cp /c/'Program Files'/MariaDB/'MariaDB C++ Connector 64-bit'/mariadbcpp.dll /c/w1/gaow_build/Debug
```

In powershell terminal run server `wsrv.exe`:
```
> cd /w1/gaow_build/Debug
> ./wsrv.exe
Listening on port 9001
```


### Visual Studio C++ manual settings (windows only)

Open `wsrv` project properties, go to `C/C++`, choose `General`, 
then under the item `Additional Include Directories` add directories `C:\w1\cpackages\include` and `C:\w1\vcpkg\installed\x64-windows\include`
and `C:\Program Files\MariaDB\MariaDB C++ Connector 64-bit\include`.


## Build (linux only)


```
> mkdir ~/w1
> cd ~/w1
```
Clone `gaow` repository inside `~\w1` 

Clone the [repository](https://github.com/uNetworking/uWebSockets.git) inside the project root.

```
> cd ~/w1/gaow
> git clone --recursive https://github.com/uNetworking/uWebSockets.git
```

### Build uWebSockets (linux only)

```
> apt install build-essential
> cd ~/w1/gaow/uWebSockets
> make
```

### Install mariadb connector (linux only)

Im windows follow instructions on this [link](https://mariadb.com/downloads/connectors/connectors-data-access/cpp-connector/)

```
> dopkg -i mariadb-connector-cpp_1.1.5-1+maria~jammy_amd64.deb
```

### Build jwt-cpp (linux only)

Install dependencies:

```
> apt install libssl-dev
> apt install libuv1-dev
> apt install libz-dev
> apt install cmake
```

Build `jwt-cpp`:

```
> mkdir ~/w1/cpackages
> mkdir ~/w1/build
> cd ~/w1/build
> git clone https://github.com/Thalhammer/jwt-cpp.git
> cd jwt-cpp
> git checkout a6927cb8140858c34e05d1a954626b9849fbcdfc
> cd ..
> mkdir jwt-cpp_build
> cd jwt-cpp_build
> cmake ../jwt-cpp
> cmake --build .
> cmake --install . --prefix ~/w1/cpackages
```

### Build abseil (linux only)


```
> mkdir ~/w1/cpackages
> cd ~/w1/build
> git clone https://github.com/abseil/abseil-cpp.git
> cd abseil-cpp
> git checkout f04e489056d9be93072bb633d9818b1e2add6316
> cd ..
> mkdir abseil-cpp_build
> cd abseil-cpp_build
> cmake ../abseil-cpp -DCMAKE_INSTALL_PREFIX=~/w1/cpackages -DABSL_PROPAGATE_CXX_STD=ON
> cmake --build . --config Release
> cmake --install . --config Release --prefix ~/w1/cpackages

```

### Build protobuf (linux only)

```
> cd ~/w1/build
> git clone https://github.com/protocolbuffers/protobuf.git
> cd protobuf
> git checkout v3.21.12
> git submodule update --init --recursive
> cd ..
> mkdir protobuf_build
> cd protobuf_build
> cmake ../protobuf -DCMAKE_CXX_STANDARD=14 -DCMAKE_INSTALL_PREFIX=~/w1/cpackages 
> cmake --build . --config Release
> cmake --install . --config Release --prefix ~/w1/cpackages
```


### Buiild gaow (linux ony)

```
> cd ~/w1
> mkdir gaow_build
> cd gaow_build
> cmake ../gaow
> cmake --build . --config Release
```
