#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(BogosortNull, BogosortTest) {
    auto [lst, cmp] = GetParam();
    EXPECT_EQ(slist_bogosort(lst, cmp), tuti::onFailure);
    EXPECT_EQ(slist_is_sorted(lst, cmp), tuti::onFailure);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(BogosortNullSuite, BogosortNull, ::testing::Values(
    std::make_tuple(static_cast<slist_t*>(nullptr), static_cast<comparator_fn>(nullptr)),
    std::make_tuple(static_cast<slist_t*>(nullptr), &test_utils::ascending),
    std::make_tuple(slist_create(sizeof(int)), static_cast<comparator_fn>(nullptr))
));

TEST_P(BogosortFull, BogosortTest) {
    SortFullParam testValues = GetParam();
    slist_t *lst = tuti::toSlist(testValues.disordered);
    EXPECT_EQ(slist_bogosort(lst, testValues.comparator), tuti::onSuccess);
    EXPECT_EQ(slist_size(lst), testValues.disordered.size());
    EXPECT_EQ(slist_size(lst), testValues.sorted.size());

    if(!slist_size(lst)) tuti::testEmpty(lst);
    else tuti::compareWith(lst, testValues.sorted);
    EXPECT_EQ(slist_is_sorted(lst, testValues.comparator), 1);
    tuti::tearDown(lst);
};

INSTANTIATE_TEST_SUITE_P(BogosortFullSuite, BogosortFull, ::testing::Values(
    SortFullParam(&test_utils::ascending , {}          , {}),
    SortFullParam(&test_utils::ascending , {111}       , {111}),
    SortFullParam(&test_utils::ascending , {2, 1}      , {1, 2}),
    SortFullParam(&test_utils::ascending , {2, 1, 3}   , {1, 2, 3}),
    SortFullParam(&test_utils::descending, {1, 2}      , {2, 1}),
    SortFullParam(&test_utils::descending, {3, 1, 2}   , {3, 2, 1})
));
