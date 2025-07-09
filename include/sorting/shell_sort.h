#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "sorting/sort_common.h"

// 希尔排序的思想是使数组中任意间隔为H的元素都是有序的。这样
// 的数组成为H有序数组。换言之，H有序数组就是将H个互相独立的
// 有序数组交织在一起组成的数组。在进行排序时，如果H很大，就
// 能将元素移动到很远的地方，为实现更小的H有序数组奠定基础。
//
// 

extern sort_result_t generic_shell_sort(
    void *arr,
    size_t arr_len,
    size_t element_size,
    compare_func_t cmp
);
 

#ifdef __cplusplus
}
#endif
#endif // SHELL_SORT_H