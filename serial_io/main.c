#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <logger.h>

#define ARG_NUM 2

int main(int argc, char **argv) {
    if (argc < ARG_NUM + 1) 
        return EXIT_FAILURE;
    
    int i = open(argv[1], O_RDONLY);
    if (i < 0) logg_term("Error opening file");

    int o = open(argv[2], O_WRONLY | O_CREAT, 644);
    if (o < 0) logg_term("Error opening file");

    if (close(i) < 0) logg_term("Error closing file");
    if (close(o) < 0) logg_term("Error closing file");

    return EXIT_SUCCESS;
}