/**
 * @file insertion_sort.c
 * @brief 高性能插入排序算法实现
 * @author C Programming Expert
 * @date 2025-06-26
 * @version 1.0
 */

#define _POSIX_C_SOURCE 199309L  /* 启用POSIX时间函数 */

#include "sorting/insertion_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/* ============================================================================
 * 内部辅助函数声明
 * ============================================================================ */

static inline size_t binary_search_insertion_point(void **arr, size_t len, 
                                                   void *key, compare_func_t cmp);
static double get_time_diff_ms(struct timespec start, struct timespec end);

/* ============================================================================
 * 性能统计控制变量
 * ============================================================================ */

/** 全局统计开关，默认禁用以获得最佳性能 */
static int g_stats_enabled = 0;

/* ============================================================================
 * 性能统计控制函数实现
 * ============================================================================ */

void insertion_sort_enable_stats(void) {
    g_stats_enabled = 1;
}

void insertion_sort_disable_stats(void) {
    g_stats_enabled = 0;
}

int insertion_sort_is_stats_enabled(void) {
    return g_stats_enabled;
}

/* ============================================================================
 * 核心排序算法实现
 * ============================================================================ */

sort_result_t insertion_sort_generic(void **arr, size_t len, 
                                   compare_func_t cmp, sort_stats_t *stats) {
    /* 参数验证 */
    if (arr == NULL || cmp == NULL) {
        return SORT_ERROR_NULL_POINTER;
    }
    
    if (len == 0) {
        return SORT_ERROR_INVALID_LENGTH;
    }
    
    /* 初始化统计信息 */
    sort_stats_t local_stats = {0, 0, 0.0};
    struct timespec start_time, end_time;
    
    /* 根据全局开关决定是否进行时间统计 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);
    }
    
    /* 如果只有一个元素，直接返回 */
    if (len <= 1) {
        if (g_stats_enabled) {
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            local_stats.time_elapsed_ms = get_time_diff_ms(start_time, end_time);
        }
        if (stats != NULL) {
            *stats = local_stats;
        }
        return SORT_SUCCESS;
    }
    
    /* 插入排序主循环 */
    for (size_t i = 1; i < len; i++) {
        void *key = arr[i];
        size_t j = i;
        
        /* 向后移动比key大的元素 */
        while (j > 0) {
            if (g_stats_enabled) {
                local_stats.comparisons++;
            }
            if (cmp(arr[j - 1], key) <= 0) {
                break;
            }
            
            arr[j] = arr[j - 1];
            if (g_stats_enabled) {
                local_stats.movements++;
            }
            j--;
        }
        
        /* 插入key到正确位置 */
        if (j != i) {
            arr[j] = key;
            if (g_stats_enabled) {
                local_stats.movements++;
            }
        }
    }
    
    /* 计算执行时间 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        local_stats.time_elapsed_ms = get_time_diff_ms(start_time, end_time);
    }
    
    /* 输出统计信息 */
    if (stats != NULL) {
        *stats = local_stats;
    }
    
    return SORT_SUCCESS;
}

sort_result_t binary_insertion_sort(void **arr, size_t len, 
                                  compare_func_t cmp, sort_stats_t *stats) {
    /* 参数验证 */
    if (arr == NULL || cmp == NULL) {
        return SORT_ERROR_NULL_POINTER;
    }
    
    if (len == 0) {
        return SORT_ERROR_INVALID_LENGTH;
    }
    
    /* 初始化统计信息 */
    sort_stats_t local_stats = {0, 0, 0.0};
    struct timespec start_time, end_time;
    
    /* 根据全局开关决定是否进行时间统计 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);
    }
    
    /* 如果只有一个元素，直接返回 */
    if (len <= 1) {
        if (g_stats_enabled) {
            clock_gettime(CLOCK_MONOTONIC, &end_time);
            local_stats.time_elapsed_ms = get_time_diff_ms(start_time, end_time);
        }
        if (stats != NULL) {
            *stats = local_stats;
        }
        return SORT_SUCCESS;
    }
    
    /* 二分插入排序主循环 */
    for (size_t i = 1; i < len; i++) {
        void *key = arr[i];
        
        /* 二分查找插入位置 */
        size_t insert_pos = binary_search_insertion_point(arr, i, key, cmp);
        if (g_stats_enabled) {
            local_stats.comparisons += (size_t)(log2(i) + 1); /* 估算二分查找比较次数 */
        }
        
        /* 向后移动元素为key腾出空间 */
        for (size_t j = i; j > insert_pos; j--) {
            arr[j] = arr[j - 1];
            if (g_stats_enabled) {
                local_stats.movements++;
            }
        }
        
        /* 插入key */
        arr[insert_pos] = key;
        if (g_stats_enabled && insert_pos != i) {
            local_stats.movements++;
        }
    }
    
    /* 计算执行时间 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        local_stats.time_elapsed_ms = get_time_diff_ms(start_time, end_time);
    }
    
    /* 输出统计信息 */
    if (stats != NULL) {
        *stats = local_stats;
    }
    
    return SORT_SUCCESS;
}

sort_result_t insertion_sort_int_optimized(int *arr, size_t len, sort_stats_t *stats) {
    /* 参数验证 */
    if (arr == NULL) {
        return SORT_ERROR_NULL_POINTER;
    }
    
    if (len == 0) {
        return SORT_ERROR_INVALID_LENGTH;
    }
    
    /* 初始化统计信息 */
    sort_stats_t local_stats = {0, 0, 0.0};
    struct timespec start_time, end_time;
    
    /* 根据全局开关决定是否进行时间统计 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);
    }
    
    /* 优化的插入排序 */
    for (size_t i = 1; i < len; i++) {
        int key = arr[i];
        size_t j = i;
        
        /* 内联比较，避免函数调用开销 */
        while (j > 0 && arr[j - 1] > key) {
            if (g_stats_enabled) {
                local_stats.comparisons++;
            }
            arr[j] = arr[j - 1];
            if (g_stats_enabled) {
                local_stats.movements++;
            }
            j--;
        }
        
        if (g_stats_enabled && j > 0) {
            local_stats.comparisons++; /* 最后一次失败的比较 */
        }
        
        if (j != i) {
            arr[j] = key;
            if (g_stats_enabled) {
                local_stats.movements++;
            }
        }
    }
    
    /* 计算执行时间 */
    if (g_stats_enabled) {
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        local_stats.time_elapsed_ms = get_time_diff_ms(start_time, end_time);
    }
    
    /* 输出统计信息 */
    if (stats != NULL) {
        *stats = local_stats;
    }
    
    return SORT_SUCCESS;
}

void insertion_sort(void *arr[], int len, int (*cmp)(const void *, const void *)) {
    if (arr == NULL || cmp == NULL || len <= 0) {
        return; /* 静默处理错误情况 */
    }
    
    sort_stats_t stats;
    insertion_sort_generic((void **)arr, (size_t)len, cmp, &stats);
}

/* ============================================================================
 * 辅助函数实现
 * ============================================================================ */

static inline size_t binary_search_insertion_point(void **arr, size_t len, 
                                                   void *key, compare_func_t cmp) {
    size_t left = 0;
    size_t right = len;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (cmp(arr[mid], key) <= 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

static double get_time_diff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + 
           (end.tv_nsec - start.tv_nsec) / 1000000.0;
}


