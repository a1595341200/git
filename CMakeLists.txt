cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory("./src/TCP/server")
add_subdirectory("./src/TCP/client")
add_subdirectory("./src/1.9/1.9.1")
