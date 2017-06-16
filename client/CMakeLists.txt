cmake_minimum_required(VERSION 3.7)

include_directories(src)

add_executable(client
    client.c
    src/mysocket.c
    src/mystruct.c
    src/parser.c
    src/java_rules_of_the_grammer.c
    src/handle.c
    src/task.c
    src/person.c
    src/serialize.c
)
