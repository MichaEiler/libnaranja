file (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/common/*.hpp")

add_executable (naranja_tests ${SOURCES})
target_link_libraries (naranja_tests naranja gtest gmock_main)
target_include_directories(naranja_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/")
