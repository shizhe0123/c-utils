#include <stdio.h>
#include <stdint.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(uint32_t))

void print_arr(uint32_t arr[], uint32_t arr_len)
{
    uint32_t i = 0;

    for(i = 0; i < arr_len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    fflush(stdout);
}

void swap(uint32_t *a, uint32_t *b)
{
    uint32_t tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(uint32_t arr[], uint32_t arr_len)
{
    uint32_t i = 0;
    uint32_t j = 0;

    if((NULL == arr) || (0 == arr_len))
    {
        printf("check your para\n");
        return;
    }

    if(1 == arr_len)
    {
        printf("only 1 element\n");
        return;
    }

    for(i = 0; i < (arr_len - 1); i++)
    {
        for(j = i + 1; j > 0; j--)
        {
            if(arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
            }
        }
        print_arr(arr, arr_len);
    }

}

int main()
{
    uint32_t a[] = {12, 49, 2, 4, 8, 0};

    insertion_sort(a, ARR_SIZE(a));
    print_arr(a, ARR_SIZE(a));
    return 0;
}