#include <gtest/gtest.h>
#include <gtest/gtest-printers.h>
#include "util/test_data_util.h"
#include "sorting/selection_sort.h"



TEST(selection_sort_test, NullPointerTest) {
    sort_stats_t stats;
    
    EXPECT_EQ(selection_sort(nullptr, 10, compare_integers, integers_swap, &stats), SORT_ERROR_NULL_POINTER);
    
    int arr[10] = {64, 34, 25, 12, 22, 11, 90, 45, 78, 23};
    void* arr_ptr[10];
    for (size_t i = 0; i < 10; i++) {
        arr_ptr[i] = &arr[i];
    }

    EXPECT_EQ(selection_sort(arr_ptr, 10, nullptr, integers_swap, &stats), SORT_ERROR_NULL_POINTER);
}

TEST(generic_selection_sort_test, NativeArrayTest) {
    sort_stats_t stats;
    #define array_size 1000
    int sorted_int_arr[array_size];
    for (int i = 0; i < array_size; i++) {
        sorted_int_arr[i] = i;
    }
    auto shuffled = Shuffle<int>::shuffle_array(sorted_int_arr);
    int shuffled_int_arr[array_size];
    for (auto i : shuffled) {
        shuffled_int_arr[i] = i;
    }

    generic_selection_sort(shuffled_int_arr, sizeof(int), array_size, compare_integers, integers_swap, &stats);
    EXPECT_TRUE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled_int_arr));
    EXPECT_FALSE(std::equal(std::begin(sorted_int_arr), std::end(sorted_int_arr), shuffled.begin()));
    #undef array_size
}


TEST(generic_selection_sort_test, VectorTest) {
    sort_stats_t stats;
    std::vector<int> sorted_int_vector;
    for (int i = 0; i < 1000; i++) {
        sorted_int_vector.push_back(i);
    }
    auto shuffled = Shuffle<int>::shuffle_vector(sorted_int_vector);
    auto shuffled_data = shuffled.data();
    EXPECT_FALSE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    generic_selection_sort(shuffled_data, sizeof(int), shuffled.size(), compare_integers, integers_swap, &stats);
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_data));
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled.begin()));
}
