#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "vector.h"
#include "hash_strmap.h"

typedef struct
{
    INT8 mac[16];
    INT32 test;
}device_register;



int main(int argc, char *argv[])
{
    void *hash_table = NULL;
    INT8 res = 0;
    device_register dev_reg  = {0};

    hash_table = hash_strmap_create(512, sizeof(device_register), &res);
    if(NULL == hash_table)
    {
        printf("hash table create failed\n");
        return 0;
    }

    strcpy(dev_reg.mac, "123");
    dev_reg.test = 123;
    hash_strmap_insert(hash_table, dev_reg.mac, (void *)&dev_reg);

    strcpy(dev_reg.mac, "abc");
    dev_reg.test = 0xabc;
    hash_strmap_insert(hash_table, dev_reg.mac, (void *)&dev_reg);

    strcpy(dev_reg.mac, "defa11");
    dev_reg.test = 0xF2;
    hash_strmap_insert(hash_table, dev_reg.mac, (void *)&dev_reg);

    dev_reg = *((device_register *)hash_strmap_get(hash_table, "123", &res));
    printf("res:%d, value = %d\n", res, dev_reg.test);

    hash_strmap_get(hash_table, "defa11", &res);
    printf("res:%d\n", res);

    printf("delete:%d\n", hash_strmap_delete(hash_table, "123"));

    hash_strmap_get(hash_table, "123", &res);
    printf("res:%d\n", res);

    return 0;
}
