# TODO: Set the cmake minimum version to 3.25, make a project named homework_2, and set the C++ standard to 20.
cmake_minimum_required(VERSION 3.25)
project(homework_2)
set(CMAKE_CXX_STANDARD 20)

# TODO: Find two required packages: GTest and Threads. 
find_package(GTest REQUIRED)
enable_testing()
find_package(Threads REQUIRED)
# NOTE: Don't worry about what Threads does until lab 3, we're using it for testing.

# Library for client server functions.
add_library(client_server_lib STATIC src/client_server.cpp)
target_include_directories(client_server_lib PUBLIC include)

# Executable for manual runs of the server.
add_executable(server test_manual/server_driver.cpp)
target_include_directories(server PRIVATE include)
target_link_libraries(server PUBLIC client_server_lib)

# Executable for manual runs of the client.
add_executable(client test_manual/client_driver.cpp)
target_include_directories(client PRIVATE include)
target_link_libraries(client PUBLIC client_server_lib)




# TODO: Set up a test case called test_client_server with test/test_client_server.cpp as the source.
#       Link the test against GTest::gtest_main AND client_server_lib. Make sure the test is runnable
#       through CTest.
#is this right?
#include(CTest)




add_executable(test_client_server src/client_server.cpp test/test_client_server.cpp)
target_link_libraries(test_client_server GTest::gtest_main)
target_include_directories(test_client_server PRIVATE include) 

gtest_discover_tests(test_client_server)