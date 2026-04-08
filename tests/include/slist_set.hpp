#ifndef SLIST_SET_HPP
#define SLIST_SET_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct SetNullParam {
    slist_t *slst;
    const size_t index;
    const void *item;
    SetNullParam(slist_t *slst, const size_t index, const void *item) 
        : slst{slst}, index{index}, item{item} {}
};

class SetNull : public TestBase<SetNullParam> {};

TEST_P(SetNull, SetTest) {
    SetNullParam set = GetParam();
    EXPECT_EQ(slist_set(set.slst, set.index, set.item), API_RESULT_ON_FAILURE);
    if(set.slst) slist_delete(&set.slst);
}

INSTANTIATE_TEST_SUITE_P(SetNullSuite, SetNull, ::testing::Values(
    SetNullParam(nullptr                  , 10, nullptr), 
    SetNullParam(nullptr                  , 10, test_utils::toVoidPtr(1)), 
    SetNullParam(slist_create(sizeof(int)), 10, nullptr),
    SetNullParam(slist_create(sizeof(int)), 0, test_utils::toVoidPtr(1))   
));

/*
    Test full cases
*/
struct SetFullParam {
    struct DataParam {
        size_t index;
        int item;
        DataParam (size_t index, int item) : 
        index{index}, item{item} {}
    };

    std::vector<int> base;
    std::vector<DataParam> datas;
    std::vector<int> target;
    int result;
    SetFullParam(std::vector<int> base, std::vector<DataParam> datas, 
        std::vector<int> target, int result) 
            : base{base}, datas{datas}, 
            target{target}, result{result}   {}
};

class SetFull : public TestBase<SetFullParam> {};

TEST_P(SetFull, SetTest) {
    SetFullParam set = GetParam();
    FillList(set.base);
    for(auto d : set.datas) {
        int result = slist_set(lst, d.index, &d.item);
        EXPECT_EQ(result, set.result);
    }
    CompareWith(set.target);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(SetFullSuite, SetFull, ::testing::Values(
    SetFullParam({1, 2, 3}, {{4, 0}}, {1, 2, 3}, API_RESULT_ON_FAILURE), // index out of range

    SetFullParam({1, 2, 3}, {{0, 0}}, {0, 2, 3}, API_RESULT_ON_SUCCESS), 
    SetFullParam({1, 2, 3}, {{1, 0}}, {1, 0, 3}, API_RESULT_ON_SUCCESS),
    SetFullParam({1, 2, 3}, {{2, 0}}, {1, 2, 0}, API_RESULT_ON_SUCCESS),
    SetFullParam({1, 2, 3}, {{0, 0}, {1, 0}}, {0, 0, 3}, API_RESULT_ON_SUCCESS),
    SetFullParam({1, 2, 3}, {{2, 0}, {0, 6}, {1, 5}}, {6, 5, 0}, API_RESULT_ON_SUCCESS),
    SetFullParam({1, 2, 3, 4}, {{1, 0}, {2, 7}}, {1, 0, 7, 4}, API_RESULT_ON_SUCCESS)
));

#endif