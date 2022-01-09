set(PROJECT_N tcpserver)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/tcp/server/*.cpp SOURCE_DIR)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
message("src files:")
foreach(file ${SOURCE_DIR})
        message(STATUS ${file})
endforeach()

add_executable(${PROJECT_N} main.cpp)

target_include_directories(${PROJECT_N} PUBLIC include)
