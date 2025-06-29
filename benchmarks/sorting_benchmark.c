/**
 * @file sorting_benchmark.c
 * @brief 排序算法性能基准测试
 * @author Algorithms Toolkit Team
 * @date 2025-06-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "algorithms.h"

#define MAX_ARRAY_SIZE 10000
#define NUM_ITERATIONS 5

// 生成随机数组
void generate_random_array(int* array, size_t size, int max_value) {
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % max_value + 1;
    }
}

// 生成已排序数组
void generate_sorted_array(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = (int)i + 1;
    }
}

// 生成逆序数组
void generate_reverse_array(int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = (int)(size - i);
    }
}

// 验证数组是否已排序
bool is_sorted(const int* array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (array[i-1] > array[i]) {
            return false;
        }
    }
    return true;
}

// 复制数组
void copy_array(const int* src, int* dst, size_t size) {
    memcpy(dst, src, size * sizeof(int));
}

// 运行排序算法基准测试
void run_sorting_benchmark(const char* test_name, const int* original_array, size_t size) {
    printf("\n=== %s (%zu 元素) ===\n", test_name, size);
    
    int* test_array1 = malloc(size * sizeof(int));
    int* test_array2 = malloc(size * sizeof(int));
    int* test_array3 = malloc(size * sizeof(int));
    void** ptr_array1 = malloc(size * sizeof(void*));
    void** ptr_array2 = malloc(size * sizeof(void*));
    
    if (!test_array1 || !test_array2 || !test_array3 || !ptr_array1 || !ptr_array2) {
        fprintf(stderr, "内存分配失败\n");
        goto cleanup;
    }
    
    sort_stats_t stats1, stats2, stats3;
    double total_time1 = 0, total_time2 = 0, total_time3 = 0;
    bool success1 = true, success2 = true, success3 = true;
    
    // 多次运行取平均值
    for (int iter = 0; iter < NUM_ITERATIONS; iter++) {
        // 准备测试数据
        copy_array(original_array, test_array1, size);
        copy_array(original_array, test_array2, size);
        copy_array(original_array, test_array3, size);
        
        // 准备指针数组
        for (size_t i = 0; i < size; i++) {
            ptr_array1[i] = &test_array1[i];
            ptr_array2[i] = &test_array2[i];
        }
        
        // 测试通用插入排序
        if (success1) {
            sort_result_t result = insertion_sort_generic(ptr_array1, size, compare_integers, &stats1);
            if (result != SORT_SUCCESS || !is_sorted(test_array1, size)) {
                success1 = false;
            } else {
                total_time1 += stats1.time_elapsed_ms;
            }
        }
        
        // 测试优化整数排序
        if (success2) {
            sort_result_t result = insertion_sort_int_optimized(test_array3, size, &stats3);
            if (result != SORT_SUCCESS || !is_sorted(test_array3, size)) {
                success2 = false;
            } else {
                total_time2 += stats3.time_elapsed_ms;
            }
        }
        
        // 测试二分插入排序
        if (success3) {
            sort_result_t result = binary_insertion_sort(ptr_array2, size, compare_integers, &stats2);
            if (result != SORT_SUCCESS || !is_sorted(test_array2, size)) {
                success3 = false;
            } else {
                total_time3 += stats2.time_elapsed_ms;
            }
        }
    }
    
    // 输出结果
    printf("%-20s | %10s | %10s | %10s | %10s\n", 
           "算法", "平均时间(ms)", "比较次数", "移动次数", "状态");
    printf("-------------------- | ---------- | ---------- | ---------- | ----------\n");
    
    if (success1) {
        printf("%-20s | %10.3f | %10zu | %10zu | %10s\n",
               "通用插入排序", total_time1 / NUM_ITERATIONS, 
               stats1.comparisons, stats1.movements, "✅");
    } else {
        printf("%-20s | %10s | %10s | %10s | %10s\n",
               "通用插入排序", "N/A", "N/A", "N/A", "❌");
    }
    
    if (success2) {
        printf("%-20s | %10.3f | %10zu | %10zu | %10s\n",
               "优化整数排序", total_time2 / NUM_ITERATIONS, 
               stats3.comparisons, stats3.movements, "✅");
    } else {
        printf("%-20s | %10s | %10s | %10s | %10s\n",
               "优化整数排序", "N/A", "N/A", "N/A", "❌");
    }
    
    if (success3) {
        printf("%-20s | %10.3f | %10zu | %10zu | %10s\n",
               "二分插入排序", total_time3 / NUM_ITERATIONS, 
               stats2.comparisons, stats2.movements, "✅");
    } else {
        printf("%-20s | %10s | %10s | %10s | %10s\n",
               "二分插入排序", "N/A", "N/A", "N/A", "❌");
    }
    
    // 性能分析
    if (success1 && success2) {
        double speedup = total_time1 / total_time2;
        printf("\n优化整数排序性能提升: %.2fx\n", speedup);
    }
    
    if (success2 && success3) {
        printf("二分插入排序比较次数减少: %.1f%%\n", 
               (1.0 - (double)stats2.comparisons / stats3.comparisons) * 100);
    }

cleanup:
    free(test_array1);
    free(test_array2);
    free(test_array3);
    free(ptr_array1);
    free(ptr_array2);
}

int main(void) {
    printf("=== 排序算法性能基准测试 ===\n");
    printf("算法工具包版本: %s\n", algorithms_get_version());
    printf("测试配置: %d 次迭代取平均值\n\n", NUM_ITERATIONS);
    
    // 初始化
    algorithms_init();
    srand(time(NULL));
    
    // 测试不同大小的数组
    size_t test_sizes[] = {100, 500, 1000, 2000, 5000};
    size_t num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);
    
    for (size_t i = 0; i < num_sizes; i++) {
        size_t size = test_sizes[i];
        if (size > MAX_ARRAY_SIZE) continue;
        
        int* test_array = malloc(size * sizeof(int));
        if (!test_array) {
            fprintf(stderr, "内存分配失败\n");
            continue;
        }
        
        // 测试随机数据
        generate_random_array(test_array, size, 10000);
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "随机数据测试");
        run_sorting_benchmark(test_name, test_array, size);
        
        free(test_array);
    }
    
    // 测试特殊情况（使用中等大小数组）
    const size_t special_size = 1000;
    int* special_array = malloc(special_size * sizeof(int));
    
    if (special_array) {
        // 已排序数据
        generate_sorted_array(special_array, special_size);
        run_sorting_benchmark("已排序数据测试", special_array, special_size);
        
        // 逆序数据
        generate_reverse_array(special_array, special_size);
        run_sorting_benchmark("逆序数据测试", special_array, special_size);
        
        free(special_array);
    }
    
    algorithms_cleanup();
    
    printf("\n=== 基准测试完成 ===\n");
    printf("说明:\n");
    printf("- 通用插入排序: 支持任意类型，使用函数指针比较\n");
    printf("- 优化整数排序: 专门针对整数优化，避免函数调用开销\n");
    printf("- 二分插入排序: 使用二分查找减少比较次数\n");
    
    return 0;
}
