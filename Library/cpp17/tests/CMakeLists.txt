file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Utilities/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/Protocol/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/Streams/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/Streams/*.hpp")

add_executable (rpc2_tests ${SOURCES})
target_link_libraries (rpc2_tests rpc2 gtest gmock_main)
