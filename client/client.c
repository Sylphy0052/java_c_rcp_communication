// #include <stdio.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

#include <stdlib.h>

#include "src/mysocket.h"
#include "src/mystruct.h"
#include "src/parser.h"
#include "src/java_rules_of_the_grammer.h"
#include "src/task.h"
#include "src/person.h"

int main(int argc, char const *argv[]) {
    int sock = connect_socket();
    struct byte_struct recv_bytes = send_and_receive_socket(sock, "Get Task\n");
    struct stream s = parse(recv_bytes);
    struct task *t = malloc(sizeof(struct task));
    convert_task(&s, t);
    show_task(t);
    struct person *p = malloc(sizeof(struct person));
    convert_person(p, t);
    send_person("Call Task", p);
    printf("fin\n");
    return 0;
}
