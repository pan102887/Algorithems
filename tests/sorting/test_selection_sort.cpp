#include <gtest/gtest.h>
#include <gtest/gtest-printers.h>
#include "util/test_data_util.h"
#include "sorting/selection_sort.h"

#define TEST_DATA_SIZE 10000


TEST(selection_sort_test, NullPointerTest) {
    
    EXPECT_EQ(selection_sort(nullptr, 10, compare_integers, integers_swap), SORT_ERROR_NULL_POINTER);
    
    int arr[10] = {64, 34, 25, 12, 22, 11, 90, 45, 78, 23};
    void* arr_ptr[10];
    for (size_t i = 0; i < 10; i++) {
        arr_ptr[i] = &arr[i];
    }

    EXPECT_EQ(selection_sort(arr_ptr, 10, nullptr, integers_swap), SORT_ERROR_NULL_POINTER);
}

TEST(generic_selection_sort_test, NativeIntArrayTest) {
    sort_stats_t stats;
    int sorted_int_arr[TEST_DATA_SIZE];
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        sorted_int_arr[i] = i;
    }
    auto shuffled = Shuffle<int>::shuffle_array(sorted_int_arr);
    int shuffled_int_arr[TEST_DATA_SIZE];
    for (size_t i = 0; i < shuffled.size(); i++) {
        shuffled_int_arr[i] = shuffled[i];
    }
    START_TIMMING(&stats);
    RECORD_ARR_LEN(&stats, shuffled.size());
    RECORD_ELEMENT_SIZE(&stats, sizeof(int));
    generic_selection_sort(shuffled_int_arr, sizeof(int), TEST_DATA_SIZE, compare_integers, integers_swap);
    STOP_TIMMING(&stats);
    PRINT_STATS(&stats, Selection Sort);
    EXPECT_TRUE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled_int_arr));
    EXPECT_FALSE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled.begin()));
}


TEST(generic_selection_sort_test, IntVectorTest) {
    sort_stats_t stats;
    std::vector<int> sorted_int_vector;
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        sorted_int_vector.push_back(i);
    }
    auto shuffled = Shuffle<int>::shuffle_vector(sorted_int_vector);
    auto shuffled_data = shuffled.data();
    EXPECT_FALSE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    RECORD_ARR_LEN(&stats, shuffled.size());
    RECORD_ELEMENT_SIZE(&stats, sizeof(int));
    START_TIMMING(&stats);
    generic_selection_sort(shuffled_data, sizeof(int), shuffled.size(), compare_integers, integers_swap);
    STOP_TIMMING(&stats);
    PRINT_STATS(&stats, Selection Sort);
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled.begin()));
}

TEST(generic_selection_sort_test, NativeLongArrayTest) {
    sort_stats_t stats;
    long sorted_int_arr[TEST_DATA_SIZE];
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        sorted_int_arr[i] = i;
    }
    auto shuffled = Shuffle<long>::shuffle_array(sorted_int_arr);
    long shuffled_int_arr[TEST_DATA_SIZE];
    for (size_t i = 0; i < shuffled.size(); i++) {
        shuffled_int_arr[i] = shuffled[i];
    }
    START_TIMMING(&stats);
    RECORD_ARR_LEN(&stats, shuffled.size());
    RECORD_ELEMENT_SIZE(&stats, sizeof(long));
    generic_selection_sort(shuffled_int_arr, sizeof(long), TEST_DATA_SIZE, compare_integers, integers_swap);
    STOP_TIMMING(&stats);
    PRINT_STATS(&stats, Selection Sort);
    EXPECT_TRUE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled_int_arr));
    EXPECT_FALSE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled.begin()));
}


TEST(generic_selection_sort_test, IntLongTest) {
    sort_stats_t stats;
    std::vector<long> sorted_int_vector;
    for (long i = 0; i < TEST_DATA_SIZE; i++) {
        sorted_int_vector.push_back(i);
    }
    auto shuffled = Shuffle<long>::shuffle_vector(sorted_int_vector);
    auto shuffled_data = shuffled.data();
    EXPECT_FALSE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    RECORD_ARR_LEN(&stats, shuffled.size());
    RECORD_ELEMENT_SIZE(&stats, sizeof(long));
    START_TIMMING(&stats);
    generic_selection_sort(shuffled_data, sizeof(long), shuffled.size(), compare_integers, integers_swap);
    STOP_TIMMING(&stats);
    PRINT_STATS(&stats, Selection Sort);
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled.begin()));
}

#undef TEST_DATA_SIZE