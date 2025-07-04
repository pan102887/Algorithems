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

#ifdef DEBUG
#define INCRE_COMPARITIONS(stats) incre_comparisons(stats)
#define INCRE_MOVEMENTS(stats) incre_movements(stats)
#else
#define INCRE_COMPARITIONS(stats)
#define INCRE_MOVEMENTS(stats)
#endif

#define GENERIC_SAMP_SIZE_SWAP(size, ap, bp) \
  do {\
    if ((size) <= 0) break;\
    size_t __SIZE = (size);\
    for (size_t i = 0; i < __SIZE; i++) {\
      ((char *)(ap))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i];\
      ((char *)(bp))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i];\
      ((char *)(ap))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i];\
    }\
  } while (0)


typedef int compare_func_t(const void * const a, const void * const b);
typedef void swap_func_t(void * const a, void * const b);


/**
 * ===========================================================================
 * Commonly Compare Function
 * ===========================================================================
 */

int compare_integers(const void * const a, const void * const b);
int generic_int_cmp(const int * const a, const int * const b);
void integers_swap(void * const a, void * const b);
int compare_strings(const void * const a, const void * const b);


#ifdef __cplusplus
}
#endif
#endif
