cmake_minimum_required(VERSION 3.10)

project(rpc2 CXX)
set (CMAKE_CXX_STANDARD 17)
set (THREADS_PREFER_PTHREAD_FLAG ON)

file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Streams/*.cpp"
                   "${CMAKE_SOURCE_DIR}/include/rpc2/Core/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/rpc2/Protocol/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/rpc2/Streams/*.hpp"
                   "${CMAKE_SOURCE_DIR}/include/rpc2/Utilities/*.hpp")

add_library (rpc2 ${SOURCES})
target_include_directories (rpc2 PUBLIC "${CMAKE_SOURCE_DIR}/include/")

find_package (Threads REQUIRED)
target_link_libraries (rpc2 Threads::Threads)

if (MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdParty/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

