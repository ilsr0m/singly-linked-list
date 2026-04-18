#include "test_utils.hpp"
#include "test_fixtures.hpp"

TEST_P(PopFrontNull, PopFrontTest) {
    slist_t* slst = GetParam();
    EXPECT_EQ(slist_pop_front(slst), tuti::onFailure);
    tuti::tearDown(slst);
}

// null and empty
INSTANTIATE_TEST_SUITE_P(PopFrontNullSuite, PopFrontNull, ::testing::Values (
    nullptr, slist_create(sizeof(int))
));

TEST_P(PopFrontFull, PopFrontTest) {
    PopFrontFullParam pop = GetParam();
    slist_t *lst = tuti::toSlist(pop.base);
    for(unsigned i = 0; i < pop.count; i++) {
        EXPECT_EQ(slist_pop_front(lst), tuti::onSuccess);
    }
    tuti::compareWith(lst, pop.target);
    tuti::tearDown(lst);
}

INSTANTIATE_TEST_SUITE_P(PopFrontFullSuite, PopFrontFull, ::testing::Values(
    PopFrontFullParam({1, 2, 3}, 1, {2, 3}, {1}),
    PopFrontFullParam({1, 2, 3}, 2, {3}, {1, 2}),
    PopFrontFullParam({1, 2, 3}, 3, {}, {1, 2, 3})
));
