#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "sort_common.h"

sort_result_t generic_merge_sort(void *arrp[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats);

                                 
#ifdef __cplusplus
}
#endif
#endif
