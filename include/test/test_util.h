#ifndef TEST_UTIL_H
#define TEST_UTIL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdio.h>

#define ASSERT_TRUE(condition,message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s, at %s:%d\n", message, __FILE__, __LINE__); \
            assert(condition); \
        } \
    } while (0)

#define ASSERT_FALSE(condition,message) \
    do { \
        if (condition) { \
            fprintf(stderr, "Assertion failed: %s, at %s:%d\n", message, __FILE__, __LINE__); \
            assert(!condition); \
        } \
    } while (0)

#define ASSERT_EQUAL(actual, expected, message) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "Assertion failed: %s, expected %d but got %d, at %s:%d\n", \
                    message, (int)(expected), (int)(actual), __FILE__, __LINE__); \
            assert((actual) == (expected)); \
        } \
    } while (0)



#ifdef __cplusplus
}
#endif
#endif
