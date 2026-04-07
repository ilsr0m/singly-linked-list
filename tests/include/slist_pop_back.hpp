#ifndef SLIST_POP_BACK_HPP
#define SLIST_POP_BACK_HPP

#include "slist_pop_front.hpp"

/*
    Test null cases
*/
// class PopBackNull : public PopFrontNull {};
using PopBackNull = ::testing::TestWithParam<slist_t*>;
TEST_P(PopBackNull, PopBackTest) {
    slist_t* slst = GetParam();
    EXPECT_EQ(slist_pop_back(slst), nullptr);
    if(slst) slist_delete(&slst);
}

// null and empty
INSTANTIATE_TEST_SUITE_P(PopBackNullSuite, PopBackNull, ::testing::Values (
    nullptr, slist_create(sizeof(int))
));

/*
    Test full cases
*/
class PopBack : public PopFront {};

TEST_P(PopBack, PopBackTest) {
    PopFrontParam pop = GetParam();
    FillList(pop.base);
    for(unsigned i = 0; i < pop.count; i++)
        EXPECT_EQ(*(int*)slist_pop_back(lst), pop.popped[i]);
    CompareWith(pop.target);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(PopBackFullSuite, PopBack, ::testing::Values(
    PopFrontParam({1, 2, 3}, 1, {1, 2}, {3}),
    PopFrontParam({1, 2, 3}, 2, {1}, {3, 2}),
    PopFrontParam({1, 2, 3}, 3, {}, {3, 2, 1})
));

#endif