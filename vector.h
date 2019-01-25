#ifndef VECTOR_H
#define VECTOR_H

enum
{
    VECTOR_LEAK_MEM = -12,
    VECTOR_ELE_NOT_EXISTED = -3,
    VECTOR_ELE_EXISTED = -2,
    VECTOR_OPER_FAILED = -1,
    VECTOR_OPER_SUCCESS = 0
    
};


typedef struct
{
    void* storage;      /*存储的数据内容*/
    UINT32 count;       /*存储的数量*/
    UINT32 element_size; /*每个数据内容的大小*/
}vector;

typedef vector vector_handle;

/*****************************************************************************
 * @brief vector_create
 * @param[in] UINT32 element_size:条目的大小 
 * @param[out] none
 * @return extern
 * @details 创建vector
 * @author sdc
*****************************************************************************/
extern  vector_handle   *vector_create(UINT32 element_size);
/*****************************************************************************
 * @brief vector_find_element
 * @param[in] vector_handle *handle:vector句柄  
             const INT8 *target:需要查找的字符串     
 * @param[out] none
 * @return extern
 * @details 查找条目
 * @author sdc
 * @note 目前只支持字符串查找
*****************************************************************************/
extern  vector_handle   *vector_find_element(vector_handle *handle, const INT8 *target);
/*****************************************************************************
 * @brief vector_add_element
 * @param[in] vector_handle *handle:vector句柄  
             const void *elements:需要添加的条目地址   
             UINT32 element_num:需要添加的条目数量
 * @param[out] none
 * @return extern
 * @details 添加条目
 * @author sdc
*****************************************************************************/
extern  INT8 vector_add_element(vector_handle *handle, const void *elements, UINT32 element_num);
/*****************************************************************************
 * @brief vector_delete_element
 * @param[in] vector_handle *handle:vector句柄  
             const INT8 *target:需要删除的字符串   
 * @param[out] none
 * @return extern
 * @details 删除条目
 * @author sdc
*****************************************************************************/
extern  INT8 vector_delete_element(vector_handle *handle, const INT8 *target);
/*****************************************************************************
 * @brief vector_destroy
 * @param[in] vector_handle *handle:vector句柄   
 * @param[out] none
 * @return extern
 * @details 删除vector
 * @author sdc
*****************************************************************************/
extern  void vector_destroy(vector_handle *handle);

#endif
