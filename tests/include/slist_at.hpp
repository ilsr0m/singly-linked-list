#ifndef SLIST_AT_HPP
#define SLIST_AT_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct AtNullParam {
    slist_t *slst;
    const size_t index;
    AtNullParam(slist_t *slst, const size_t index) 
        : slst{slst}, index{index} {}
};

class AtNull : public TestBase<AtNullParam> {};

TEST_P(AtNull, AtTest) {
    AtNullParam set = GetParam();
    EXPECT_EQ(slist_at(set.slst, set.index), nullptr);
    if(set.slst) slist_delete(&set.slst);
}

INSTANTIATE_TEST_SUITE_P(AtNullSuite, AtNull, ::testing::Values(
    AtNullParam(nullptr, 10),
    AtNullParam(slist_create(sizeof(int)), 10)
));

/*
    Test full cases
*/
struct AtFullParam {
    std::vector<int> base;
    size_t index;
    int value;
    AtFullParam(std::vector<int> base, size_t index, int value) 
            : base{std::move(base)}, index{index}, value{value}   {}
};

class AtFull : public TestBase<AtFullParam> {};

TEST_P(AtFull, AtTest) {
    AtFullParam set = GetParam();
    FillList(set.base);
    int result = *(int*)slist_at(lst, set.index);
    CompareWith(set.base); // check if nothing changed
    EXPECT_EQ(result, set.value);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(AtFullSuite, AtFull, ::testing::Values(
    AtFullParam({1, 2, 3}, 0, 1),
    AtFullParam({1, 2, 3}, 1, 2),
    AtFullParam({1, 2, 3}, 2, 3)
));

#endif