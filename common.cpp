#include "common.h"

size_t get_rand_seed(){
    int fd;
    ssize_t len = 4;
    char buf[5] = {0,}; 
    size_t random;

    if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
        return 0;
    }
    if (read(fd, buf, len) != (ssize_t) len) {
        close(fd);
        return 0;
    }
    close(fd);
    memcpy(&random, buf, 4);

    return random;
}

size_t get_rand(size_t max){
    size_t random = rand() % max; // 난수 생성 // OZ1NG019
    return random;
}