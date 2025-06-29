/**
 * @file algorithms.h
 * @brief 算法工具包主头文件
 * @author Algorithms Toolkit Team
 * @date 2025-06-26
 * @version 1.0
 * 
 * 这是算法工具包的主要头文件，包含了所有常用算法的接口定义。
 * 工具包按功能模块组织，包括：
 * - 排序算法 (Sorting Algorithms)
 * - 搜索算法 (Searching Algorithms) 
 * - 数据结构 (Data Structures)
 * - 图算法 (Graph Algorithms)
 * - 动态规划 (Dynamic Programming)
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 版本信息
 * ============================================================================ */

#define ALGORITHMS_TOOLKIT_VERSION_MAJOR 1
#define ALGORITHMS_TOOLKIT_VERSION_MINOR 0
#define ALGORITHMS_TOOLKIT_VERSION_PATCH 0

/* ============================================================================
 * 排序算法模块
 * ============================================================================ */

#include "sorting/insertion_sort.h"
// #include "sorting/quick_sort.h"      // 将来添加
// #include "sorting/merge_sort.h"      // 将来添加
// #include "sorting/heap_sort.h"       // 将来添加
// #include "sorting/bubble_sort.h"     // 将来添加
// #include "sorting/selection_sort.h"  // 将来添加

/* ============================================================================
 * 搜索算法模块
 * ============================================================================ */

// #include "searching/binary_search.h"    // 将来添加
// #include "searching/linear_search.h"    // 将来添加
// #include "searching/ternary_search.h"   // 将来添加

/* ============================================================================
 * 数据结构模块
 * ============================================================================ */

// #include "data_structures/stack.h"      // 将来添加
// #include "data_structures/queue.h"      // 将来添加
// #include "data_structures/linked_list.h" // 将来添加
// #include "data_structures/hash_table.h" // 将来添加
// #include "data_structures/binary_tree.h" // 将来添加

/* ============================================================================
 * 图算法模块
 * ============================================================================ */

// #include "graph/dfs.h"                   // 将来添加
// #include "graph/bfs.h"                   // 将来添加
// #include "graph/dijkstra.h"              // 将来添加
// #include "graph/kruskal.h"               // 将来添加
// #include "graph/prim.h"                  // 将来添加

/* ============================================================================
 * 动态规划模块
 * ============================================================================ */

// #include "dynamic_programming/fibonacci.h"    // 将来添加
// #include "dynamic_programming/knapsack.h"     // 将来添加
// #include "dynamic_programming/lcs.h"          // 将来添加

/* ============================================================================
 * 通用工具函数
 * ============================================================================ */

/**
 * @brief 获取算法工具包版本字符串
 * @return 版本字符串（例如："1.0.0"）
 */
const char* algorithms_get_version(void);

/**
 * @brief 初始化算法工具包
 * @return 成功返回0，失败返回负数
 */
int algorithms_init(void);

/**
 * @brief 清理算法工具包资源
 */
void algorithms_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* ALGORITHMS_H */
