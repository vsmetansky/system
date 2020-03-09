#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/time.h>

#include <logger.h>

#define ARG_NUM 1
#define TIMER_SEC 5
#define BUF_SIZE 1024

void read_setup(fd_set *readfds);
void timer_setup(struct timeval *t);
void select_setup(fd_set *readfds, struct timeval *t);
bool stdin_active(void);

int main(int argc, char **argv) {
    if (argc < ARG_NUM + 1) {
        return EXIT_FAILURE;
    }
    
    while(true) {
        if (stdin_active()) {
            char buf[BUF_SIZE];
            char b_read = 0;
            if ((b_read = read(STDIN_FILENO, buf, BUF_SIZE)) < 0) {
                logg_term("Error reading data");
            } else {
                printf("\n%s:\n", argv[1]);
                write(STDOUT_FILENO, buf, b_read);
            }
        } else {
            logg(argv[1]);
        }
    }
    
    return EXIT_SUCCESS;
}

void read_setup(fd_set *readfds) {
    FD_ZERO(readfds);
    FD_SET(STDIN_FILENO, readfds);
}

void timer_setup(struct timeval *t) {
    t->tv_sec = TIMER_SEC;
    t->tv_usec = 0;
}

void select_setup(fd_set *readfds, struct timeval *t) {
    read_setup(readfds);
    timer_setup(t);
}

bool stdin_active(void) {
    fd_set readfds;
    struct timeval timer;

    select_setup(&readfds, &timer);

    int active = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timer);

    if (active < 0) {
        exit(EXIT_FAILURE);
    }
    if (active > 0) {
        return true;
    }
    return false;
}
