#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <vector>

extern "C" {
    #include "single_list.h"
}

namespace test_utils {
    
    template <typename T>
    const void* toVoidPtr(const T& value) { return &value; }

    // comparator
    static int ascending(const void* a, const void* b) {
        int _a = *(int*)a;
        int _b = *(int*)b;
        if(_a > _b) return 1;
        if(_a == _b) return 0;
        return -1;
    }

    // reversed comparator
    static int descending(const void* a, const void* b) {
        int _a = *(int*)a;
        int _b = *(int*)b;
        if(_a > _b) return -1;
        if(_a == _b) return 0;
        return 1;
    }

}

#endif