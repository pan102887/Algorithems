#ifndef SORT_COMMON_H
#define SORT_COMMON_H

#include <stddef.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 类型定义和常量
 * ============================================================================
 */


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

void incre_comparisons(sort_stats_t *stats);
void incre_movements(sort_stats_t *stats);


typedef int (*generic_compare_func_t)(const void * const a, const void * const b);
typedef int (*int_compare_func_t)(const int a, const int b);
typedef int (*string_compare_func_t)(const char * const a, const char * const b);

/**
 * ===========================================================================
 * Commonly Compare Function
 * ===========================================================================
 */

int compare_integers(const void * const a, const void * const b);
int compare_strings(const void * const a, const void * const b);


#ifdef __cplusplus
}
#endif
#endif