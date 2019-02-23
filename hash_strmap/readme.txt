1.
vector的数据结构为：
typedef struct
{
    UINT32 count;           /*存储的数量*/
    UINT32 element_size;    /*每个数据内容的大小*/
    void* storage;          /*存储的数据内容。storage中存储的结构体的第一个成员必须为字符串*/
}vector;

2.应用场景：
作为网关设备，将收到的数据根据mac地址分发到不同的设备。
vector.storage中存储的数据结构为：
typedef struct
{
    INT8 mac[16];
    ...
    data_callback cb;
    void *cb_para;
}device_info;

从收到的数据中提取出mac以后，从网关设备本地存储的各设备中根据mac来查找相应的设备，将数据分发出去。

查找设备时用到了qsort()和bsearch()两个库函数。因此对于device_info结构体的要求是：mac必须为该结构体的第一个成员。

3. 使用哈希表时，key--value必须在同一个结构体中，并且key必须是结构体的第一元素。