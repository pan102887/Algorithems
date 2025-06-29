#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "sort_common.h"

typedef int (*compare_func_t)(const void *a, const void *b);

sort_result_t generic_merge_sort(void *arr[], size_t len, compare_func_t cmp,
                                 sort_stats_t *stats);

void turn_on_merge_sort_debug(void);
                                 
#ifdef __cplusplus
}
#endif
#endif