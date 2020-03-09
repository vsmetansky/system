#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <logger.h>

void logg(char *message) {
    char *err_buff = strerror(errno);
    fprintf(stderr, message, err_buff);
}

void logg_term(char *message) {
    logg(message);
    exit(EXIT_FAILURE);
}

void logg_series_one(char *message, int n, ...) {
    va_list valist;
    va_start(valist, n);
    for (int i = 0; i < n; i++) {
        if (va_arg(valist, int) < 0) {
            logg(message);
            break;
        }
    }
    va_end(valist);
}

void logg_series_one_term(char *message, int n, ...) {
    va_list valist;
    va_start(valist, n);
    for (int i = 0; i < n; i++) {
        if (va_arg(valist, int) < 0) {
            logg_term(message);
        }
    }
    va_end(valist);
}