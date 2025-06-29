/**
 * @file demo.c
 * @brief 算法工具包演示程序
 * @author Algorithms Toolkit Team
 * @date 2025-06-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "algorithms.h"

#define ARRAY_SIZE 20

int main(void) {
    printf("=== 算法工具包演示程序 ===\n");
    printf("版本: %s\n", algorithms_get_version());
    printf("作者: Algorithms Toolkit Team\n");
    printf("日期: 2025-06-26\n\n");
    
    // 初始化算法库
    if (algorithms_init() != 0) {
        fprintf(stderr, "算法库初始化失败\n");
        return 1;
    }
    
    // 演示插入排序
    printf("=== 插入排序演示 ===\n");
    
    // 创建测试数组
    int test_array[ARRAY_SIZE] = {
        64, 34, 25, 12, 22, 11, 90, 88, 76, 50,
        42, 37, 15, 28, 93, 47, 71, 68, 83, 56
    };
    
    printf("排序前: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    
    // 使用优化整数排序
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(test_array, ARRAY_SIZE, &stats);
    
    if (result == SORT_SUCCESS) {
        printf("排序后: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", test_array[i]);
        }
        printf("\n");
        
        printf("统计信息:\n");
        printf("  比较次数: %zu\n", stats.comparisons);
        printf("  移动次数: %zu\n", stats.movements);
        printf("  执行时间: %.3f ms\n", stats.time_elapsed_ms);
    } else {
        printf("排序失败，错误代码: %d\n", result);
    }
    
    printf("\n=== 性能对比演示 ===\n");
    
    // 生成更大的随机数组进行性能测试
    const int perf_size = 1000;
    int* perf_array1 = malloc(perf_size * sizeof(int));
    int* perf_array2 = malloc(perf_size * sizeof(int));
    
    if (!perf_array1 || !perf_array2) {
        fprintf(stderr, "内存分配失败\n");
        free(perf_array1);
        free(perf_array2);
        algorithms_cleanup();
        return 1;
    }
    
    // 生成随机数据
    srand(time(NULL));
    for (int i = 0; i < perf_size; i++) {
        perf_array1[i] = perf_array2[i] = rand() % 10000;
    }
    
    // 测试通用插入排序
    void** ptr_array = malloc(perf_size * sizeof(void*));
    if (!ptr_array) {
        fprintf(stderr, "内存分配失败\n");
        free(perf_array1);
        free(perf_array2);
        algorithms_cleanup();
        return 1;
    }
    
    for (int i = 0; i < perf_size; i++) {
        ptr_array[i] = &perf_array1[i];
    }
    
    sort_stats_t stats1, stats2;
    
    result = insertion_sort_generic(ptr_array, perf_size, compare_integers, &stats1);
    if (result == SORT_SUCCESS) {
        printf("通用插入排序 (%d 元素):\n", perf_size);
        printf("  比较次数: %zu, 移动次数: %zu, 时间: %.3f ms\n", 
               stats1.comparisons, stats1.movements, stats1.time_elapsed_ms);
    }
    
    // 测试优化整数排序
    result = insertion_sort_int_optimized(perf_array2, perf_size, &stats2);
    if (result == SORT_SUCCESS) {
        printf("优化整数排序 (%d 元素):\n", perf_size);
        printf("  比较次数: %zu, 移动次数: %zu, 时间: %.3f ms\n", 
               stats2.comparisons, stats2.movements, stats2.time_elapsed_ms);
        
        if (stats1.time_elapsed_ms > 0 && stats2.time_elapsed_ms > 0) {
            printf("  性能提升: %.1fx\n", stats1.time_elapsed_ms / stats2.time_elapsed_ms);
        }
    }
    
    // 验证排序结果正确性
    bool sorted1 = true, sorted2 = true;
    for (int i = 1; i < perf_size; i++) {
        if (*(int*)ptr_array[i-1] > *(int*)ptr_array[i]) sorted1 = false;
        if (perf_array2[i-1] > perf_array2[i]) sorted2 = false;
    }
    
    printf("排序正确性验证: %s\n", 
           (sorted1 && sorted2) ? "✅ 通过" : "❌ 失败");
    
    // 清理资源
    free(perf_array1);
    free(perf_array2);
    free(ptr_array);
    
    algorithms_cleanup();
    
    printf("\n=== 演示程序完成 ===\n");
    return 0;
}
