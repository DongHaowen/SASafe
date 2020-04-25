
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>

#define D_MMAP_LEN 256
#define D_PAGE_SIZE 512

int result;

int main()
{
    size_t karr1, karr2, secret_phy_addr, secret_ker_vir, prob_ker_vir;
    size_t malicious_x, malicious_y;
    int fd;
    int junk = 0;
    register uint64_t time1, time2;

    fd = open("/dev/expdev", O_RDWR);
    if(fd < 0){
        perror("Fail Open File.\n");
        return -1;
    }
    
    result = mmap(NULL, D_MMAP_LEN * D_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(result == MAP_FAILED){
        perror("Fail to MMAP.\n");
        return -1;
    }

    return 0;
}