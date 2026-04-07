#ifndef SLIST_REMOVE_AT_HPP
#define SLIST_REMOVE_AT_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct RemoveAtNullParam {
    slist_t *slst;
    const size_t position;
    RemoveAtNullParam(slist_t *slst, const size_t position) 
        : slst{slst}, position{position} {}
};

class RemoveAtNull : public TestBase<RemoveAtNullParam> {};

TEST_P(RemoveAtNull, RemoveAtTest) {
    RemoveAtNullParam rat = GetParam();
    if(rat.slst) RemoveAtNull::FillList(rat.slst, {1, 2, 3, 4 ,5});
    EXPECT_EQ(slist_remove_at(rat.slst, rat.position), API_RESULT_ON_FAILURE);
    if(rat.slst) slist_delete(&rat.slst);
}

INSTANTIATE_TEST_SUITE_P(RemoveAtSuite, RemoveAtNull, ::testing::Values(
    RemoveAtNullParam(nullptr                  , 10), // !lst, pos >
    RemoveAtNullParam(nullptr                  , 0 ), // !list
    RemoveAtNullParam(slist_create(sizeof(int)), 10)  // pos >
));

/*
    Test full cases
*/
struct RemoveAtParam {
    std::vector<int> base;
    std::vector<int> positions;
    std::vector<int> target;
    int result;

    RemoveAtParam(std::vector<int> base, std::vector<int> positions, 
        std::vector<int> target, int result) 
        : base{base}, positions{positions}, target{target}, result{result} {}
};

class RemoveAt : public TestBase<RemoveAtParam> {};

TEST_P(RemoveAt, RemoveAtTest) {
    RemoveAtParam rat = GetParam();
    FillList(rat.base);
    for(auto p : rat.positions) 
        EXPECT_EQ(slist_remove_at(lst, p), rat.result);
    CompareWith(rat.target);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(RemoveAtSuite, RemoveAt, ::testing::Values(
    RemoveAtParam({}, {1}      , {}, API_RESULT_ON_FAILURE),
    RemoveAtParam({}, {1, 2, 3}, {}, API_RESULT_ON_FAILURE),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {0}, {2, 3, 4, 5, 6}, API_RESULT_ON_SUCCESS),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {0, 0}, {3, 4, 5, 6}, API_RESULT_ON_SUCCESS),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {5}, {1, 2, 3, 4, 5}, API_RESULT_ON_SUCCESS),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {5, 4}, {1, 2, 3, 4}, API_RESULT_ON_SUCCESS),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {2}, {1, 2, 4, 5, 6}, API_RESULT_ON_SUCCESS),
    RemoveAtParam({1, 2, 3, 4, 5, 6}, {2, 2}, {1, 2, 5, 6}, API_RESULT_ON_SUCCESS)
));

#endif