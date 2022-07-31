cmake_minimum_required(VERSION 3.8)

project(mysql_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
  set(MYSQL_DIR "C:\\Program Files\\MySQL\\MySQL Server 8.0" CACHE STRING "set MySQL root dir" FORCE)
  set(MYSQL_INCLUDE_DIR "${MYSQL_DIR}\\include" CACHE STRING "set MySQL include dir" FORCE)
  set(MYSQL_LIBRARY "${MYSQL_DIR}\\lib\\libmysql.lib" CACHE STRING "set MySQL lib" FORCE)
  file(GLOB mysql_headers "${MYSQL_INCLUDE_DIR}/*.h")
  foreach(header ${mysql_headers})
    file(COPY ${header} DESTINATION "${MYSQL_INCLUDE_DIR}/mysql")
  endforeach()

  if (CMAKE_BUILD_TYPE MATCHES Debug)
    file(COPY "${MYSQL_DIR}\\lib\\libmysql.dll" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
  else()
    file(COPY "${MYSQL_DIR}\\lib\\libmysql.dll" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
  endif()
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "set CRT to MD" FORCE)

set(ENABLE_NET OFF CACHE BOOL "Enable Net" FORCE)
set(ENABLE_ENCODINGS OFF CACHE BOOL "Enable Encodings" FORCE)
set(ENABLE_XML OFF CACHE BOOL "Enable XML" FORCE)
set(ENABLE_JSON OFF CACHE BOOL "Enable JSON" FORCE)
set(ENABLE_MONGODB OFF CACHE BOOL "Enable MongoDB" FORCE)
set(ENABLE_DATA_SQLITE OFF CACHE BOOL "Enable Data SQlite" FORCE)
set(ENABLE_REDIS OFF CACHE BOOL "Enable Redis" FORCE)
set(ENABLE_ZIP OFF CACHE BOOL "Enable Zip" FORCE)
set(ENABLE_PAGECOMPILER OFF CACHE BOOL "Enable PageCompiler" FORCE)
set(ENABLE_PAGECOMPILER_FILE2PAGE OFF CACHE BOOL "Enable File2Page" FORCE)
set(ENABLE_ACTIVERECORD OFF CACHE BOOL "Enable ActiveRecord" FORCE)
set(ENABLE_ACTIVERECORD_COMPILER OFF CACHE BOOL "Enable ActiveRecord Compiler" FORCE)
set(ENABLE_DATA_MYSQL ON CACHE BOOL "Enable MySQL" FORCE)

add_subdirectory(external/poco)

add_executable(application src/main.cpp)
target_link_libraries(application PRIVATE Poco::Data Poco::DataMySQL)
