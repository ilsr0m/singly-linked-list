#ifndef SLIST_APPEND_HPP
#define SLIST_APPEND_HPP

#include "test_base.hpp"

/*
    Test null cases
*/
struct AppendNullParam {
    slist_t * singleList;
    const void *item;
    AppendNullParam(slist_t * singleList, const void *item) 
        : singleList{singleList}, item{item} {}
};

class AppendNull : public TestBase<AppendNullParam> {};

TEST_P(AppendNull, AppendTest) {
    AppendNullParam testValues = GetParam();
    EXPECT_EQ(slist_append(testValues.singleList, testValues.item), API_RESULT_ON_FAILURE);
    if(testValues.singleList) slist_delete(&testValues.singleList);
}

INSTANTIATE_TEST_SUITE_P(AppendNullSuite, AppendNull, ::testing::Values (
    AppendNullParam(nullptr, nullptr),
    AppendNullParam(slist_create(sizeof(int)), nullptr),
    AppendNullParam(nullptr, test_utils::toVoidPtr(2))
));

/*
    Test full cases
*/
struct AppendParam {
    std::vector<int> values;
    AppendParam(std::vector<int> values) : values{std::move(values)} {}
};

class Append : public TestBase<AppendParam> {};

TEST_P(Append, AppendTest) {
    AppendParam testValues = GetParam();
    if(testValues.values.size()) {
        // Append all vector's values one by one
        for(auto v : testValues.values)
            EXPECT_EQ(slist_append(lst, &v), API_RESULT_ON_SUCCESS);
        CompareWith(testValues.values);
        ClearList();
        return;
    }
    IsEmpty();
}

INSTANTIATE_TEST_SUITE_P(AppendFullSuite, Append, ::testing::Values (
    AppendParam({}                    ),
    AppendParam({111}                 ),
    AppendParam({1, 2}                ),
    AppendParam({2, 5, 4}             ),
    AppendParam({-11, 1, 2, 5, 6, 9}  )
));

#endif