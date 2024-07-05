cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(vcpkg_install_path /w1/vcpkg/installed/x64-windows)
set(cpackages_install_path /w1/cpackages)

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

add_library(libprotobuf STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotobuf PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotobufd.lib 
  )
  target_include_directories(libprotobuf 
    INTERFACE ${cpackages_install_path}/include
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libprotoc STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotoc PROPERTIES
    IMPORTED_LOCATION ${cpackages_install_path}/lib/libprotocd.lib 
  )
  target_include_directories(libprotoc 
    INTERFACE ${cpackages_install_path}/include
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

# Note: jwt-cpp is header only library
add_library(jwt-cpp STATIC IMPORTED)
if(WIN32)
  target_include_directories(jwt-cpp 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libssl STATIC IMPORTED)
if(WIN32)
  set_target_properties(libssl PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libssl.lib 
  )
  target_include_directories(libssl 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libcrypto STATIC IMPORTED)
if(WIN32)
  set_target_properties(libcrypto PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libcrypto.lib 
  )
  target_include_directories(libcrypto 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
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
	#target_include_directories(uWebSocketsLib 
	#  INTERFACE ${vcpkg_install_path}/include
	#)
endif()


project(WebsocketServer)

file(GLOB protobuf_source_files "${CMAKE_SOURCE_DIR}/wsrv/protobuf/*.pb.cc"  "${CMAKE_SOURCE_DIR}/wsrv/protobuf/*.pb.h")

add_executable(wsrv 
  wsrv/main.cpp
  wsrv/WsConnection.cpp
  wsrv/WsConnection.h
  wsrv/WsSocketContext.cpp
  wsrv/WsSocketContext.h
  wsrv/uuid.cpp
  wsrv/uuid.h
  wsrv/message/Dispatcher.cpp
  wsrv/message/Dispatcher.h
  wsrv/message/websocket/PingPong.cpp
  wsrv/message/websocket/PingPong.h
  wsrv/message/websocket/Authenticate.cpp
  wsrv/message/websocket/Authenticate.h
  wsrv/message/unity_browser_channel/UnityBrowserChannel.cpp
  wsrv/message/unity_browser_channel/UnityBrowserChannel.h
  ${protobuf_source_files}
)

# Create source groups to maintain directory structure in Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}")

# Set the runtime library to /MTd for debug builds
if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
endif()

if(WIN32)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    libuv
    libz
	libprotobuf
	libprotoc
	libssl
	libcrypto
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

# Note: allways keep cpackages_install_path include before vcpkg_install_path include, 
#       we want manualy compiled package overide vcpkg installed package provided same include can be found  in both locations, 
target_include_directories(wsrv PRIVATE 
	${uWebSocketsLib_includes}
	${cpackages_install_path}/include
	${vcpkg_install_path}/include
)
