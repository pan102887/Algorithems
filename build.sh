#!/bin/bash

# ============================================================================
# 算法工具包构建和测试脚本
# Author: Algorithms Toolkit Team
# Date: 2025-06-26
# ============================================================================

set -e  # 遇到错误立即退出

# 颜色输出
RED='\e[0;31m'
GREEN='\e[0;32m'
YELLOW='\e[1;33m'
BLUE='\e[0;34m'
PURPLE='\e[0;35m'
CYAN='\e[0;36m'
NC='\e[0m' # No Color

# 打印彩色消息
print_message() {
    local color=$1
    local message=$2
    echo -e "${color}${message}${NC}"
}

print_header() {
    echo
    print_message $BLUE "=================================================="
    print_message $BLUE "$1"
    print_message $BLUE "=================================================="
    echo
}

print_success() {
    print_message $GREEN "✅ $1"
}

print_warning() {
    print_message $YELLOW "⚠️  $1"
}

print_error() {
    print_message $RED "❌  $1"
}

print_info() {
    print_message $CYAN "ℹ️  $1"
}

# 检查必要的工具
check_dependencies() {
    print_header "检查依赖工具"
    
    local missing_tools=()
    
    # 检查CMake
    if command -v cmake >/dev/null; then
        print_success "CMake: $(cmake --version | head -n1)"
    else
        missing_tools+=("cmake")
    fi
    
    # 检查Make
    if command -v make >/dev/null; then
        print_success "Make: $(make --version | head -n1)"
    else
        missing_tools+=("make")
    fi
    
    # 检查GCC
    if command -v gcc >/dev/null; then
        print_success "GCC: $(gcc --version | head -n1)"
    else
        missing_tools+=("gcc")
    fi
    
    # 检查G++
    if command -v g++ >/dev/null; then
        print_success "G++: $(g++ --version | head -n1)"
    else
        missing_tools+=("g++")
    fi
    
    # 检查可选工具
    if command -v lcov >/dev/null; then
        print_success "lcov: $(lcov --version | head -n1)"
    else
        print_warning "lcov未安装，代码覆盖率功能不可用"
    fi
    
    if command -v cppcheck >/dev/null; then
        print_success "cppcheck: $(cppcheck --version)"
    else
        print_warning "cppcheck未安装，静态分析功能不可用"
    fi
    
    if command -v clang-format >/dev/null; then
        print_success "clang-format: $(clang-format --version | head -n1)"
    else
        print_warning "clang-format未安装，代码格式化功能不可用"
    fi
    
    # 检查是否有缺失的必要工具
    if [ ${#missing_tools[@]} -ne 0 ]; then
        print_error "缺少必要工具: ${missing_tools[*]}"
        print_info "Ubuntu/Debian安装命令: sudo apt install cmake build-essential"
        exit 1
    fi
}

# 清理构建目录
clean_build() {
    print_header "清理构建目录"
    
    if [ -d "build" ]; then
        rm -rf build
        print_success "已清理 build 目录"
    fi
    
    mkdir -p build
    print_success "已创建 build 目录"
}

# 智能清理构建目录（保留Google Test缓存）
smart_clean() {
    print_header "智能清理构建目录"
    
    if [ -d "build" ]; then
        # 保留Google Test缓存
        if [ -d "build/_deps" ]; then
            print_message $BLUE "保留Google Test缓存..."
            mv build/_deps /tmp/gtest_cache_$$ 2>/dev/null || true
        fi
        
        rm -rf build
        mkdir -p build
        
        # 恢复Google Test缓存
        if [ -d "/tmp/gtest_cache_$$" ]; then
            mv /tmp/gtest_cache_$$ build/_deps
            print_success "已恢复Google Test缓存"
        fi
        
        print_success "已智能清理 build 目录"
    else
        mkdir -p build
        print_success "已创建 build 目录"
    fi
}

# 配置项目
configure_project() {
    print_header "配置项目"
    
    cd build
    
    local build_type=${1:-Release}
    print_message $BLUE "构建类型: $build_type"
    
    cmake -DCMAKE_BUILD_TYPE=$build_type \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
          ..
    
    if [ $? -eq 0 ]; then
        print_success "项目配置成功"
    else
        print_error "项目配置失败"
        exit 1
    fi
    
    cd ..
}

# 编译项目
build_project() {
    print_header "编译项目"
    
    cd build
    
    # 获取CPU核心数用于并行编译
    local cores=$(nproc || echo 4)
    print_message $BLUE "使用 $cores 个并行任务编译"
    
    make -j$cores
    
    if [ $? -eq 0 ]; then
        print_success "项目编译成功"
    else
        print_error "项目编译失败"
        exit 1
    fi
    
    cd ..
}

# 运行测试
run_tests() {
    print_header "运行测试"
    
    cd build
    
    print_message $BLUE "运行单元测试..."
    ctest --verbose
    
    if [ $? -eq 0 ]; then
        print_success "所有测试通过"
    else
        print_warning "测试失败，但继续执行其他任务"
        print_info "注意: 一些Google Test测试用例可能需要进一步调试"
    fi
    
    print_message $BLUE "运行详细测试输出..."
    if [ -f "./algorithms_tests" ]; then
        ./algorithms_tests
    fi
    
    cd ..
}

# 运行模块特定测试
run_module_tests() {
    local module=$1
    print_header "运行 ${module} 模块测试"
    
    cd build
    
    if [ -f "./algorithms_${module}_tests" ]; then
        print_message $BLUE "运行${module}模块测试..."
        ./algorithms_${module}_tests
        
        if [ $? -eq 0 ]; then
            print_success "${module}模块测试通过"
        else
            print_warning "${module}模块测试失败"
        fi
    else
        print_warning "${module}模块测试程序不存在"
    fi
    
    cd ..
}

# 运行演示程序
run_examples() {
    print_header "运行示例程序"
    
    cd build
    
    # 查找所有示例程序
    for example in example_*; do
        if [ -x "$example" ]; then
            print_message $BLUE "运行示例程序: $example"
            ./$example
            echo
        fi
    done
    
    cd ..
}

# 运行基准测试
run_benchmarks() {
    print_header "运行性能基准测试"
    
    cd build
    
    # 查找所有基准测试程序
    for benchmark in benchmark_*; do
        if [ -x "$benchmark" ]; then
            print_message $BLUE "运行基准测试: $benchmark"
            ./$benchmark
            echo
        fi
    done
    
    cd ..
}

# 生成代码覆盖率报告
generate_coverage() {
    print_header "生成代码覆盖率报告"
    
    if ! command -v lcov >/dev/null; then
        print_error "lcov未安装，无法生成覆盖率报告"
        return 1
    fi
    
    cd build
    make coverage
    
    if [ $? -eq 0 ]; then
        print_success "代码覆盖率报告生成成功"
        print_info "报告位置: build/coverage_report/index.html"
    else
        print_error "代码覆盖率报告生成失败"
    fi
    
    cd ..
}

# 运行静态分析
run_static_analysis() {
    print_header "运行静态代码分析"
    
    if ! command -v cppcheck >/dev/null; then
        print_error "cppcheck未安装，无法运行静态分析"
        return 1
    fi
    
    cd build
    make static_analysis
    
    if [ $? -eq 0 ]; then
        print_success "静态代码分析完成"
    else
        print_warning "静态代码分析发现问题"
    fi
    
    cd ..
}

# 格式化代码
format_code() {
    print_header "格式化代码"
    
    if ! command -v clang-format >/dev/null; then
        print_error "clang-format未安装，无法格式化代码"
        return 1
    fi
    
    cd build
    make format
    
    if [ $? -eq 0 ]; then
        print_success "代码格式化完成"
    else
        print_error "代码格式化失败"
    fi
    
    cd ..
}

# 显示帮助信息
show_help() {
    cat << EOF
算法工具包构建和测试脚本

用法: $0 [选项]

选项:
    -h, --help          显示此帮助信息
    -c, --clean         完全清理构建目录
    --smart-clean       智能清理（保留Google Test缓存）
    -d, --debug         使用Debug模式构建
    -r, --release       使用Release模式构建（默认）
    -t, --test          运行所有测试
    -m, --module MODULE 运行指定模块测试 (sorting|searching|data_structures|graph|dynamic_programming)
    -e, --examples      运行示例程序
    -b, --benchmarks    运行基准测试
    -f, --format        格式化代码
    -s, --static        运行静态分析
    -v, --coverage      生成代码覆盖率报告
    -a, --all           执行完整流程（智能清理、构建、测试、示例）
    --full-clean        执行完整流程（完全清理、构建、测试、示例）

示例:
    $0                  # 增量构建（Release模式）
    $0 --debug --test   # Debug模式构建并运行测试
    $0 --all            # 执行完整流程（智能清理）
    $0 --full-clean     # 执行完整流程（完全清理）
    $0 -m sorting       # 仅运行排序模块测试
    $0 --coverage       # 生成代码覆盖率报告

模块列表:
    sorting             排序算法模块
    searching           搜索算法模块
    data_structures     数据结构模块
    graph               图算法模块
    dynamic_programming 动态规划模块
EOF
}

# 主函数
main() {
    local do_clean=false
    local do_smart_clean=false
    local do_build=true
    local do_test=false
    local do_module_test=""
    local do_examples=false
    local do_benchmarks=false
    local do_coverage=false
    local do_static=false
    local do_format=false
    local build_type="Release"
    local do_all=false
    local do_full_clean=false
    
    # 解析命令行参数
    while [[ $# -gt 0 ]]; do
        case $1 in
            -h|--help)
                show_help
                exit 0
                ;;
            -c|--clean)
                do_clean=true
                shift
                ;;
            --smart-clean)
                do_smart_clean=true
                shift
                ;;
            -d|--debug)
                build_type="Debug"
                shift
                ;;
            -r|--release)
                build_type="Release"
                shift
                ;;
            -t|--test)
                do_test=true
                shift
                ;;
            -m|--module)
                do_module_test="$2"
                shift 2
                ;;
            -e|--examples)
                do_examples=true
                shift
                ;;
            -b|--benchmarks)
                do_benchmarks=true
                shift
                ;;
            -f|--format)
                do_format=true
                shift
                ;;
            -s|--static)
                do_static=true
                shift
                ;;
            -v|--coverage)
                do_coverage=true
                build_type="Debug"  # 覆盖率需要Debug模式
                shift
                ;;
            -a|--all)
                do_all=true
                do_smart_clean=true  # 使用智能清理
                do_test=true
                do_examples=true
                shift
                ;;
            --full-clean)
                do_full_clean=true
                do_clean=true
                do_test=true
                do_examples=true
                shift
                ;;
            *)
                print_error "未知选项: $1"
                show_help
                exit 1
                ;;
        esac
    done
    
    print_header "算法工具包构建脚本"
    print_message $BLUE "当前目录: $(pwd)"
    print_message $BLUE "构建类型: $build_type"
    
    # 检查依赖
    check_dependencies
    
    # 执行操作
    if [ "$do_clean" = true ]; then
        clean_build
    elif [ "$do_smart_clean" = true ]; then
        smart_clean
    fi
    
    if [ "$do_build" = true ]; then
        configure_project $build_type
        build_project
    fi
    
    if [ "$do_test" = true ] || [ "$do_all" = true ] || [ "$do_full_clean" = true ]; then
        run_tests
    fi
    
    if [ -n "$do_module_test" ]; then
        run_module_tests "$do_module_test"
    fi
    
    if [ "$do_examples" = true ] || [ "$do_all" = true ] || [ "$do_full_clean" = true ]; then
        run_examples
    fi
    
    if [ "$do_benchmarks" = true ]; then
        run_benchmarks
    fi
    
    if [ "$do_coverage" = true ]; then
        generate_coverage
    fi
    
    if [ "$do_static" = true ]; then
        run_static_analysis
    fi
    
    if [ "$do_format" = true ]; then
        format_code
    fi
    
    print_header "构建完成"
    print_success "所有任务执行完毕"
    
    if [ -d "build" ]; then
        print_message $BLUE "构建产物位于 build/ 目录"
        print_message $BLUE "库文件:"
        ls -la build/*.a 2>/dev/null || true
        print_message $BLUE "可执行文件:"
        ls -la build/example_* build/benchmark_* build/algorithms_*tests 2>/dev/null || true
    fi
}

# 执行主函数
main "$@"
