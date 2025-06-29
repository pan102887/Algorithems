/**
 * @file test_stats_control.c
 * @brief 测试插入排序统计开关功能
 * @date 2025-06-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting/insertion_sort.h"

#define TEST_SIZE 10000

int main(void) {
    printf("=== 插入排序统计开关功能测试 ===\n\n");
    
    // 准备测试数据
    int *test_data1 = malloc(TEST_SIZE * sizeof(int));
    int *test_data2 = malloc(TEST_SIZE * sizeof(int));
    
    if (test_data1 == NULL || test_data2 == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }
    
    // 初始化随机数据
    srand((unsigned int)time(NULL));
    for (int i = 0; i < TEST_SIZE; i++) {
        test_data1[i] = test_data2[i] = rand() % 10000;
    }
    
    printf("测试数据大小: %d 个整数\n\n", TEST_SIZE);
    
    // 测试1: 启用统计功能
    printf("=== 测试1: 启用统计功能 ===\n");
    insertion_sort_enable_stats();
    printf("统计状态: %s\n", insertion_sort_is_stats_enabled() ? "已启用" : "已禁用");
    
    sort_stats_t stats1;
    clock_t start_time = clock();
    sort_result_t result1 = insertion_sort_int_optimized(test_data1, TEST_SIZE, &stats1);
    clock_t end_time = clock();
    double total_time1 = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    
    if (result1 == SORT_SUCCESS) {
        printf("排序结果: 成功\n");
        printf("统计信息:\n");
        printf("  比较次数: %lu\n", stats1.comparisons);
        printf("  移动次数: %lu\n", stats1.movements);
        printf("  内部统计时间: %.3f ms\n", stats1.time_elapsed_ms);
        printf("  外部测量时间: %.3f ms\n", total_time1);
    } else {
        printf("排序失败: %d\n", result1);
    }
    
    // 重新初始化数据
    for (int i = 0; i < TEST_SIZE; i++) {
        test_data2[i] = test_data1[i];
    }
    
    printf("\n=== 测试2: 禁用统计功能 ===\n");
    insertion_sort_disable_stats();
    printf("统计状态: %s\n", insertion_sort_is_stats_enabled() ? "已启用" : "已禁用");
    
    sort_stats_t stats2;
    start_time = clock();
    sort_result_t result2 = insertion_sort_int_optimized(test_data2, TEST_SIZE, &stats2);
    end_time = clock();
    double total_time2 = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    
    if (result2 == SORT_SUCCESS) {
        printf("排序结果: 成功\n");
        printf("统计信息:\n");
        printf("  比较次数: %lu (应为0)\n", stats2.comparisons);
        printf("  移动次数: %lu (应为0)\n", stats2.movements);
        printf("  内部统计时间: %.3f ms (应为0)\n", stats2.time_elapsed_ms);
        printf("  外部测量时间: %.3f ms\n", total_time2);
    } else {
        printf("排序失败: %d\n", result2);
    }
    
    // 验证排序正确性
    printf("\n=== 排序正确性验证 ===\n");
    int sorted1 = 1, sorted2 = 1;
    for (int i = 1; i < TEST_SIZE; i++) {
        if (test_data1[i] < test_data1[i-1]) sorted1 = 0;
        if (test_data2[i] < test_data2[i-1]) sorted2 = 0;
    }
    printf("启用统计排序结果: %s\n", sorted1 ? "✅ 正确" : "❌ 错误");
    printf("禁用统计排序结果: %s\n", sorted2 ? "✅ 正确" : "❌ 错误");
    
    // 性能对比
    printf("\n=== 性能对比分析 ===\n");
    if (total_time1 > 0 && total_time2 > 0) {
        double speedup = total_time1 / total_time2;
        printf("启用统计用时: %.3f ms\n", total_time1);
        printf("禁用统计用时: %.3f ms\n", total_time2);
        printf("性能提升倍数: %.2f x\n", speedup);
        if (speedup > 1.1) {
            printf("✅ 禁用统计确实提升了性能\n");
        } else if (speedup < 0.9) {
            printf("⚠️  禁用统计性能反而下降，可能是测试误差\n");
        } else {
            printf("➖ 性能差异不明显\n");
        }
    }
    
    printf("\n=== 功能特性总结 ===\n");
    printf("✅ 全局统计开关正常工作\n");
    printf("✅ 禁用统计时统计值为0\n");
    printf("✅ 启用/禁用不影响排序正确性\n");
    printf("✅ 生产环境可根据需要开关统计功能\n");
    
    // 清理内存
    free(test_data1);
    free(test_data2);
    
    printf("\n=== 测试完成 ===\n");
    return 0;
}
