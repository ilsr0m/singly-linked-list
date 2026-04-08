#ifndef SLIST_TRIM_FRONT_HPP
#define SLIST_TRIM_FRONT_HPP

#include "test_base.hpp"
#include <tuple>

/*
    Test null cases
*/
using TrimFrontNull = ::testing::TestWithParam<std::tuple<slist_t*, size_t>>;

TEST_P(TrimFrontNull, TrimFrontTest) {
    std::tuple<slist_t*, size_t> tu = GetParam();
    slist_t* slst = std::get<0>(tu);
    EXPECT_EQ(slist_trim_front(slst, std::get<1>(tu)), API_RESULT_ON_FAILURE);
    if(slst) slist_delete(&slst);
}

INSTANTIATE_TEST_SUITE_P(TrimFrontNullSuite, TrimFrontNull, ::testing::Values (
    std::make_tuple(nullptr, 0),
    std::make_tuple(slist_create(sizeof(int)), 2)
));

/*
    Test full cases
*/

struct TrimFrontFullParam {
    std::vector<int> base;
    unsigned count;
    std::vector<int> target;
    TrimFrontFullParam(std::vector<int> base, unsigned count, std::vector<int> target) 
    : base{std::move(base)}, count{count}, target{std::move(target)} {}
};

class TrimFrontFull : public TestBase<TrimFrontFullParam> {};

TEST_P(TrimFrontFull, TrimFrontTest) {
    TrimFrontFullParam trim = GetParam();
    FillList(trim.base);
    EXPECT_EQ(slist_trim_front(lst, trim.count), trim.count);
    CompareWith(trim.target);
    ClearList();
}

INSTANTIATE_TEST_SUITE_P(TrimFrontFullSuite, TrimFrontFull, ::testing::Values (
    TrimFrontFullParam({1, 2, 3, 4, 5}, 0, {1, 2, 3, 4, 5}),
    TrimFrontFullParam({1, 2, 3, 4, 5}, 1, {2, 3, 4, 5}),
    TrimFrontFullParam({1, 2, 3, 4, 5}, 2, {3, 4, 5}),
    TrimFrontFullParam({1, 2, 3, 4, 5}, 3, {4, 5}),
    TrimFrontFullParam({1, 2, 3, 4, 5}, 4, {5}),
    TrimFrontFullParam({1, 2, 3, 4, 5}, 5, {})
));


#endif