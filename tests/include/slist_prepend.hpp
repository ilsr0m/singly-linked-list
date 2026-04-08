#ifndef SLIST_PREPEND_HPP
#define SLIST_PREPEND_HPP

#include "slist_append.hpp"

/*
    Test null cases
*/
class PrependNull : public AppendNull {};

TEST_P(AppendNull, PrependTest){
    AppendNullParam testValues = GetParam();
    EXPECT_EQ(slist_prepend(testValues.singleList, testValues.item), API_RESULT_ON_FAILURE);
    if(testValues.singleList) slist_delete(&testValues.singleList);
}

INSTANTIATE_TEST_SUITE_P(PrependNullSuite, AppendNull, ::testing::Values (
    AppendNullParam(nullptr, nullptr),
    AppendNullParam(slist_create(sizeof(int)), nullptr),
    AppendNullParam(nullptr, test_utils::toVoidPtr(2))
));

/*
    Test full cases
*/
class Prepend : public AppendFull {
public:
    void CompareWith(std::vector<int> vec) override {
        if(slist_empty(lst)) { 
            IsEmpty(); 
            return; 
        }
        IsNotEmpty();
        EXPECT_EQ(slist_size(lst), vec.size());
        // Tail must be equal to the first vector's item
        EXPECT_EQ(*(int*)snode_data(slist_tail(lst)), vec[0]);
        // Head must be equal to the last vector's item
        EXPECT_EQ(*(int*)snode_data(slist_head(lst)), vec[vec.size() - 1]);
        // Compare each list's item and vector's item
        snode_t *current = slist_head(lst);
        for(unsigned i = vec.size() - 1; i != 0; i--, current = snode_next(current)) 
            EXPECT_EQ(*(int*)snode_data(current), vec[i]);
    };
};

TEST_P(Prepend, PrependTest) {
    AppendFullParam testValues = GetParam();  

    if(testValues.values.size()){
        // Append all vector's values one by one
        for(auto v : testValues.values)
            EXPECT_EQ(slist_prepend(lst, &v), API_RESULT_ON_SUCCESS);
        CompareWith(testValues.values);
        ClearList();
        return;
    }
    IsEmpty();
}

INSTANTIATE_TEST_SUITE_P(PrependFullSuite, Prepend, ::testing::Values(
    AppendFullParam({}                  ),
    AppendFullParam({111}               ),
    AppendFullParam({1, 2}              ),
    AppendFullParam({2, 5, 4}           ),
    AppendFullParam({-11, 1, 2, 5, 6, 9})
));

#endif
