cmake_minimum_required(VERSION 3.16)
project(AlgorithmsToolkit VERSION 1.0.0 LANGUAGES C CXX)

# 设置C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Debug和Release配置
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")

# 包含目录
include_directories(include)

# ============================================================================
# 收集所有源文件
# ============================================================================

# 排序算法源文件
file(GLOB_RECURSE SORTING_SOURCES src/sorting/*.c)
file(GLOB_RECURSE SORTING_HEADERS include/sorting/*.h)

# 搜索算法源文件
file(GLOB_RECURSE SEARCHING_SOURCES src/searching/*.c)
file(GLOB_RECURSE SEARCHING_HEADERS include/searching/*.h)

# 数据结构源文件
file(GLOB_RECURSE DATA_STRUCTURES_SOURCES src/data_structures/*.c)
file(GLOB_RECURSE DATA_STRUCTURES_HEADERS include/data_structures/*.h)

# 图算法源文件
file(GLOB_RECURSE GRAPH_SOURCES src/graph/*.c)
file(GLOB_RECURSE GRAPH_HEADERS include/graph/*.h)

# 动态规划算法源文件
file(GLOB_RECURSE DP_SOURCES src/dynamic_programming/*.c)
file(GLOB_RECURSE DP_HEADERS include/dynamic_programming/*.h)

# 合并所有源文件
set(ALL_SOURCES 
    src/algorithms.c
    ${SORTING_SOURCES}
    ${SEARCHING_SOURCES}
    ${DATA_STRUCTURES_SOURCES}
    ${GRAPH_SOURCES}
    ${DP_SOURCES}
)

set(ALL_HEADERS
    ${SORTING_HEADERS}
    ${SEARCHING_HEADERS}
    ${DATA_STRUCTURES_HEADERS}
    ${GRAPH_HEADERS}
    ${DP_HEADERS}
)

# ============================================================================
# 创建库目标
# ============================================================================

# 创建主静态库
add_library(algorithms_toolkit STATIC ${ALL_SOURCES} ${ALL_HEADERS})
target_include_directories(algorithms_toolkit PUBLIC include)

# 创建各模块的独立库
if(SORTING_SOURCES)
    add_library(algorithms_sorting STATIC ${SORTING_SOURCES} ${SORTING_HEADERS})
    target_include_directories(algorithms_sorting PUBLIC include)
endif()

if(SEARCHING_SOURCES)
    add_library(algorithms_searching STATIC ${SEARCHING_SOURCES} ${SEARCHING_HEADERS})
    target_include_directories(algorithms_searching PUBLIC include)
endif()

if(DATA_STRUCTURES_SOURCES)
    add_library(algorithms_data_structures STATIC ${DATA_STRUCTURES_SOURCES} ${DATA_STRUCTURES_HEADERS})
    target_include_directories(algorithms_data_structures PUBLIC include)
endif()

if(GRAPH_SOURCES)
    add_library(algorithms_graph STATIC ${GRAPH_SOURCES} ${GRAPH_HEADERS})
    target_include_directories(algorithms_graph PUBLIC include)
endif()

if(DP_SOURCES)
    add_library(algorithms_dp STATIC ${DP_SOURCES} ${DP_HEADERS})
    target_include_directories(algorithms_dp PUBLIC include)
endif()

# 链接数学库和实时库（POSIX）
target_link_libraries(algorithms_toolkit m rt)

# ============================================================================
# Google Test 配置
# ============================================================================

# 查找Google Test
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    # 检查是否已经有Google Test缓存
    if(EXISTS "${CMAKE_BINARY_DIR}/_deps/googletest-src/CMakeLists.txt")
        message(STATUS "Found existing Google Test cache, reusing...")
        # 直接设置已下载的路径
        set(googletest_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/googletest-src")
        set(googletest_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/googletest-build")
        
        # 添加子目录
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
        
        # 设置目标
        set(GTEST_LIBRARIES gtest gtest_main)
        set(GTEST_INCLUDE_DIRS "")
        set(GOOGLETEST_CACHED TRUE)
    else()
        # 如果系统没有安装Google Test且没有缓存，使用FetchContent下载
        include(FetchContent)
        
        message(STATUS "Google Test not found, downloading...")
        
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
            GIT_SHALLOW TRUE
        )
        
        # 禁用Google Test的安装
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        
        FetchContent_MakeAvailable(googletest)
        
        # 设置目标
        set(GTEST_LIBRARIES gtest gtest_main)
        set(GTEST_INCLUDE_DIRS "")
        set(GOOGLETEST_CACHED FALSE)
    endif()
else()
    message(STATUS "Found Google Test")
    set(GTEST_LIBRARIES GTest::gtest GTest::gtest_main)
    set(GTEST_INCLUDE_DIRS "")
    set(GOOGLETEST_CACHED FALSE)
endif()

# 启用测试
enable_testing()
include(CTest)
set(CTEST_PROJECT_NAME "AlgorithmsToolkit")
set(CTEST_NIGHTLY_START_TIME "00:00:00 EST")
set(CTEST_DROP_METHOD "http")

# ============================================================================
# 测试目标
# ============================================================================

# 收集所有测试文件
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

if(TEST_SOURCES)
    # 创建主测试可执行文件
    add_executable(algorithms_tests ${TEST_SOURCES})
    
    # 链接依赖
    target_link_libraries(algorithms_tests
        algorithms_toolkit
        ${GTEST_LIBRARIES}
    )
    
    # 如果使用缓存或FetchContent，需要包含Google Test的头文件
    if(NOT GTest_FOUND)
        target_include_directories(algorithms_tests PRIVATE
            ${googletest_SOURCE_DIR}/googletest/include
        )
    endif()
    
    # 添加测试到CTest
    add_test(NAME algorithms_unit_tests COMMAND algorithms_tests)
    
    # 为每个模块创建独立的测试（如果需要）
    foreach(MODULE sorting searching data_structures graph dynamic_programming)
        file(GLOB MODULE_TEST_SOURCES tests/${MODULE}/*.cpp)
        if(MODULE_TEST_SOURCES)
            add_executable(algorithms_${MODULE}_tests ${MODULE_TEST_SOURCES})
            target_link_libraries(algorithms_${MODULE}_tests
                algorithms_toolkit
                ${GTEST_LIBRARIES}
            )
            
            # 为模块测试添加覆盖率和sanitizer支持（Debug模式）
            if(CMAKE_BUILD_TYPE STREQUAL "Debug")
                if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
                    target_compile_options(algorithms_${MODULE}_tests PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
                    target_link_options(algorithms_${MODULE}_tests PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
                endif()
            endif()
            
            if(NOT GTest_FOUND)
                target_include_directories(algorithms_${MODULE}_tests PRIVATE
                    ${googletest_SOURCE_DIR}/googletest/include
                )
            endif()
            add_test(NAME algorithms_${MODULE}_unit_tests COMMAND algorithms_${MODULE}_tests)
        endif()
    endforeach()
endif()


# ============================================================================
# 代码覆盖率和Sanitizer（Debug模式）
# ============================================================================

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
        # 为主库添加覆盖率和sanitizer支持
        target_compile_options(algorithms_toolkit PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        target_link_options(algorithms_toolkit PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        
        # 为各模块库也添加覆盖率和sanitizer支持
        if(TARGET algorithms_sorting)
            target_compile_options(algorithms_sorting PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_sorting PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
        
        if(TARGET algorithms_searching)
            target_compile_options(algorithms_searching PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_searching PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
        
        if(TARGET algorithms_data_structures)
            target_compile_options(algorithms_data_structures PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_data_structures PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
        
        if(TARGET algorithms_graph)
            target_compile_options(algorithms_graph PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_graph PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
        
        if(TARGET algorithms_dp)
            target_compile_options(algorithms_dp PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_dp PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
        
        # 为测试目标添加覆盖率和sanitizer支持
        if(TARGET algorithms_tests)
            target_compile_options(algorithms_tests PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            target_link_options(algorithms_tests PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
        endif()
    endif()
endif()

# ============================================================================
# 自定义目标
# ============================================================================

# 运行所有测试
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS algorithms_tests
    COMMENT "Running all tests"
)

# 生成代码覆盖率报告
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(GCOV_PATH gcov)
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)
    
    if(GCOV_PATH AND LCOV_PATH AND GENHTML_PATH)
        add_custom_target(coverage
            COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
            COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' --output-file coverage.info
            COMMAND ${LCOV_PATH} --list coverage.info
            COMMAND ${GENHTML_PATH} -o coverage_report coverage.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS run_tests
            COMMENT "Generating code coverage report"
        )
    endif()
endif()

# 代码格式化
find_program(CLANG_FORMAT_PATH clang-format)
if(CLANG_FORMAT_PATH)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_PATH} -i ${ALL_SOURCES} ${ALL_HEADERS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting code with clang-format"
    )
endif()

# 静态分析
find_program(CPPCHECK_PATH cppcheck)
if(CPPCHECK_PATH)
    add_custom_target(static_analysis
        COMMAND ${CPPCHECK_PATH} --enable=all --std=c11 --language=c 
                --suppress=missingIncludeSystem 
                --project=${CMAKE_BINARY_DIR}/compile_commands.json
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running static analysis with cppcheck"
    )
endif()

# 安装配置
install(TARGETS algorithms_toolkit
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include/algorithms
    FILES_MATCHING PATTERN "*.h"
)

# 打印配置信息
message(STATUS "=== Algorithms Toolkit Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
if(GTest_FOUND)
    message(STATUS "Google Test: System Installation")
elseif(GOOGLETEST_CACHED)
    message(STATUS "Google Test: Cached (${googletest_SOURCE_DIR})")
else()
    message(STATUS "Google Test: Downloaded")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Coverage support: ON")
else()
    message(STATUS "Coverage support: OFF")
endif()
message(STATUS "Modules found:")
if(SORTING_SOURCES)
    list(LENGTH SORTING_SOURCES SORTING_COUNT)
    message(STATUS "  - Sorting: ${SORTING_COUNT} files")
endif()
if(SEARCHING_SOURCES)
    list(LENGTH SEARCHING_SOURCES SEARCHING_COUNT)
    message(STATUS "  - Searching: ${SEARCHING_COUNT} files")
endif()
if(DATA_STRUCTURES_SOURCES)
    list(LENGTH DATA_STRUCTURES_SOURCES DS_COUNT)
    message(STATUS "  - Data Structures: ${DS_COUNT} files")
endif()
if(GRAPH_SOURCES)
    list(LENGTH GRAPH_SOURCES GRAPH_COUNT)
    message(STATUS "  - Graph: ${GRAPH_COUNT} files")
endif()
if(DP_SOURCES)
    list(LENGTH DP_SOURCES DP_COUNT)
    message(STATUS "  - Dynamic Programming: ${DP_COUNT} files")
endif()
message(STATUS "=========================================")
