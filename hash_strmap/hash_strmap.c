#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "vector.h"
#include "hash_strmap.h"

enum
{
    HASH_TABLE_ELEMENT_NOEXISTS = 0,    /*不存在数据*/
    HASH_TABLE_ELEMENT_EXISTS,          /*存在数据*/
};

typedef struct
{
    UINT32 exists;          /*此hash值的位置是否存在数据*/
    vector *content;        /*内容*/
}hash_table_element;

typedef struct
{
    //UINT8 *maps;          /*位图，表示有哪些位置存储了元素*/
    UINT32 capacity;        /*此哈希表的容量*/
    UINT32 element_size;    /*每个value的大小*/
    hash_table_element *hash_table;
}hash_strmap;

/*****************************************************************************
 * @brief __hash
 * @param[in] const INT8 *str  
 * @param[out] none
 * @return static
 * @details 计算字符串的hash值
 * @author sdc
*****************************************************************************/
static UINT32 __hash(const INT8 *str)
{
	UINT32 hash = 5381;
	INT8 c;

	while (c = *str++) 
    {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}


void *hash_strmap_create(UINT32 capacity, UINT32 value_size, INT8 *res)
{
    hash_strmap *handle = NULL;

    if((0 != (capacity & (capacity -1))) || (2 > value_size))
    {
        printf("Wrong para\n");
        *res = HASHTAB_PARA_ERR;
        return NULL;
    }

    handle = malloc(sizeof(hash_strmap));
    if(NULL == handle)
    {
        printf("hash table handle malloc error\n");
        *res = HASHTAB_LEAK_MEM;
    }
    else
    {
        memset(handle, 0, sizeof(hash_strmap));
        handle->hash_table = malloc(capacity * sizeof(hash_table_element));
        if(NULL == handle->hash_table)
        {
            printf("hash table malloc error\n");
            free(handle);
            *res = HASHTAB_LEAK_MEM;
        }
        else
        {
            memset(handle->hash_table, 0, capacity * sizeof(hash_table_element));
            handle->capacity = capacity;
            handle->element_size = value_size;
            *res = HASHTAB_OPER_SUCCESS; 
        }
    }

    return handle;
}

INT8 hash_strmap_insert(void *hash_strmap_handle, const INT8 *key, void *value)
{
    UINT32 hash_pos = 0;
    INT8 rc = 0;
    hash_strmap *handle = (hash_strmap *)hash_strmap_handle;

    if((NULL == handle) || (NULL == key) || (NULL == value))
    {
        printf("wrong para\n");
        return HASHTAB_PARA_ERR;
    }

    hash_pos = __hash(key) & (handle->capacity - 1);    /*mod handle->capacity*/
    printf("hash pos:%d\n", hash_pos);
    if(HASH_TABLE_ELEMENT_EXISTS == handle->hash_table[hash_pos].exists) /*查看是否已存在元素*/
    {
        INT8 v_rc = 0;

        v_rc = vector_add_element(handle->hash_table[hash_pos].content, value, 1);
        if((VECTOR_OPER_FAILED == v_rc) || (VECTOR_ELE_EXISTED == v_rc))
        {
            printf("hash vector add element failed\n");
            rc = HASHTAB_OPER_FAILED;
        }
        else
        {
            rc = HASHTAB_OPER_SUCCESS;
        }
    }
    else    /*不存在 */
    {
        vector *vector_handle = NULL;
        
        vector_handle = vector_create(handle->element_size);
        if(NULL == vector_handle)
        {
            printf("hash malloc vector create error\n");
            rc = HASHTAB_LEAK_MEM;
        }
        else
        {
            if(VECTOR_OPER_FAILED == vector_add_element(vector_handle, value, 1))
            {
                printf("hash vector add element failed\n");
                vector_destroy(vector_handle);
                rc = HASHTAB_OPER_FAILED;
            }
            else
            {
                handle->hash_table[hash_pos].exists = HASH_TABLE_ELEMENT_EXISTS;
                handle->hash_table[hash_pos].content = vector_handle;
                rc = HASHTAB_OPER_SUCCESS;
            }
        }
    }

    return rc;
}

void *hash_strmap_get(void *hash_strmap_handle, const INT8 *key, INT8 *res)
{
    UINT32 hash_pos = 0;
    void *value = NULL;
    hash_strmap *handle = (hash_strmap *)hash_strmap_handle;

    if((NULL == handle) || (NULL == key) || (NULL == res))
    {
        printf("wrong para\n");
        *res = HASHTAB_PARA_ERR;
        return NULL;
    }
    
    hash_pos = __hash(key) & (handle->capacity - 1);    /*mod handle->capacity*/
    if(HASH_TABLE_ELEMENT_EXISTS == handle->hash_table[hash_pos].exists)
    {
        value = vector_find_element(handle->hash_table[hash_pos].content, key);
        if(NULL == value)
        {
            *res = HASHTAB_ELE_NOT_EXISTED;
        }
        else
        {
            *res = HASHTAB_ELE_EXISTED;
        }
    }
    else    /*不存在该key*/
    {
        *res = HASHTAB_ELE_NOT_EXISTED;
    }

    return value;
}

INT8 hash_strmap_delete(void *hash_strmap_handle, const INT8 *key)
{
    UINT32 hash_pos = 0;
    INT8 rc = 0;
    hash_strmap *handle = (hash_strmap *)hash_strmap_handle;

    if((NULL == handle) || (NULL == key))
    {
        printf("wrong para\n");
        return HASHTAB_PARA_ERR;
    }
    
    hash_pos = __hash(key) & (handle->capacity - 1);    /*mod handle->capacity*/
    
    if(HASH_TABLE_ELEMENT_EXISTS == handle->hash_table[hash_pos].exists)
    {
        INT8 v_rc = 0;
        
        v_rc == vector_delete_element(handle->hash_table[hash_pos].content, key);
        if((VECTOR_ELE_NOT_EXISTED == v_rc) || (VECTOR_OPER_SUCCESS == v_rc))
        {
            printf("hash table delete ele success\n");
            rc = HASHTAB_OPER_SUCCESS;
        }
        else
        {
            printf("hash table delete ele failed\n");
            rc = HASHTAB_OPER_FAILED;
        }
    }
    else
    {
        printf("hash table(pos:%d) element is not existed\n", hash_pos);
        rc = HASHTAB_OPER_SUCCESS;
    }

    return rc;
}
void hash_strmap_destroy(void *hash_strmap_handle)
{
    UINT32 i = 0;
    hash_strmap *handle = (hash_strmap *)hash_strmap_handle;
    
    if(NULL == handle)
    {
        printf("wrong para\n");
        return;
    }
    for(i = 0; i < handle->capacity; i++)
    {
        if(HASH_TABLE_ELEMENT_EXISTS == handle->hash_table[i].exists)   /*查看此位置是否存在数据*/
        {
            vector_destroy(handle->hash_table[i].content);
        }
    }

    free(handle->hash_table);
    free(handle);
}
