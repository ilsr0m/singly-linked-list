#ifndef SLIST_REMOVE_HPP
#define SLIST_REMOVE_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct RemoveNullParam {
    slist_t *singleList;
    const void *key;
    comparator_fn comparator;
    RemoveNullParam(slist_t *singleList, const void *key, comparator_fn comparator) 
        : singleList{singleList}, key{key}, comparator{comparator} {}
};

class RemoveNull : public TestBase<RemoveNullParam> {
};

TEST_P(RemoveNull, RemoveTest) {
    RemoveNullParam rm = GetParam();
    EXPECT_EQ(slist_remove(rm.singleList, rm.key, rm.comparator), API_RESULT_ON_FAILURE);
    if(rm.singleList) slist_delete(&rm.singleList);
}

INSTANTIATE_TEST_SUITE_P(RemoveSuite, RemoveNull, ::testing::Values(
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
struct RemoveParam {
    comparator_fn cmp;
    std::vector<int> base;
    std::vector<int> keys;
    std::vector<int> target;
    int result;

    RemoveParam(std::vector<int> base, std::vector<int> keys, std::vector<int> target, comparator_fn cmp, int result) : 
        cmp{cmp}, keys{std::move(keys)}, base{std::move(base)}, target{std::move(target)}, result{result} {}
};

class Remove : public TestBase<RemoveParam> {
public:

};

TEST_P(Remove, RemoveTest) {
    RemoveParam rm = GetParam();
    FillList(rm.base);
    for(auto k : rm.keys) {
        EXPECT_EQ(slist_remove(lst, &k, rm.cmp), rm.result);
    }
    CompareWith(rm.target);
    ClearList();
}

// base, keys, target 
INSTANTIATE_TEST_SUITE_P(RemoveSuite, Remove, ::testing::Values(
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {6}                     , {1, 2, 3, 4, 5, 1, 1, 7}, &test_utils::ascending, API_RESULT_ON_FAILURE), // invalid key
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {1}                     , {2, 3, 4, 5, 1, 1, 7}   , &test_utils::ascending, API_RESULT_ON_SUCCESS), // single remove in head
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {7}                     , {1, 2, 3, 4, 5, 1, 1}   , &test_utils::ascending, API_RESULT_ON_SUCCESS), // single remove in tail
    RemoveParam({1, 2, 3, 4, 5, 1, 1, 7}, {4}                     , {1, 2, 3, 5, 1, 1, 7}   , &test_utils::ascending, API_RESULT_ON_SUCCESS), // single remove in middle
    RemoveParam({0, 2, 3, 4, 5, 1, 1, 7}, {1, 1}                  , {0, 2, 3, 4, 5, 7}      , &test_utils::ascending, API_RESULT_ON_SUCCESS), // multiple remove
    RemoveParam({0, 2, 3, 4, 5, 1, 1, 7}, {0, 2}                  , {3, 4, 5, 1, 1, 7}      , &test_utils::ascending, API_RESULT_ON_SUCCESS), // single remove in middle
    RemoveParam({0, 2, 3, 4, 5, 1, 1, 7}, {7, 1}                  , {0, 2, 3, 4, 5, 1}      , &test_utils::ascending, API_RESULT_ON_SUCCESS), // single remove in middle
    RemoveParam({0, 2, 3, 4, 5, 1, 1, 7}, {0, 2, 3, 4, 5, 1, 1, 7}, {}                      , &test_utils::ascending, API_RESULT_ON_SUCCESS)  // remove all values
));

#endif