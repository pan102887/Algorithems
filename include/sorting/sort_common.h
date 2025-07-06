#ifndef SORT_COMMON_H
#define SORT_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

  /* ============================================================================
   * 类型定义和常量
   * ============================================================================
   */
  typedef enum
  {
    SORT_SUCCESS = 0,
    SORT_ERROR_NULL_POINTER = -1,
    SORT_ERROR_INVALID_LENGTH = -2,
    SORT_ERROR_ALLOCATION_FAILED = -3,
    SORT_ERROR_THREAD_FAILED = -4,
    SORT_ERROR_INVALID_ELEMENT_SIZE = -5,
  } sort_result_t;

  /** 排序统计信息 */
  typedef struct
  {
    size_t element_size;    /**< 元素大小(字节) */
    size_t array_length;    /**< 数组长度 */
    clock_t start_time;     /**< 排序开始时间 */
    clock_t end_time;       /**< 排序结束时间 */
    double time_elapsed_ms; /**< 排序耗时(毫秒) */
    size_t comparisons;     /**< 比较次数 */
    size_t movements;       /**< 元素移动次数 */
    size_t memory_used;     /**< 使用的内存大小(字节) */
    size_t max_mamory_used; /**< 最大内存使用(字节) */
  } sort_stats_t;

  extern void print_stats(const sort_stats_t *stats);

#if defined(DEBUG) && defined(PRINT_SORTING_INFO)
#define START_TIMMING(stats)        \
  do                                \
  {                                 \
    if (NULL == (stats))            \
    {                               \
      break;                        \
    }                               \
    (stats)->time_elapsed_ms = 0.0; \
    (stats)->comparisons = 0;       \
    (stats)->movements = 0;         \
    (stats)->memory_used = 0;       \
    (stats)->max_mamory_used = 0;   \
    (stats)->end_time = 0;          \
    (stats)->start_time = clock();  \
  } while (0)

#define STOP_TIMMING(stats)                                                                                   \
  do                                                                                                          \
  {                                                                                                           \
    if (NULL == (stats))                                                                                      \
    {                                                                                                         \
      break;                                                                                                  \
    }                                                                                                         \
    (stats)->end_time = clock();                                                                              \
    (stats)->time_elapsed_ms = ((double)((stats)->end_time - (stats)->start_time)) / CLOCKS_PER_SEC * 1000.0; \
  } while (0)

#define INCRE_COMPARISONS(stats) \
  do                             \
  {                              \
    if (NULL == (stats))         \
    {                            \
      break;                     \
    }                            \
    (stats)->comparisons++;      \
  } while (0)

#define INCRE_MOVEMENTS(stats) \
  do                           \
  {                            \
    if (NULL == (stats))       \
    {                          \
      break;                   \
    }                          \
    (stats)->movements++;      \
  } while (0)

#define INCRE_MOVEMENTS_BY(stats, times) \
  do                                     \
  {                                      \
    if (NULL == (stats))                 \
    {                                    \
      break;                             \
    }                                    \
    (stats)->movements += times;         \
  } while (0)

#define INCRE_MEMORY_USED(stats, size)                                                                                              \
  do                                                                                                                                \
  {                                                                                                                                 \
    if (NULL == (stats) || size == 0)                                                                                               \
    {                                                                                                                               \
      break;                                                                                                                        \
    }                                                                                                                               \
    (stats)->memory_used += size;                                                                                                   \
    (stats)->max_mamory_used = ((stats)->memory_used > (stats)->max_mamory_used) ? (stats)->memory_used : (stats)->max_mamory_used; \
  } while (0)

#define DECRE_MEMORY_USED(stats, size) \
  do                                   \
  {                                    \
    if (NULL == (stats) || size == 0)  \
    {                                  \
      break;                           \
    }                                  \
    (stats)->memory_used -= size;      \
  } while (0)

#define RECORD_ELEMENT_SIZE(stats, ele_size) \
  do                                         \
  {                                          \
    if (NULL == (stats))                     \
    {                                        \
      break;                                 \
    }                                        \
    (stats)->element_size = (ele_size);      \
  } while (0)

#define RECORD_ARR_LEN(stats, arr_len) \
  do                                   \
  {                                    \
    if (NULL == (stats))               \
    {                                  \
      break;                           \
    }                                  \
    (stats)->array_length = (arr_len); \
  } while (0)

#define PRINT_STATS(stats, sort_type)             \
  do                                              \
  {                                               \
    if (NULL == (stats))                          \
    {                                             \
      break;                                      \
    }                                             \
    printf("element_size: %zu bytes\n"            \
           "array_length: %zu\n"                  \
           "Comparisons: %zu\n"                   \
           "Movements: %zu\n"                     \
           "Time Spent: %.2f ms\n"                \
           "Additional Memory Used: %zu bytes\n", \
           (stats)->element_size,                 \
           (stats)->array_length,                 \
           (stats)->comparisons,                  \
           (stats)->movements,                    \
           (stats)->time_elapsed_ms,              \
           (stats)->max_mamory_used);             \
  } while (0)

#else
#define START_TIMMING(stats)
#define STOP_TIMMING(stats)
#define INCRE_COMPARISONS(stats)
#define INCRE_MOVEMENTS(stats)
#define INCRE_MOVEMENTS_BY(stats, times)
#define INCRE_MEMORY_USED(stats, size)
#define DECRE_MEMORY_USED(stats, size)
#define RECORD_ELEMENT_SIZE(stats, ele_size)
#define RECORD_ARR_LEN(stats, arr_len)
#define PRINT_STATS(stats, sort_type)
#endif

#define GENERIC_SAMP_SIZE_SWAP(size, ap, bp)                     \
  do                                                             \
  {                                                              \
    if ((size) <= 0)                                             \
      break;                                                     \
    size_t __SIZE = (size);                                      \
    for (size_t i = 0; i < __SIZE; i++)                          \
    {                                                            \
      ((char *)(ap))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i]; \
      ((char *)(bp))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i]; \
      ((char *)(ap))[i] = ((char *)(ap))[i] ^ ((char *)(bp))[i]; \
    }                                                            \
  } while (0)

  /**
   * ===========================================================================
   * Commonly Compare Function
   * ===========================================================================
   */

  typedef int compare_func_t(const void *const a, const void *const b);
  typedef void swap_func_t(void *const a, void *const b);

  int compare_integers(const void *const a, const void *const b);
  void integers_swap(void *const a, void *const b);
  int compare_strings(const void *const a, const void *const b);

#ifdef __cplusplus
}
#endif
#endif
