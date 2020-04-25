#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/sched.h>
 
 
MODULE_LICENSE("Dual BSD/GPL");

// sudo cat /proc/kallsyms | grep sys_call_table

#define SYS_CALL_TABLE_ADDRESS 0xffffffff82000280   //sys_call_table对应的地址
#define VICTIM_CALL_NUM 223                        //系统调用号为2243
#define HELP_CALL_NUM 224
#define HELLO_CALL_NUM 225

int orig_cr0;                                       //用来存储cr0寄存器原来的值
unsigned long *sys_call_table_my=0;

typedef unsigned long d_addr_t;
typedef unsigned char d_uchar;

unsigned int array1_size = 16;
d_uchar unused1[64];
d_uchar array1[160] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
d_uchar unused2[64];
d_uchar array2[512 * 4096]; 
d_uchar temp;
// You need to Open Array2 First.
 
static void(*syscall_saved_victim)(d_addr_t, d_addr_t);   //定义一个函数指针，用来保存一个系统调用
static d_addr_t(*syscall_saved_help)(d_addr_t);
static void(*syscall_saved_hello)(int);
 
static int clear_cr0(void)                          //使cr0寄存器的第17位设置为0（内核空间可写）
{
    unsigned int cr0=0;
    unsigned int ret;
    asm volatile("movq %%cr0,%%rax":"=a"(cr0));     //将cr0寄存器的值移动到eax寄存器中，同时输出到cr0变量中
    ret=cr0;
    cr0&=0xfffffffffffeffff;                        //将cr0变量值中的第17位清0,将修改后的值写入cr0寄存器
    asm volatile("movq %%rax,%%cr0"::"a"(cr0));     //将cr0变量的值作为输入，输入到寄存器eax中，同时移动到寄存器cr0中
    return ret;
}
 
static void setback_cr0(int val)                    //使cr0寄存器设置为内核不可写
{
    asm volatile("movq %%rax,%%cr0"::"a"(val));
}
 
static void sys_mycall_victim(d_addr_t secret_offset, d_addr_t prob_offset) //定义自己的系统调用
{
    printk("Get %lx %lx\n",secret_offset,prob_offset);
    volatile d_uchar temp;
    volatile int z;
    d_uchar *a2tmp = array2 + array1[secret_offset] * 4096 + prob_offset;
    asm volatile ("mfence\n" ::: "memory");
    asm volatile ("clflush 0(%0)\n" : : "c"(&array1_size) : "eax");
    asm volatile ("mfence\n" ::: "memory");
    asm volatile ("clflush 0(%0)\n" : : "c"(&secret_offset) : "eax");
    asm volatile ("mfence\n" ::: "memory");

    if(secret_offset < array1_size)
        temp = *a2tmp;
}

static d_addr_t sys_mycall_help(d_addr_t phy_addr)
{
    void *vir_addr;
    printk("Get Address is %lx\n", phy_addr);
    if (phy_addr == 1) {
        printk("DONG: Array 1 is: 0x%p\n", array1);
        return (d_addr_t)array1;
    } else if (phy_addr == 2){
        printk("DONG: Array 2 is: 0x%p\n", array2);
        return (d_addr_t)array2;
    } else {
        printk("DONG: PHY ADD is: 0x%p\n", phy_addr);
        printk("DONG: VIR ADD is: 0x%p\n", vir_addr);
        return phy_addr;
    }
}

static void sys_mycall_hello(int a){
    printk("Hello World. %d\n", a);
} 

static int __init call_init(void)
{
    sys_call_table_my=(unsigned long*)(SYS_CALL_TABLE_ADDRESS);
    printk("call_init......\n");
    // Function 1
    syscall_saved_victim=(void(*)(d_addr_t, d_addr_t))(sys_call_table_my[VICTIM_CALL_NUM]);     //保存系统调用表中的NUM位置上的系统调用
    orig_cr0=clear_cr0();                                                                       //使内核地址空间可写
    sys_call_table_my[VICTIM_CALL_NUM]=(unsigned long) &sys_mycall_victim;                      //用自己的系统调用替换NUM位置上的系统调用
    setback_cr0(orig_cr0);                                                                      //使内核地址空间不可写
    // Function 2
    syscall_saved_help=(d_addr_t(*)(d_addr_t))(sys_call_table_my[HELP_CALL_NUM]);              
    orig_cr0=clear_cr0();                                               
    sys_call_table_my[HELP_CALL_NUM]=(unsigned long) &sys_mycall_help; 
    setback_cr0(orig_cr0);                                              

    // Function test
    syscall_saved_hello=(void(*)(int))(sys_call_table_my[HELLO_CALL_NUM]);
    orig_cr0=clear_cr0();  
    sys_call_table_my[HELLO_CALL_NUM]=(unsigned long) &sys_mycall_hello;
    setback_cr0(orig_cr0);

    return 0;
}
 
static void __exit call_exit(void)
{
    printk("call_exit......\n");
    orig_cr0=clear_cr0();
    sys_call_table_my[VICTIM_CALL_NUM]=(unsigned long)syscall_saved_victim;//将系统调用恢复
    sys_call_table_my[HELP_CALL_NUM] = (unsigned long)syscall_saved_help;
    sys_call_table_my[HELLO_CALL_NUM] = (unsigned long)syscall_saved_hello;
    setback_cr0(orig_cr0);
}
 
module_init(call_init);
module_exit(call_exit);