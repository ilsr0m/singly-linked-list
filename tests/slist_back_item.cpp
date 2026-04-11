#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(BackItemNull, BackItemTest) {
    auto lst = GetParam();
    EXPECT_EQ(slist_back_item(lst), nullptr);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(BackItemNullSuite, BackItemNull, ::testing::Values (
    static_cast<slist_t*>(nullptr), slist_create(sizeof(int))
));

TEST_P(BackItemFull, BackItemTest) {
    auto [v, val] = GetParam();
    slist_t* lst = tuti::toSlist(v);
    EXPECT_EQ(*(int*)slist_back_item(lst), val);
    tuti::compareWith(lst, v);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(BackItemFullSuite, BackItemFull, ::testing::Values (
    std::make_tuple((std::vector<int>{1, 2, 3, 4, 5}), 5),
    std::make_tuple((std::vector<int>{2, 1, 3, 5, 4}), 4),
    std::make_tuple((std::vector<int>{5, 2, 1, 4, 3}), 3),
    std::make_tuple((std::vector<int>{4, 5, 3, 1, 2}), 2),
    std::make_tuple((std::vector<int>{5, 2, 3, 4, 1}), 1)
));