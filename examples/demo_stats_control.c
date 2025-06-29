/**
 * @file demo_stats_control.c
 * @brief 演示插入排序统计开关功能的简单示例
 * @date 2025-06-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "sorting/insertion_sort.h"

int main(void) {
    printf("=== 插入排序统计开关演示 ===\n\n");
    
    // 准备测试数据
    int data[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int len = sizeof(data) / sizeof(data[0]);
    
    printf("原始数据: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", data[i]);
    }
    printf("\n\n");
    
    // 创建两个副本
    int data1[10], data2[10];
    for (int i = 0; i < len; i++) {
        data1[i] = data2[i] = data[i];
    }
    
    // 演示1: 启用统计
    printf("【场景1：开发调试阶段 - 启用统计】\n");
    insertion_sort_enable_stats();
    printf("统计状态: %s\n", insertion_sort_is_stats_enabled() ? "已启用" : "已禁用");
    
    sort_stats_t stats1;
    sort_result_t result1 = insertion_sort_int_optimized(data1, len, &stats1);
    
    if (result1 == SORT_SUCCESS) {
        printf("排序结果: ");
        for (int i = 0; i < len; i++) {
            printf("%d ", data1[i]);
        }
        printf("\n");
        printf("详细统计: %lu比较, %lu移动, %.3fms\n", 
               stats1.comparisons, stats1.movements, stats1.time_elapsed_ms);
    }
    
    // 演示2: 禁用统计
    printf("\n【场景2：生产环境 - 禁用统计】\n");
    insertion_sort_disable_stats();
    printf("统计状态: %s\n", insertion_sort_is_stats_enabled() ? "已启用" : "已禁用");
    
    sort_stats_t stats2;
    sort_result_t result2 = insertion_sort_int_optimized(data2, len, &stats2);
    
    if (result2 == SORT_SUCCESS) {
        printf("排序结果: ");
        for (int i = 0; i < len; i++) {
            printf("%d ", data2[i]);
        }
        printf("\n");
        printf("轻量执行: %lu比较, %lu移动, %.3fms (全部为0)\n", 
               stats2.comparisons, stats2.movements, stats2.time_elapsed_ms);
    }
    
    printf("\n=== 使用建议 ===\n");
    printf("🔧 开发调试阶段:\n");
    printf("   - 调用 insertion_sort_enable_stats() 启用统计\n");
    printf("   - 获得详细的性能数据和执行统计\n");
    printf("   - 用于性能分析、算法优化\n");
    printf("\n⚡ 生产环境:\n");
    printf("   - 调用 insertion_sort_disable_stats() 禁用统计\n");
    printf("   - 获得最佳执行性能\n");
    printf("   - 减少不必要的计算开销\n");
    
    printf("\n=== 演示完成 ===\n");
    return 0;
}
