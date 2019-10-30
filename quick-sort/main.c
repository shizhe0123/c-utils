#include <stdio.h>
#include <stdint.h>

static void printf_arr(uint32_t *a, uint32_t len)
{
    uint32_t i = 0;

    for(i = 0; i < len; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    fflush(stdout);
}

static void swap(uint32_t *a, uint32_t *b)
{
    uint32_t temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(uint32_t arr[], int32_t start, int32_t end)
{
    uint32_t pivot = arr[start];
    int32_t i = 0;
    int32_t j = 0;

    if(start >= end)    //退出递归的条件
    {
        return;
    }

    for(i = start, j = i + 1; j < end; j++)
    {
        if(arr[j] < pivot)
        {//swap
            swap(&arr[i + 1], &arr[j]);
            i++;
        }
    }
    if(i != start)
    {
        swap(&arr[start], &arr[i]);
    }

    printf_arr(arr, end);

    quick_sort(arr, start, i);
    quick_sort(arr, i + 1, end);
}

int main() {
    uint32_t a[8] = {6, 10, 13, 5, 8, 3, 2, 11};
    uint32_t b[4] = {2, 5, 3, 6};
    quick_sort(a, 0, sizeof(a) / 4);
    printf_arr(a, 8);

    return 0;
}