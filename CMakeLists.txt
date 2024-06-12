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

add_library(libprotobuf STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotobuf PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libprotobuf.lib 
  )
  target_include_directories(libprotobuf 
    INTERFACE ${vcpkg_install_path}/include
  )
elseif(UNIX)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_library(libprotoc STATIC IMPORTED)
if(WIN32)
  set_target_properties(libprotoc PROPERTIES
    IMPORTED_LOCATION ${vcpkg_install_path}/lib/libprotoc.lib 
  )
  target_include_directories(libprotoc 
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
  wsrv/WsSocketContext.cpp
  wsrv/WsSocketContext.h
  wsrv/message/Dispatcher.cpp
  wsrv/message/Dispatcher.h
  wsrv/message/parser/Ping.cpp
  wsrv/message/parser/Ping.h
  wsrv/message/websocket/PingPong.cpp
  wsrv/message/websocket/PingPong.h
  ${protobuf_source_files}
)

# Create source groups to maintain directory structure in Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}")

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/wsrv" PREFIX "wsrv" FILES
#  wsrv/main.cpp
#)
#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/wsrv/messages" PREFIX "wsrv/messages" FILES
#  wsrv/messages/Dispatcher.cpp
#)
#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/wsrv/messages/websocket" PREFIX "wsrv/messages/websocket" FILES
#  wsrv/messages/websocket/PingPong.cpp
#)
## protobuf directories
#foreach(file IN LISTS protobuf_source_files)
#  get_filename_component(dir ${file} DIRECTORY)
#  file(RELATIVE_PATH dir ${CMAKE_CURRENT_SOURCE_DIR} ${dir})
#  # Create groups based on directory structure for protobuf files
#  source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "${dir}" FILES "${file}")
#endforeach()

if(WIN32)
  target_link_libraries(wsrv 
    uWebSocketsLib 
    libuv
    libz
	libprotobuf
	libprotoc
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

target_include_directories(wsrv PRIVATE 
	${uWebSocketsLib_includes}
	${vcpkg_install_path}/include
)
#if(WIN32)
#	target_include_directories(wsrv PRIVATE ${vcpkg_install_path}/include)
#endif()

#project(app1)
#
#add_executable(app1 app1/main.cpp)
