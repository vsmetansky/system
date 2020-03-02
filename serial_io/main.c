#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <headers/logger.h>

#define ARG_NUM 2

int main(int argc, char **argv) {
    if (argc < ARG_NUM + 1) {
        return EXIT_FAILURE;
    }
    int i = open(argv[1], O_RDONLY);
    if (i < 0) log_term("Error opening file");

    int o = open(argv[2], O_WRONLY);
    if (o < 0) log_term("Error opening file");


    return EXIT_SUCCESS;
}