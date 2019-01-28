#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"

/*****************************************************************************
 * @brief __item_cmp
 * @param[in] const void *a
             const void *b
 * @param[out] none
 * @return static
 * @details 字符串比较
 * @author sdc
*****************************************************************************/
static INT32 __item_cmp(const void *a, const void *b)
{
    return strcmp((INT8 *)b, (INT8 *)a);
}

/*****************************************************************************
 * @brief item_find
 * @param[in] INT8 *target
             void *src_addr
             UINT8 item_count
             UINT32 item_size
 * @param[out] none
 * @return void
 * @details 使用二分查找，从src_addr中查找target
 * @author sdc
*****************************************************************************/
void *item_find(INT8 *target, void *src_addr, UINT8 item_count, UINT32 item_size)
{
    return bsearch(target, src_addr, item_count, item_size, __item_cmp);
}

/*****************************************************************************
 * @brief items_sort
 * @param[in] void *src_addr
             UINT8 items_count
             UINT32 item_size
 * @param[out] none
 * @return
 * @details 将src_addr指向的内容进行排序
 * @author sdc
*****************************************************************************/
void items_sort(void *src_addr, UINT8 items_count, UINT32 item_size)
{
    qsort(src_addr, items_count, item_size, __item_cmp);
}
