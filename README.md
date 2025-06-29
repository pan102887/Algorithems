# 算法工具包 (Algorithms Toolkit)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![C++ Standard](https://img.shields.io/badge/C++-C++17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Testing](https://img.shields.io/badge/testing-Google%20Test-red.svg)](https://github.com/google/googletest)
[![Build System](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)

## 🚀 项目简介

**算法工具包**是一个高质量、现代化的C语言算法库，包含了计算机科学中最常用的算法和数据结构实现。项目采用模块化设计，支持独立使用各个模块，同时提供了完整的测试套件、性能基准测试和详细的文档。

### ✨ 核心特性

- 🏗️ **模块化设计**: 按功能分模块组织，支持独立编译和使用
- 🚀 **高性能实现**: 针对不同场景的优化版本，追求极致性能
- 🔒 **内存安全**: 完整的边界检查、错误处理和内存泄漏防护
- 🧪 **全面测试**: 基于Google Test的完整单元测试覆盖
- 📊 **性能基准**: 详细的性能对比和分析工具
- 🛠️ **现代构建**: CMake + 智能缓存管理，支持增量构建
- 📚 **丰富文档**: API文档、使用示例和最佳实践指南

## 📁 项目结构

```
algorithms-toolkit/
├── include/                    # 头文件目录
│   ├── algorithms.h           # 主头文件
│   ├── sorting/               # 排序算法
│   │   └── insertion_sort.h   # 插入排序（已实现）
│   ├── searching/             # 搜索算法（规划中）
│   ├── data_structures/       # 数据结构（规划中）
│   ├── graph/                 # 图算法（规划中）
│   └── dynamic_programming/   # 动态规划（规划中）
├── src/                       # 源文件目录
│   ├── algorithms.c           # 主实现文件
│   ├── sorting/               # 排序算法实现
│   │   └── insertion_sort.c   # 插入排序实现
│   ├── searching/             # 搜索算法实现
│   ├── data_structures/       # 数据结构实现
│   ├── graph/                 # 图算法实现
│   └── dynamic_programming/   # 动态规划实现
├── tests/                     # 测试目录
│   ├── sorting/               # 排序算法测试
│   │   └── test_insertion_sort.cpp
│   ├── searching/             # 搜索算法测试
│   ├── data_structures/       # 数据结构测试
│   ├── graph/                 # 图算法测试
│   └── dynamic_programming/   # 动态规划测试
├── examples/                  # 示例程序
│   └── demo.c                 # 主演示程序
├── benchmarks/                # 基准测试
│   └── sorting_benchmark.c    # 排序算法性能测试
├── docs/                      # 文档目录
├── tools/                     # 工具脚本
├── build.sh                   # 自动化构建脚本
├── CMakeLists.txt            # CMake配置文件
└── README.md                 # 项目文档
```

## 🛠️ 快速开始

### 系统要求

**必需工具:**
- CMake >= 3.16
- GCC >= 9.0 或 Clang >= 10.0
- Make (GNU Make推荐)

**可选工具:**
- lcov (代码覆盖率报告)
- cppcheck (静态代码分析)
- clang-format (代码格式化)

### 构建和安装

```bash
# 克隆项目
git clone <repository-url>
cd algorithms-toolkit

# 赋予构建脚本执行权限
chmod +x build.sh

# 查看帮助信息
./build.sh --help

# 🚀 一键构建和测试（推荐）
./build.sh --all

# 或分步执行
./build.sh              # 基本构建
./build.sh --test        # 运行测试
./build.sh --examples    # 运行示例
./build.sh --benchmarks  # 运行基准测试
```

### 智能缓存优化

项目实现了Google Test智能缓存管理，大幅提升构建速度：

```bash
# 🚀 智能清理（保留依赖缓存，推荐）
./build.sh --smart-clean --test    # ~3秒

# 🐌 完全清理（重新下载所有依赖）
./build.sh --full-clean --test     # ~30秒

# 性能提升: 智能清理比完全清理快10倍！
```

## 📚 算法模块

### 🔄 排序算法 (已实现)

| 算法 | 时间复杂度 | 空间复杂度 | 稳定性 | 适用场景 |
|------|-----------|-----------|--------|----------|
| **插入排序** | O(n²) / O(n) | O(1) | 稳定 | 小规模数据，部分有序 |

**实现版本:**
- `insertion_sort_generic()` - 通用版本，支持任意数据类型
- `insertion_sort_int_optimized()` - 整数优化版本，性能提升3倍
- `binary_insertion_sort()` - 二分查找版本，减少比较次数

### 🔍 搜索算法 (规划中)

- 线性搜索 (Linear Search)
- 二分搜索 (Binary Search)
- 三分搜索 (Ternary Search)
- 插值搜索 (Interpolation Search)

### 📊 数据结构 (规划中)

- 动态数组 (Dynamic Array)
- 链表 (Linked List)
- 栈 (Stack)
- 队列 (Queue)
- 哈希表 (Hash Table)
- 二叉搜索树 (Binary Search Tree)
- AVL树 (AVL Tree)
- 红黑树 (Red-Black Tree)

### 🕸️ 图算法 (规划中)

- 深度优先搜索 (DFS)
- 广度优先搜索 (BFS)
- Dijkstra最短路径
- Floyd-Warshall算法
- Kruskal最小生成树
- Prim最小生成树

### 🎯 动态规划 (规划中)

- 斐波那契数列
- 最长公共子序列 (LCS)
- 背包问题
- 编辑距离
- 最长递增子序列

## 🧪 测试和基准

### 运行测试

```bash
# 运行所有测试
./build.sh --test

# 运行特定模块测试
./build.sh --module sorting

# 生成代码覆盖率报告
./build.sh --coverage
# 报告位置: build/coverage_report/index.html
```

### 性能基准测试

```bash
# 运行排序算法基准测试
./build.sh --benchmarks

# 示例输出:
# === 随机数据测试 (1000 元素) ===
# 算法                 | 平均时间(ms) | 比较次数   | 移动次数   | 状态
# -------------------- | ---------- | ---------- | ---------- | ----------
# 通用插入排序          | 0.245      | 244302     | 244301     | ✅
# 优化整数排序          | 0.082      | 244302     | 244301     | ✅
# 二分插入排序          | 0.063      | 8977       | 244301     | ✅
# 
# 优化整数排序性能提升: 2.99x
# 二分插入排序比较次数减少: 96.3%
```

## 📖 使用示例

### 基本使用

```c
#include "algorithms.h"

int main() {
    // 初始化算法库
    algorithms_init();
    
    // 使用插入排序
    int array[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size = sizeof(array) / sizeof(array[0]);
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(array, size, &stats);
    
    if (result == SORT_SUCCESS) {
        printf("排序成功！\n");
        printf("比较次数: %zu, 移动次数: %zu\n", 
               stats.comparisons, stats.movements);
    }
    
    // 清理资源
    algorithms_cleanup();
    return 0;
}
```

### 通用排序使用

```c
#include "algorithms.h"

// 自定义比较函数
int compare_strings(const void* a, const void* b) {
    const char** str1 = (const char**)a;
    const char** str2 = (const char**)b;
    return strcmp(*str1, *str2);
}

int main() {
    algorithms_init();
    
    // 排序字符串数组
    const char* fruits[] = {"banana", "apple", "cherry", "date"};
    size_t count = 4;
    
    // 创建指针数组
    const char** ptr_array = malloc(count * sizeof(const char*));
    for (size_t i = 0; i < count; i++) {
        ptr_array[i] = fruits[i];
    }
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_generic(
        (void**)ptr_array, count, compare_strings, &stats);
    
    if (result == SORT_SUCCESS) {
        printf("字符串排序结果:\n");
        for (size_t i = 0; i < count; i++) {
            printf("%s ", ptr_array[i]);
        }
        printf("\n");
    }
    
    free(ptr_array);
    algorithms_cleanup();
    return 0;
}
```

## 🔧 高级功能

### 代码质量工具

```bash
# 静态代码分析
./build.sh --static

# 代码格式化
./build.sh --format

# 生成编译数据库（用于IDE智能提示）
# build/compile_commands.json 会自动生成
```

### Debug模式构建

```bash
# Debug模式（包含AddressSanitizer和UndefinedBehaviorSanitizer）
./build.sh --debug --test

# 生成代码覆盖率报告（自动使用Debug模式）
./build.sh --coverage
```

## 🤝 贡献指南

我们欢迎各种形式的贡献！

### 开发流程

1. Fork项目
2. 创建功能分支: `git checkout -b feature/new-algorithm`
3. 按模块添加算法实现
4. 编写对应的测试用例
5. 运行测试确保通过: `./build.sh --all`
6. 提交Pull Request

### 代码规范

- 遵循项目现有的代码风格
- 为新算法添加完整的文档注释
- 编写全面的单元测试
- 添加性能基准测试
- 使用 `./build.sh --format` 格式化代码

### 添加新算法

1. 在对应模块目录下创建头文件和源文件
2. 在主头文件中包含新算法
3. 编写Google Test测试用例
4. 更新CMakeLists.txt（如果需要）
5. 更新文档

## 📄 许可证

本项目采用 [MIT License](LICENSE) 开源协议。

## 🏆 项目亮点

- ✅ **现代化C语言开发最佳实践**
- ✅ **Google Test集成和智能缓存优化**
- ✅ **模块化可扩展架构设计**
- ✅ **全面的性能基准测试框架**
- ✅ **智能构建系统和依赖管理**
- ✅ **详细的文档和使用示例**
- ✅ **内存安全和错误处理机制**
- ✅ **跨平台兼容性支持**

## 🎯 未来规划

- [ ] **Phase 1**: 完善排序算法模块 (快速排序、归并排序、堆排序等)
- [ ] **Phase 2**: 实现搜索算法模块
- [ ] **Phase 3**: 添加基础数据结构
- [ ] **Phase 4**: 实现图算法模块
- [ ] **Phase 5**: 添加动态规划算法
- [ ] **Phase 6**: 性能优化和并行化支持
- [ ] **Phase 7**: Python/Java绑定支持

---

*算法工具包 - 让算法实现更简单，让性能优化更高效！*
