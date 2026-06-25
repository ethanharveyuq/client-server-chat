cmake_minimum_required(VERSION 3.20)
project(server-client-chatroom)

set(CMAKE_CXX_STANDARD 20)

add_executable(server
    src/main.cpp
    src/server.cpp
)

add_executable(client
    src/client.cpp
)

target_include_directories(server PRIVATE include)
target_include_directories(client PRIVATE include)