#ifndef SLIST_INSERT_HPP
#define SLIST_INSERT_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct InsertNullParam {
    slist_t *singleList;
    const void *item;
    const size_t position;

    InsertNullParam(slist_t *singleList, const void *item, const size_t position)
        : singleList{singleList}, item{item}, position{position} {}
};

class InsertNull : public TestBase<InsertNullParam> {};

TEST_P(InsertNull, InsertTest) {
    InsertNullParam testValues = GetParam();
    if(testValues.singleList) 
        InsertNull::FillList(testValues.singleList, {1, 2, 3, 4, 5});
    EXPECT_EQ(slist_insert(
        testValues.singleList, testValues.item, testValues.position), API_RESULT_ON_FAILURE);
    if(testValues.singleList) slist_delete(&testValues.singleList);
}

INSTANTIATE_TEST_SUITE_P(InsertNullSuite, InsertNull, ::testing::Values(
    InsertNullParam(nullptr                  , nullptr                  , 15), // !lst, !item, pos >
    InsertNullParam(nullptr                  , nullptr                  , 0 ), // !lst, !item
    InsertNullParam(slist_create(sizeof(int)), nullptr                  , 15), // !item, pos >
    InsertNullParam(nullptr                  , test_utils::toVoidPtr(10), 10), // !lst, pos >
    InsertNullParam(nullptr                  , test_utils::toVoidPtr(10), 0 ), // !lst
    InsertNullParam(slist_create(sizeof(int)), nullptr                  , 0 ), // !item
    InsertNullParam(slist_create(sizeof(int)), test_utils::toVoidPtr(10), 15)  // pos >
));

/*
    Test full cases
*/
struct InsertFullParam {
    std::vector<int> baseValues;
    std::vector<int> targetValues;
    int item;
    int position;
    int result;
    
    InsertFullParam( std::vector<int> baseValues, std::vector<int> targetValues,
        int item, int position, int result) 
        : baseValues{std::move(baseValues)}, targetValues{std::move(targetValues)},
         item{item}, position{position}, result{result} {}
};

class InsertFull : public TestBase<InsertFullParam> {};

TEST_P(InsertFull, InsertTest) {
    InsertFullParam testValues = GetParam();
    FillList(testValues.baseValues);
    int result = slist_insert(lst, &testValues.item, testValues.position);
    if(testValues.position > testValues.baseValues.size()) {
        EXPECT_EQ(result, API_RESULT_ON_FAILURE);
        CompareWith(testValues.baseValues);
    }
    else {
        EXPECT_EQ(result, API_RESULT_ON_SUCCESS);
        CompareWith(testValues.targetValues);
    }
    ClearList();
};

INSTANTIATE_TEST_SUITE_P(InsertFullSuite, InsertFull, ::testing::Values(
    InsertFullParam({}          , {}             , 2, 1, API_RESULT_ON_FAILURE), // Position > Size 
    InsertFullParam({1, 2, 3, 4}, {}             , 2, 5, API_RESULT_ON_FAILURE), // Position > Size 
    InsertFullParam({}          , {0}            , 0, 0, API_RESULT_ON_SUCCESS), // Empty
    InsertFullParam({1, 2, 3, 4}, {2, 1, 2, 3, 4}, 2, 0, API_RESULT_ON_SUCCESS), // Insert as the first item
    InsertFullParam({1, 2, 3, 4}, {1, 2, 3, 4, 2}, 2, 4, API_RESULT_ON_SUCCESS), // Insert as the last item
    InsertFullParam({1, 2, 3, 4}, {1, 5, 2, 3, 4}, 5, 1, API_RESULT_ON_SUCCESS), // Insert as the middle item
    InsertFullParam({1, 2, 3, 4}, {1, 2, 5, 3, 4}, 5, 2, API_RESULT_ON_SUCCESS), // Insert as the middle item
    InsertFullParam({1, 2, 3, 4}, {1, 2, 3, 2, 4}, 2, 3, API_RESULT_ON_SUCCESS)  // Insert as the middle item
));

#endif