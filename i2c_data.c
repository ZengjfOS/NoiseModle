#include <stdio.h>
#include <string.h>
#include <linux/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "i2c_data.h"
#include <linux/i2c-dev.h>  
#include <linux/i2c.h>

int i2c_data_read_str (int fd, int addr, unsigned char *buf, int count) {
    int ret;
    struct i2c_rdwr_ioctl_data i2c_data;

    i2c_data.nmsgs = 1; 
    i2c_data.msgs  = (struct i2c_msg*)malloc(i2c_data.nmsgs*sizeof(struct i2c_msg));
    if(!i2c_data.msgs) {
        perror("i2c_data_read_byte functionmalloc error");
        exit(1);
    }

    ioctl(fd, I2C_TIMEOUT, 4); /*超时时间*/
    ioctl(fd, I2C_RETRIES, 8); /*重复次数*/

    (i2c_data.msgs[0]).len      = count;    //读出的数据
    (i2c_data.msgs[0]).addr     = addr;     // i2c 设备地址
    (i2c_data.msgs[0]).flags    = I2C_M_RD; //read
    (i2c_data.msgs[0]).buf      = buf;      //存放返回值的地址。

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if(ret<0) {
        perror("i2c_data_read_byte ioctl error.\n");
        return ret;
    }
    free(i2c_data.msgs);

    return 0;
}
