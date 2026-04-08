#ifndef SLIST_SORT_HPP
#define SLIST_SORT_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct SortNullParam {
    slist_t * singleList;
    comparator_fn comparator;
    SortNullParam(slist_t * singleList, comparator_fn comparator) 
      : singleList{singleList}, comparator{comparator} {}
};

class SortNull : public TestBase<SortNullParam> {};

TEST_P(SortNull, SortTest) {
    SortNullParam testValues = GetParam();
    EXPECT_EQ(slist_sort(testValues.singleList, testValues.comparator), API_RESULT_ON_FAILURE);
    if(testValues.singleList) slist_delete(&testValues.singleList);
}

INSTANTIATE_TEST_SUITE_P(SortNullSuite, SortNull, ::testing::Values(
    SortNullParam(nullptr, nullptr),
    SortNullParam(nullptr, &test_utils::ascending),
    SortNullParam(slist_create(sizeof(int)), nullptr)
));

/*
    Test full cases
*/
struct SortParam {
    comparator_fn comparator;
    std::vector<int> disordered;
    std::vector<int> sorted;

    SortParam(comparator_fn comparator, std::vector<int> disordered, std::vector<int> sorted) : 
        comparator{comparator}, disordered{disordered}, sorted{sorted} {}
};

class Sort : public TestBase<SortParam> {};  

TEST_P(Sort, SortTest) {
    SortParam testValues = GetParam();
    
    FillList(testValues.sorted);
    EXPECT_EQ(slist_sort(lst, testValues.comparator), API_RESULT_ON_SUCCESS);

    EXPECT_EQ(slist_size(lst), testValues.disordered.size());
    EXPECT_EQ(slist_size(lst), testValues.sorted.size());

    if(!slist_size(lst)) IsEmpty();
    else CompareWith(testValues.sorted);
    ClearList();
};

INSTANTIATE_TEST_SUITE_P(SortFullSuite, Sort, ::testing::Values(
    SortParam(&test_utils::ascending , {}                    , {}                    ),
    SortParam(&test_utils::ascending , {111}                 , {111}                 ),
    SortParam(&test_utils::ascending , {2, 1}                , {1, 2}                ),
    SortParam(&test_utils::ascending , {9, 0, 2, 1, 6, 5}    , {0, 1, 2, 5, 6, 9}    ),
    SortParam(&test_utils::ascending , {9, 0, 2, 1, 6, 5, 44}, {0, 1, 2, 5, 6, 9, 44}),
    SortParam(&test_utils::descending, {}                    , {}                    ),
    SortParam(&test_utils::descending, {111}                 , {111}                 ),
    SortParam(&test_utils::descending, {1, 2}                , {2, 1}                ),
    SortParam(&test_utils::descending, {9, 0, 2, 1, 6, 5}    , {9, 6, 5, 2, 1, 0}    ),
    SortParam(&test_utils::descending, {9, 0, 2, 1, 6, 5, 44}, {44, 9, 6, 5, 2, 1, 0})
));

#endif
