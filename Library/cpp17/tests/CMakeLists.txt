file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/protocol/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/streams/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/streams/*.hpp")

add_executable (naranja_tests ${SOURCES})
target_link_libraries (naranja_tests naranja gtest gmock_main)
