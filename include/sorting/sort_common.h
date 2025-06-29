#ifndef SORT_COMMON_H
#define SORT_COMMON_H

#include <stddef.h>
#include <string.h>

/* ============================================================================
 * 类型定义和常量
 * ============================================================================
 */

typedef int (*compare_func_t)(const void *a, const void *b);

typedef enum {
  SORT_SUCCESS = 0,
  SORT_ERROR_NULL_POINTER = -1,
  SORT_ERROR_INVALID_LENGTH = -2,
  SORT_ERROR_ALLOCATION_FAILED = -3,
  SORT_ERROR_THREAD_FAILED = -4
} sort_result_t;

/** 排序统计信息 */
typedef struct {
  size_t comparisons;     /**< 比较次数 */
  size_t movements;       /**< 元素移动次数 */
  double time_elapsed_ms; /**< 排序耗时(毫秒) */
} sort_stats_t;

/**
 * ===========================================================================
 * Commonly Compare Function
 * ===========================================================================
 */

int compare_integers(const void *a, const void *b);
int compare_strings(const void *a, const void *b);

#endif