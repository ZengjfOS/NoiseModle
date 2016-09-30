#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "i2c_data.h"

int main(int argc, char ** argv) {
    int fd, ret;

    fd = open("/dev/i2c-2", O_RDWR);
    if(fd < 0) {
        perror("open error\n");
    }

    unsigned char buffer[16] = {0};

    i2c_data_read_str (fd, 0x10, buffer, 7);
    i2c_data_read_str (fd, 0x10, buffer + 7, 7);
    i2c_data_read_str (fd, 0x10, buffer + 7, 2);

    int i = 0;
    for(; i < 15; i++) 
        printf("%02x ", buffer[i]);

    printf("%02x\n", buffer[i]);

    close(fd);

    return 0;
}
