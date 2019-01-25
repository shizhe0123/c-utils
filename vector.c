#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "vector.h"
#include "sort_find.h"

static void __vector_element_sort(vector_handle *handle)
{
    items_sort((void *)((UINT8 *)handle->storage + handle->element_size), handle->count - 1, handle->element_size);
}


vector_handle *vector_create(UINT32 element_size)
{
    vector_handle *vector = NULL;

    if(0 == element_size)
    {
        printf("Invalid element_size(%d)\n", element_size);
        vector = NULL;
    }
    else
    {
        vector = (vector_handle *)malloc(sizeof(vector));
        if(NULL == vector)
        {
            printf("Vector create malloc failed\n");
            vector = NULL;
        }
        else
        {/*鏌ユ壘绠楁硶闇�瑕佸厛鍒嗛厤涓�涓猠lement绌洪棿锛屾绌洪棿涓嶅瓨鍌╡lement淇℃伅*/
            vector->storage = (void *)malloc(element_size);
            if(NULL == vector->storage)
            {
                printf("Vector malloc element failed\n");
                free(vector);
                vector = NULL;
            }
            else
            {
                vector->count = 1;
                vector->element_size = element_size;
            }
        }
    }

    return vector;
}

INT8 vector_add_element(vector_handle *handle, const void *elements, UINT32 element_num)
{
    INT8 result = 0;

    if((NULL == handle) || (elements == NULL) || (0 == element_num))
    {
        printf("Invalid parameters\n");
        result = VECTOR_OPER_FAILED;        
    }
    else
    {
        UINT8 i = 0;
        INT8 *temp = NULL;

        for(i = 0; i < element_num; i++)
        {
            temp = (INT8 *)((UINT8 *)elements +  i * handle->element_size);
        
            if(NULL != vector_find_element(handle, (const INT8 *)temp))
            {
                printf("This element(%s) has existed\n", temp);
                result = VECTOR_ELE_EXISTED;
            }
            else
            {
                UINT32 cur_size = handle->element_size * handle->count;
                UINT32 append_size = handle->element_size * element_num;
                
                temp = realloc(handle->storage, cur_size + append_size);
                if(NULL == temp)
                {
                    printf("Add element realloc failed\n");
                    result = VECTOR_LEAK_MEM;
                }
                else
                {
                    memcpy((void *)((INT8 *)temp + cur_size), elements, append_size);
                    handle->storage = temp;
                    handle->count += 1;
                    /*鎺掑簭*/
                    __vector_element_sort(handle);
                    result = VECTOR_OPER_SUCCESS;
                }
            }
        }
    }

    return result;
}

vector_handle *vector_find_element(vector_handle *handle, const INT8 *target)
{
    return item_find(target, (void *)((UINT8 *)handle->storage + handle->element_size), handle->count - 1, handle->element_size);
}

INT8 vector_delete_element(vector_handle *handle, const INT8 *target)
{
    INT8 result = 0;

    if((NULL == handle) || (NULL == target))
    {
        printf("Invalid parameter(NULL)\n");
        result = VECTOR_OPER_FAILED;
    }
    else
    {
        void *element = NULL;
        
        element = (UINT8 *)vector_find_element(handle, target);
        if(NULL == element)
        {
            printf("This(%s) element is not existed\n", target);
            result = VECTOR_ELE_NOT_EXISTED;
        }
        else
        {
            UINT8 *storage_end = (UINT8 *)(handle->storage) + (handle->count * handle->element_size);
            UINT8 *del_ele_end = (UINT8 *)element + handle->element_size;

            memmove(element, del_ele_end, storage_end - del_ele_end);   /*灏嗗垹闄ゆ潯鐩悗闈㈢殑鏉＄洰鎷疯礉鍒板垹闄ゆ潯鐩殑浣嶇疆*/
            handle->count -= 1;
            element = realloc(handle->storage, (handle->element_size * handle->count));
            if(NULL == element)
            {
                printf("Element delete realloc failed\n");
                result = VECTOR_LEAK_MEM;
            }
            else
            {
                handle->storage = element;
                __vector_element_sort(handle);
                result = VECTOR_OPER_SUCCESS;
            }
        }
    }

    return result;
}

void vector_destroy(vector_handle *handle)
{
    if(NULL == handle)
    {
        printf("Invalid parameter(NULL)\n");
    }
    else
    {
        free(handle->storage);
        free(handle);
        handle = NULL;
    }
}

