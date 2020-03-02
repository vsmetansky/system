#include "../headers/logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void log(char *message) {
    char *err_buff = strerror(errno);
    fprintf(stderr, message, err_buff);
}

void log_term(char *message) {
    log(message);
    exit(EXIT_FAILURE);
}