#include <logger.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void logg(char *message) {
    char *err_buff = strerror(errno);
    fprintf(stderr, message, err_buff);
}

void logg_term(char *message) {
    logg(message);
    exit(EXIT_FAILURE);
}