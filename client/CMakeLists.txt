cmake_minimum_required(VERSION 3.7)
add_executable(client
    client.c
    src/hexdump.c
    src/mysocket.c
    src/mystruct.c
)
