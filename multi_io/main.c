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
bool stdin_availible(void);
int stdin_read(char *buf, int buf_size);
void stdout_write(char *label, char *buf, int b_num);

int main(int argc, char **argv) {
    if (argc < ARG_NUM + 1) {
        puts("You should provide 1 argument (label name)");
        return EXIT_FAILURE;
    }
    
    while(true) {
        if (stdin_availible()) {
            char buf[BUF_SIZE];
            stdout_write(argv[1], buf, stdin_read(buf, BUF_SIZE));
        } else {
            puts(argv[1]);
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

bool stdin_availible(void) {
    fd_set readfds;
    struct timeval timer;

    select_setup(&readfds, &timer);

    int availible = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timer);

    if (availible < 0) {
        exit(EXIT_FAILURE);
    }
    if (availible) {
        return true;
    }
    return false;
}

void stdout_write(char *label, char *buf, int b_num) {
    printf("\n%s: ", label);
    write(STDOUT_FILENO, buf, b_num);
    printf("\n");
}

int stdin_read(char *buf, int buf_size) {
    int b_read = 0;
    if ((b_read = read(STDIN_FILENO, buf, buf_size)) < 0) {
        logg_term("Error reading data");
    }
    return b_read;
}