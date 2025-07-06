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
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG -pg")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")

set(DEBUG_TYPE "Debug")


# ============================================================================
# 预设宏定义
# ============================================================================
if(CMAKE_BUILD_TYPE STREQUAL ${DEBUG_TYPE})
    
endif()


# PUBLIC 包含目录
include_directories(include)


# ============================================================================
# 收集所有源文件
# ============================================================================

set(MODULE_LIST 
    sorting 
    searching 
    data_structures 
    graph 
    dynamic_programming
    util
)
set(TARGET_LIST)

foreach(MODULE IN LISTS MODULE_LIST)
    string(TOUPPER "${MODULE}" MODULE_UPPER)

    file(GLOB_RECURSE ${MODULE_UPPER}_SOURCES src/${MODULE}/*.c)
    file(GLOB_RECURSE ${MODULE_UPPER}_HEADERS include/${MODULE}/*.h)
    set(ALL_SOURCES ${${MODULE_UPPER}_SOURCES} ${ALL_SOURCES})
    set(ALL_HEADERS ${${MODULE_UPPER}_HEADERS} ${ALL_HEADERS})
endforeach()

# 合并所有源文件
set(ALL_SOURCES src/algorithms.c ${ALL_SOURCES})


# ============================================================================
# 创建库目标
# ============================================================================

# 创建主静态库
if(ALL_SOURCES)
    message("-- 构建主库 algorithms_toolkit")
    add_library(algorithms_toolkit STATIC ${ALL_SOURCES} ${ALL_HEADERS})
    target_include_directories(algorithms_toolkit PUBLIC include)
    # 链接数学库和实时库（POSIX）
    target_link_libraries(algorithms_toolkit m rt)
    list(APPEND TARGET_LIST algorithms_toolkit)
endif()


# 创建各模块的独立库
foreach(MODULE IN LISTS MODULE_LIST)
    string(TOUPPER "${MODULE}" MODULE_UPPER)
    if (${MODULE_UPPER}_SOURCES OR ${MODULE_UPPER}_HEADERS)
        message("-- 生成 ${MODULE} 模块独立库")
        add_library(${MODULE} STATIC ${${MODULE_UPPER}_SOURCES} ${${MODULE_UPPER}_HEADERS})
        target_include_directories(${MODULE} PUBLIC include)
        list(APPEND TARGET_LIST ${MODULE})
    endif()
endforeach()


# ============================================================================
#                                    TEST
# ============================================================================


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



# ============================================================================
# 测试工具库
# ============================================================================
# 启用测试
enable_testing()
include(CTest)
set(CTEST_PROJECT_NAME "AlgorithmsToolkit")
set(CTEST_NIGHTLY_START_TIME "00:00:00 EST")
set(CTEST_DROP_METHOD "http")

set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB  TEST_ITEMS RELATIVE ${TEST_DIR} "${TEST_DIR}/*/")
set(TEST_MODULES)
set(TEST_MODULES_DIRS)

# 收集所有测试文件
file(GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cpp)
foreach(MODULE IN LISTS TEST_ITEMS)
     if(IS_DIRECTORY ${TEST_DIR}/${MODULE})
        list(APPEND TEST_MODULES ${MODULE})
        list(APPEND TEST_MODULES_DIRS ${TEST_DIR}/${MODULE})
        message(STATUS "Found test module: ${MODULE}")
        
        string(TOUPPER "${MODULE}" MODULE_UPPER)
        file(GLOB_RECURSE ${MODULE_UPPER}_SOURCES ${TEST_DIR}/${MODULE}/*.c ${TEST_DIR}/${MODULE}/*.cpp)
        set(TEST_SOURCES ${TEST_SOURCES} ${MODULE_UPPER}_SOURCES)

        file(GLOB_RECURSE ${MODULE_UPPER}_HEADERS ${TEST_DIR}/${MODULE}/*.h)
    endif()
endforeach()
list(APPEND ${TEST_MODULES_DIRS} ${CMAKE_SOURCE_DIR}/tests)


# # ============================================================================
# # 生成测试库
# # ============================================================================
# set(TEST_LIBS)
# foreach(MODULE IN LISTS TEST_MODULES)
#     string(TOUPPER "${MODULE}" MODULE_UPPER)
#     if(${MODULE_UPPER}_SOURCES)
#         add_library(test_${MODULE}_lib STATIC
#             ${${MODULE_UPPER}_SOURCES} 
#             ${${MODULE_UPPER}_HEADERS}
#         )
#         target_include_directories(test_${MODULE}_lib PUBLIC ${TEST_DIR})
#         list(APPEND ${TEST_LIBS} test_${MODULE}_lib)
#     endif()    
# endforeach()

# ============================================================================
# 生成单元测试可执行文件
# ============================================================================
foreach(MODULE IN LISTS TEST_MODULES)
    string(TOUPPER "${MODULE}" MODULE_UPPER)
    if(${MODULE_UPPER}_SOURCES)
        add_executable(${MODULE}_tests ${${MODULE_UPPER}_SOURCES})
        target_include_directories(${MODULE}_tests PUBLIC ${TEST_DIR})
        target_link_libraries(${MODULE}_tests
                ${TEST_LIBS}
                algorithms_toolkit
                ${GTEST_LIBRARIES}
        )
        if(NOT GTest_FOUND)
                target_include_directories(${MODULE}_tests PUBLIC
                    ${googletest_SOURCE_DIR}/googletest/include
                )
        endif()
        add_test(NAME ${MODULE}_unit_tests COMMAND ${MODULE}_tests)
        list(APPEND TARGET_LIST ${MODULE}_tests)
    endif()    
endforeach()


# ============================================================================
# 代码覆盖率和Sanitizer（Debug模式）
# ============================================================================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
        # 为各模块库添加覆盖率和sanitizer支持
        foreach(MODULE IN LISTS TARGET_LIST)
            if(TARGET ${MODULE})
                message(STATUS "Adding coverage and sanitizer support for ${MODULE}")
                target_compile_options(${MODULE} PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
                target_link_options(${MODULE} PRIVATE --coverage -fsanitize=address -fsanitize=undefined)
            endif()
        endforeach()
    endif()
endif()





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
