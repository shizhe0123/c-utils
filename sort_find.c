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
 * @details 瀛楃涓叉瘮杈�
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
 * @details 浣跨敤浜屽垎鏌ユ壘锛屼粠src_addr涓煡鎵総arget
 * @author sdc
*****************************************************************************/
void *item_find(const INT8 *target, void *src_addr, UINT8 item_count, UINT32 item_size)
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
 * @details 灏唖rc_addr鎸囧悜鐨勫唴瀹硅繘琛屾帓搴�
 * @author sdc
*****************************************************************************/
void items_sort(void *src_addr, UINT8 items_count, UINT32 item_size)
{
    qsort(src_addr, items_count, item_size, __item_cmp);
}
