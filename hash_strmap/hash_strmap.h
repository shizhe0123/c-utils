#ifndef HASH_STRMAP_H
#define HASH_STRMAP_H

#include "datatype.h"

enum
{
    HASHTAB_LEAK_MEM = -12,
    HASHTAB_PARA_ERR = -11,
    HASHTAB_ELE_NOT_EXISTED = -3,
    HASHTAB_ELE_EXISTED = -2,
    HASHTAB_OPER_FAILED = -1,
    HASHTAB_OPER_SUCCESS = 0
};


/*****************************************************************************
 * @brief hash_strmap_init
 * @param[in] UINT32 capacity:哈希表容量    
             UINT32 value_size:key-value对应关系中的value大小
 * @param[out] none
 * @return:哈希表操作句柄
 * @details 初始化哈希表
 * @author sdc
 * @note:1. capacity必须是2的整数次幂
         2. 由于key-value中的value的第一个元素必须是key，因此value_size必须大于2
*****************************************************************************/
extern void *hash_strmap_create(UINT32 capacity, UINT32 value_size, INT8 *res);
/*****************************************************************************
 * @brief hash_strmap_get
 * @param[in] void *hash_strmap_handle  
             const INT8 *key           
 * @param[out] none
 * @return extern
 * @details 根据key从哈希表中获取value
 * @author sdc
*****************************************************************************/
extern void *hash_strmap_get(void *hash_strmap_handle, const INT8 *key, INT8 *res);
/*****************************************************************************
 * @brief hash_strmap_insert
 * @param[in] void *hash_strmap_handle  
             const INT8 *key           
             void *value               
 * @param[out] none
 * @return extern
 * @details 向哈希表中插入key:value
 * @author sdc
 * @note:value中的第一个元素必须是key值
*****************************************************************************/
extern INT8 hash_strmap_insert(void *hash_strmap_handle, const INT8 *key, void *value);
/*****************************************************************************
 * @brief hash_strmap_delete
 * @param[in] void *hansh_strmap_handle  
             INT8 *string               
 * @param[out] none
 * @return extern
 * @details 根据key删除哈希表中的key:value
 * @author sdc
*****************************************************************************/
extern INT8 hash_strmap_delete(void *hansh_strmap_handle, const INT8 *key);
/*****************************************************************************
 * @brief hash_strmap_deinit
 * @param[in] void *hash_strmap_handle  
 * @param[out] none
 * @return extern
 * @details deinit哈希表
 * @author sdc
*****************************************************************************/
extern void hash_strmap_destroy(void *hash_strmap_handle);
#endif
