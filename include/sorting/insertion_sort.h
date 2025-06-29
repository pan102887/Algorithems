/**
 * @file insertion_sort.h
 * @brief 高性能插入排序算法头文件
 * @author C Programming Expert
 * @date 2025-06-26
 * @version 1.0
 */

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sort_common.h"
#include <time.h>

/* ============================================================================
 * 核心排序算法接口
 * ============================================================================
 */

/**
 * @brief 通用插入排序算法（指针数组版本）
 *
 * 时间复杂度：O(n²) 最坏情况，O(n) 最好情况
 * 空间复杂度：O(1)
 * 稳定性：稳定排序
 *
 * @param arr 待排序的指针数组
 * @param len 数组长度
 * @param cmp 比较函数指针
 * @param stats 统计信息输出参数（可为NULL）
 * @return sort_result_t 操作结果
 */
sort_result_t insertion_sort_generic(void **arr, size_t len, compare_func_t cmp,
                                    sort_stats_t *stats);

/**
 * @brief 二分插入排序算法
 *
 * 通过二分查找减少比较次数，但移动次数不变
 * 时间复杂度：O(n²) 移动，O(n log n) 比较
 *
 * @param arr 待排序的指针数组
 * @param len 数组长度
 * @param cmp 比较函数指针
 * @param stats 统计信息输出参数（可为NULL）
 * @return sort_result_t 操作结果
 */
sort_result_t binary_insertion_sort(void **arr, size_t len, compare_func_t cmp,
                                   sort_stats_t *stats);

/**
 * @brief 整数数组专用优化插入排序
 *
 * 针对整数类型的优化版本，避免函数指针调用开销
 *
 * @param arr 整数数组
 * @param len 数组长度
 * @param stats 统计信息输出参数（可为NULL）
 * @return sort_result_t 操作结果
 */
sort_result_t insertion_sort_int_optimized(int *arr, size_t len,
                                          sort_stats_t *stats);

/**
 * @brief 简单插入排序接口（向后兼容）
 *
 * 提供简单的插入排序接口，兼容旧版本代码
 * 注意：此函数不返回错误状态和统计信息
 *
 * @param arr 待排序的指针数组
 * @param len 数组长度
 * @param cmp 比较函数指针
 */
void insertion_sort(void *arr[], int len, int (*cmp)(const void *, const void *));



/* ============================================================================
 * 性能统计控制接口
 * ============================================================================
 */

/**
 * @brief 启用插入排序性能统计
 * 
 * 启用后，所有插入排序函数都会自动统计比较次数、移动次数和执行时间
 * 注意：启用统计会有轻微的性能开销
 */
void insertion_sort_enable_stats(void);

/**
 * @brief 禁用插入排序性能统计
 * 
 * 禁用后，所有插入排序函数都会跳过统计步骤，提高执行效率
 * 这是默认状态
 */
void insertion_sort_disable_stats(void);

/**
 * @brief 检查插入排序性能统计是否启用
 * 
 * @return int 1表示已启用，0表示已禁用
 */
int insertion_sort_is_stats_enabled(void);

#ifdef __cplusplus
}
#endif

#endif /* INSERTION_SORT_H */
