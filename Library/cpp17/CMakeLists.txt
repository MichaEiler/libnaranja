cmake_minimum_required(VERSION 3.10)

project(naranja CXX)
set (CMAKE_CXX_STANDARD 17)
set (THREADS_PREFER_PTHREAD_FLAG ON)

file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/streams/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/one/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/*.cpp"
                   "${CMAKE_SOURCE_DIR}/src/rpc/*.cpp"
                   "${CMAKE_SOURCE_DIR}/include/naranja/core/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/naranja/protocol/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/naranja/streams/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/naranja/utils/*.hpp")

include("${CMAKE_SOURCE_DIR}/3rdparty/boost.cmake")

add_definitions("-DBOOST_ASIO_SEPARATE_COMPILATION=1")

add_library (naranja ${SOURCES})
target_include_directories (naranja PUBLIC "${CMAKE_SOURCE_DIR}/include/")

find_package (Threads REQUIRED)
target_link_libraries (naranja boost_asio boost_coroutine2 Threads::Threads)

if (MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

