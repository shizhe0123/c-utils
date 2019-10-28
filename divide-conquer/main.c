#include <stdio.h>
#include <stdint.h>
#include <time.h>

uint64_t x_power(uint32_t x, uint32_t n)
{
    uint64_t y = 1;
    uint64_t tmp = 0;

    if(1 == n)
    {
        y = x;
    }
    else    //n != 1
    {
        if(1 == (n & 0x01)) //n 为奇数
        {
            y = x;
        }
        tmp = x_power(x, n >> 1);
        y *= tmp * tmp;
    }

    return y;
}

int main(int argc, char *argv[])
{
    uint64_t y = 1;
    uint32_t i = 0;

    struct timespec start = {0};
    struct timespec end = {0};

    clock_gettime(CLOCK_REALTIME, &start);
    printf("5 power:%lu\n", x_power(5, 16));
    clock_gettime(CLOCK_REALTIME, &end);
    printf("spend time:%d.%d\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
    for(i = 0; i < 16; i++)
    {
        y *= 5;
    }
    printf("time:%d\n", time(NULL));
    printf("y = %llu\n", y);
}