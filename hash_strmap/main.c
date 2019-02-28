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
    device_register *test = NULL;
    hashtab_room_info_struct hash_room_info = {0};

    hash_table = hash_strmap_create(4, sizeof(device_register));
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


    do
    {
        test = (device_register *)hash_strmap_get_ele_by_index(hash_table, hash_room_info.index, &hash_room_info);
        if(NULL != test)
        {
            INT8 i = 0;
            device_register *fun = NULL;

            printf("Find element at %d, count:%d\n", hash_room_info.index, hash_room_info.count);

            for(i = 0; i < hash_room_info.count; i++)
            {
                fun = test + i;
                printf("(%p)<%d>:%d\n", fun, hash_room_info.index, fun->test);
            }
            hash_room_info.index++;
        }
    }while(NULL != test);


    return 0;
}
