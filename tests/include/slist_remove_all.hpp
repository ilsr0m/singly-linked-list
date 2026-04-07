#ifndef SLIST_REMOVE_ALL_HPP
#define SLIST_REMOVE_ALL_HPP

#include "slist_remove.hpp"

/*
    Test null cases
*/
class RemoveAllNull : public RemoveNull {};

TEST_P(RemoveAllNull, RemoveAllTest) {
    RemoveNullParam rm = GetParam();
    EXPECT_EQ(slist_remove_all(rm.singleList, rm.key, rm.comparator), API_RESULT_ON_FAILURE);
    if(rm.singleList) slist_delete(&rm.singleList);
}

INSTANTIATE_TEST_SUITE_P(RemoveAllNullSuite, RemoveAllNull, ::testing::Values(
    RemoveNullParam(nullptr                  , nullptr                 , nullptr                         ), // nullptr
    RemoveNullParam(slist_create(sizeof(int)), nullptr                 , nullptr                         ), // nullptr
    RemoveNullParam(nullptr                  , test_utils::toVoidPtr(2), nullptr                         ), // nullptr
    RemoveNullParam(nullptr                  , nullptr                 , &test_utils::ascending), // nullptr
    RemoveNullParam(slist_create(sizeof(int)), test_utils::toVoidPtr(2), nullptr                         ), // nullptr
    RemoveNullParam(nullptr                  , test_utils::toVoidPtr(2), &test_utils::ascending), // nullptr
    RemoveNullParam(slist_create(sizeof(int)), nullptr                 , &test_utils::ascending), // nullptr
    RemoveNullParam(slist_create(sizeof(int)), test_utils::toVoidPtr(2), &test_utils::ascending)  // empty list
));

/*
    Test full cases
*/
class RemoveAll : public Remove {};

TEST_P(RemoveAll, RemoveAllTest) {
    RemoveParam rm = GetParam();
    FillList(rm.base);
    EXPECT_EQ(slist_remove_all(lst, &rm.keys[0], rm.cmp), rm.result);
    CompareWith(rm.target);
    ClearList();
}

// base, keys, target 
INSTANTIATE_TEST_SUITE_P(RemoveAllFullSuite, RemoveAll, ::testing::Values(
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {6}                     , {1, 2, 3, 4, 5, 1, 1, 7}, &test_utils::ascending, API_RESULT_ON_FAILURE), // invalid key
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {1}                     , {2, 3, 4, 5, 7}         , &test_utils::ascending, 3), // single remove in head
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {7}                     , {1, 2, 3, 4, 5, 1, 1}   , &test_utils::ascending, 1), // single remove in tail
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {4}                     , {1, 2, 3, 5, 1, 1, 7}   , &test_utils::ascending, 1), // single remove in middle
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 1}, {1}                     , {2, 3, 4, 5}            , &test_utils::ascending, 4), // single remove in head
    RemoveParam({1, 1, 3, 4, 5, 1, 1, 7}, {1}                     , {3, 4, 5, 7}            , &test_utils::ascending, 4), // single remove in tail
    RemoveParam({0, 2, 3, 4, 5, 1, 1, 7}, {1}                     , {0, 2, 3, 4, 5, 7}      , &test_utils::ascending, 2), // multiple remove
    RemoveParam({0, 0, 3, 0, 5, 0, 1, 0}, {0}                     , {3, 5, 1}      , &test_utils::ascending, 5) // single remove in middle
));
#endif