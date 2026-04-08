#ifndef SLIST_POP_FRONT_HPP
#define SLIST_POP_FRONT_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
using PopFrontNull = ::testing::TestWithParam<slist_t*>;

TEST_P(PopFrontNull, PopFrontTest) {
    slist_t* slst = GetParam();
    EXPECT_EQ(slist_pop_front(slst), nullptr);
    if(slst) slist_delete(&slst);
}

// null and empty
INSTANTIATE_TEST_SUITE_P(PopFrontNullSuite, PopFrontNull, ::testing::Values (
    nullptr, slist_create(sizeof(int))
));

/*
    Test full cases
*/
struct PopFrontParam {
    std::vector<int> base;
    unsigned count;
    std::vector<int> target;
    std::vector<int> popped;
    PopFrontParam(std::vector<int> base, unsigned popCount, std::vector<int> target, std::vector<int> popped) 
        : base{std::move(base)}, count{popCount}, target{std::move(target)}, popped{std::move(popped)} {}
};

class PopFront : public TestBase<PopFrontParam> {};

TEST_P(PopFront, PopFrontTest) {
    PopFrontParam pop = GetParam();
    FillList(pop.base);
    for(unsigned i = 0; i < pop.count; i++)
        EXPECT_EQ(*(int*)slist_pop_front(lst), pop.popped[i]);
    CompareWith(pop.target);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(PopFrontFullSuite, PopFront, ::testing::Values(
    PopFrontParam({1, 2, 3}, 1, {2, 3}, {1}),
    PopFrontParam({1, 2, 3}, 2, {3}, {1, 2}),
    PopFrontParam({1, 2, 3}, 3, {}, {1, 2, 3})
));

#endif