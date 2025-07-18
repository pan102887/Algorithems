#ifndef TEST_DATA_UTIL_H
#define TEST_DATA_UTIL_H
#include <vector>
#include <array>
#include <random>
#include <stddef.h>
#include <vector>


template<typename T>
class Shuffle {
public:
    static std::vector<T> shuffle_vector(const std::vector<T>& vec) {
        std::vector<T> shuffled = vec;
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(shuffled.begin(), shuffled.end(), g);
        return shuffled;
    }

    template<size_t N>    
    static std::array<T, N> shuffle_array(const T (&arr)[N]) {
        std::array<T, N> shuffled;
        std::copy(std::begin(arr), std::end(arr), shuffled.begin());
        
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(shuffled.begin(), shuffled.end(), g);
        
        return shuffled;
    }

    // 新增的指针版本
    static std::vector<T> shuffle_array(T* arr, size_t size) {
        std::vector<T> result(arr, arr + size);
        auto rng = std::default_random_engine{};
        std::shuffle(result.begin(), result.end(), rng);
        return result;
    }
};

class TestDataUtil {
public:
    std::vector<int> sorted_int_vector;
    std::vector<long> sorted_long_vector;

    TestDataUtil(size_t test_data_size) {
        for (size_t i = 0; i < test_data_size; ++i) {
            sorted_int_vector.push_back(static_cast<int>(i));
            sorted_long_vector.push_back(static_cast<long>(i));
        }
    }
    ~TestDataUtil() {

    }
    std::vector<int> get_shuffled_int_vector() {
        return Shuffle<int>::shuffle_vector(sorted_int_vector);
    }


    std::vector<long> get_shuffled_long_vector() {
        return Shuffle<long>::shuffle_vector(sorted_long_vector);
    }


    template<typename T>
    static T** get_vector_data_ptr_arr(std::vector<T>& vec) {
        T** ptr_arr = new T*[vec.size()];
        for (size_t i = 0; i < vec.size(); i++) {
            ptr_arr[i] = &vec[i];
        }
        return ptr_arr;
    }

    template<size_t N, size_t FROM, size_t TO>
    static std::vector<int> get_random_int_vecotor() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::vector<int> vec(N);
        std::uniform_int_distribution<> dis(FROM, TO);
        for (size_t i = 0; i < N; ++i) {
            vec[i] = dis(gen);
        }
        return vec;
    }

    template<size_t N, size_t FROM, size_t TO>
    static std::vector<long> get_random_long_vecotor() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::vector<long> vec(N);
        std::uniform_int_distribution<> dis(FROM, TO);
        for (size_t i = 0; i < N; ++i) {
            vec[i] = dis(gen);
        }
        return vec;
    }

    
};


#endif