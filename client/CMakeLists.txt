cmake_minimum_required(VERSION 3.7)
add_executable(client
    client.c
    src/mysocket.c
    src/mystruct.c
    src/parser.c
    src/java_rules_of_the_grammer.c
)
