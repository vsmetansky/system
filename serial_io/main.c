#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include <logger.h>

#define ARG_NUM 2
#define RWXR__R__ 0644
#define BUF_SIZE 256
#define OFFSET 32

int transmit(int a, int b);
void transform(char *buf, int buf_size);

int main(int argc, char **argv) {
    if (argc < ARG_NUM + 1) {
        logg("Invalid number of arguments\n");
        return EXIT_FAILURE;
    }
        
    int i = open(argv[1], O_RDONLY);
    if (i < 0) logg_term("Error opening file\n");
    int o = open(argv[2], O_WRONLY | O_CREAT, RWXR__R__);
    if (o < 0) logg_term("Error opening file\n");

    int b_num = transmit(i, o);
    printf("%i bytes were transmitted", &b_num);        

    if (close(i) < 0) logg_term("Error closing file\n");
    if (close(o) < 0) logg_term("Error closing file\n");

    return EXIT_SUCCESS;
}

void transform(char *buf, int bytes_num) {
    for (int i = 0; i < bytes_num; i++) {
        if(isalpha(buf[i])) buf[i] = buf[i] - OFFSET;
    }
}

int transmit(int a, int b) {
    char buf[BUF_SIZE];
    int b_read = 0;
    int b_wrote = 0;
    int b_total = 0;

    while ((b_read = read(a, buf, BUF_SIZE)) >= 0) {
        transform(buf, b_read);
        if ((b_wrote = write(b, buf, b_read)) < 0) {
            logg("Error writing data");
        } else {
            b_total += b_wrote;
        }    
    }

    return b_total;
}

