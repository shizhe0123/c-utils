#ifndef SORT_FIND_H
#define SORT_FIND_H
#include "datatype.h"
extern  void    *item_find(const INT8 *mac, void *src_addr, UINT8 item_count, UINT32 item_size);
extern  void    items_sort(void *src_addr, UINT8 items_count, UINT32 item_size);
#endif
