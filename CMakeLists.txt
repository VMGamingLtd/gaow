cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(vcpkg_install_path /w1/vcpkg/installed/x64-windows)

add_library(libuv STATIC IMPORTED)
if(WIN32)
  set_target_properties(libuv PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/uv.lib 
  )
  target_include_directories(libuv 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(UV_LIBRARY NAMES uv 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libz STATIC IMPORTED)
if(WIN32)
  set_target_properties(libz PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/zlib.lib 
  )
  target_include_directories(libz 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
  find_library(ZLIB_LIBRARY NAMES z 
    PATHS /usr/lib
    PATH_SUFFIXES x86_64-linux-gnu
    REQUIRED
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()


add_library(uWebSocketsLib OBJECT IMPORTED)
file(GLOB uWebSocketsLib_obj_files "${CMAKE_SOURCE_DIR}/uWebSockets/uSockets/*.o")
set(uWebSocketsLib_includes 
  "${CMAKE_SOURCE_DIR}/uWebSockets/uSockets/src" 
  "${CMAKE_SOURCE_DIR}/uWebSockets/src"
)
set_property(TARGET uWebSocketsLib PROPERTY
  IMPORTED_OBJECTS ${uWebSocketsLib_obj_files}
)
if(WIN32)
target_include_directories(uWebSocketsLib 
  INTERFACE ${vcpkg_install_path}/include
)
endif()


project(WebsocketServer)

add_executable(wsrv 
  wsrv/main.cpp
)

if(WIN32)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    libuv
    libz
  )
elseif(UNIX)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    ${UV_LIBRARY}
    ${ZLIB_LIBRARY}
  )
else()
  message(FATAL_ERROR "unsupported platform")
endif()
target_include_directories(wsrv PRIVATE ${uWebSocketsLib_includes})

#project(app1)
#
#add_executable(app1 app1/main.cpp)
