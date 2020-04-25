#include<stdio.h>
#include<stdlib.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
 
int main()
{
    unsigned long x = 0;
    unsigned long y = 0;
    syscall(225, 1234);
    return 0;
}