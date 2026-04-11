#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(FilterNull, FilterTest) {
    auto [lst, contOpt, pred] = GetParam();
    const void *cont = contOpt ? static_cast<const void*>(&*contOpt) : nullptr;
    EXPECT_EQ(slist_filter(lst, pred, cont), nullptr);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(FilterNullSuite, FilterNull, ::testing::Values(
    std::make_tuple(static_cast<slist_t*>(nullptr), std::nullopt, static_cast<predicate_fn>(nullptr)), 
    std::make_tuple(slist_create(sizeof(int)), std::nullopt, static_cast<predicate_fn>(nullptr)), 
    std::make_tuple(static_cast<slist_t*>(nullptr), std::optional<int>(2), static_cast<predicate_fn>(nullptr)), 
    std::make_tuple(static_cast<slist_t*>(nullptr), std::nullopt, &test_utils::greater), 
    std::make_tuple(slist_create(sizeof(int)), std::optional<int>(2), static_cast<predicate_fn>(nullptr)), 
    std::make_tuple(static_cast<slist_t*>(nullptr), std::optional<int>(2), &test_utils::greater),
    std::make_tuple(slist_create(sizeof(int)), std::nullopt, &test_utils::greater)
));

TEST_P(FilterFull, FilterTest) {
    auto [lst, context, filtered] = GetParam();
    slist_t *fLst = slist_filter(lst, tuti::greater, &context);
    tuti::compareWith(fLst, filtered);
    tuti::tearDown({lst, fLst});
}

INSTANTIATE_TEST_SUITE_P(FilterFullSuite, FilterFull, ::testing::Values(
    std::make_tuple(tuti::toSlist(std::vector<int>{1, 2, 4}), 3, std::vector<int>{4}),
    std::make_tuple(tuti::toSlist(std::vector<int>{1, 2, 2, 1, 0}), 3, std::vector<int>{}),
    std::make_tuple(tuti::toSlist(std::vector<int>{1, 5, 4, 5, 0}), 3, std::vector<int>{5, 4, 5}),
    std::make_tuple(tuti::toSlist(std::vector<int>{}), 3, std::vector<int>{}),
    std::make_tuple(tuti::toSlist(std::vector<int>{6, 5, 4, 5, 0}), 3, std::vector<int>{6, 5, 4, 5}),
    std::make_tuple(tuti::toSlist(std::vector<int>{0, 0, 4, 5, 8}), 3, std::vector<int>{4, 5, 8})
));