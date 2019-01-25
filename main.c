#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "vector.h"

typedef struct
{
    vector_handle *vector;
}cloud_data;

typedef struct
{
    INT8 mac[16];
}device_register;



int main(int argc, char *argv[])
{
    cloud_data cloud = {0};
    device_register dev = {"123456"};
    INT8 ret = 0;
    
    cloud.vector = vector_create(sizeof(device_register));
    if(NULL == cloud.vector)
    {
        printf("vector create error\n");
        return -1;
    }

    ret = vector_add_element(cloud.vector, (void *)&dev, 1);
    printf("vector add result:%d\n", ret);
 //   getchar();
    return 0;
}
