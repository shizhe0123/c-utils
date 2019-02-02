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
    device_register dev_reg  = {0};
    cloud.vector = vector_create(sizeof(device_register));
    if(NULL == cloud.vector)
    {
        printf("vector create error\n");
        return -1;
    }

    strcpy(dev_reg.mac, "123456");
    vector_add_element(cloud.vector, (void *)&dev_reg, 1);
    strcpy(dev_reg.mac, "789");
    vector_add_element(cloud.vector, (void *)&dev_reg, 1);
    strcpy(dev_reg.mac, "abc");
    vector_add_element(cloud.vector, (void *)&dev_reg, 1);
    strcpy(dev_reg.mac, "0123456");
    vector_add_element(cloud.vector, (void *)&dev_reg, 1);
    vector_add_element(cloud.vector, (void *)&dev_reg, 1);
    vector_delete_element(cloud.vector, "789");
    vector_delete_element(cloud.vector, "789");
    return 0;
}
