#include <gtest/gtest.h>

extern "C"{
    #include "list_c.h"
}

class ListTest : public testing::Test {
protected:
    list_t *list;
    int testValues[10] = {9, 2, -1, 5, 7, 0, 4, 5, 3, 1};

    void SetUp() { 
        list = list_create(sizeof(int)); 
        IsEmpty();
    }

    void TearDown() { 
        list_delete(&list);
        EXPECT_EQ(list, nullptr);
    }

    void IsEmpty() {
        EXPECT_NE(list, nullptr); // list is not null, coz it's already initialized
        EXPECT_EQ(list->list_size, 0); // no any items
        EXPECT_EQ(list->head, nullptr); // obviously null
        EXPECT_EQ(list->tail, nullptr); // obviously null
        EXPECT_EQ(list->item_size, sizeof(int));
    }

    void IsNotEmpty() {
        EXPECT_NE(list, nullptr); // list is not null, coz it's already initialized
        EXPECT_NE(list->head, nullptr); 
        EXPECT_NE(list->tail, nullptr); 
        EXPECT_GT(list->list_size, 0); 
        EXPECT_EQ(list->item_size, sizeof(int));
    }

    void Clear() {
        list_clear(list);
        IsEmpty();
    }

    void FillList(int (*add)(list_t* list, const void* data)){
        int result;
        for(int i = 0; i < 10; i++){
            result = add(list, &testValues[i]);
            EXPECT_EQ(result, 0);
        }
        IsNotEmpty();
        EXPECT_EQ(list->list_size, 10); 
    }

    // this comparator is needed as arg in list_remove and list_remove_all
    static int RemoveCmp(const void* _item, const void* _key) {
        return (*(int*)_item == *(int*)_key) ? 0 : -1;
    }
};

// function: list_create
TEST_F(ListTest, CreateTest) {
    // First of all, check it with null item size
    list = list_create(0);
    EXPECT_EQ(list, nullptr);

    // Check it with fine item size
    list = list_create(sizeof(int));
    IsEmpty();
}

// function: list_append -> once
TEST_F(ListTest, AppendOnceTest) {
    int result; // return value of funtion 
    int value = 5;

    // First of all, check if item is null
    result = list_append(list, nullptr);
    EXPECT_EQ(result, -1);
    IsEmpty();

    // Check with real value
    result = list_append(list, &value);
    EXPECT_EQ(result, 0);
    IsNotEmpty();

    EXPECT_EQ(list->list_size, 1);     // plus one item
    EXPECT_EQ(list->tail, list->head); // head and tail must be equal
    EXPECT_EQ(*(int*)list->head->item, value); // item is equal to value

    Clear();
}

// function: list_prepend -> once
TEST_F(ListTest, PrependOnceTest) {
    int result; // return value of funtion 
    int value = 5;

    // First of all, check if item is null
    result = list_prepend(list, nullptr);
    EXPECT_EQ(result, -1);
    IsEmpty();

    // Check with real value
    result = list_prepend(list, &value);
    EXPECT_EQ(result, 0);
    IsNotEmpty();

    EXPECT_EQ(list->list_size, 1); // plus one item
    EXPECT_EQ(list->tail, list->head); // head and tail must be equal
    EXPECT_EQ(*(int*)list->head->item, value); // item is equal to value

    Clear();
}

// function: list_append -> multiple times
TEST_F(ListTest, AppendMultipleTest) {
    int result; // return value of funtion 
    // fill list with some values
    FillList(list_append);
    
    // check each value in list
    node_t *list_iter = list->head;
    int value_index = 0;
    while(list_iter != nullptr){
        EXPECT_EQ(*(int*)list_iter->item, testValues[value_index]);
        value_index++;
        list_iter = list_iter->next;
    }

    // check if item is null
    result = list_append(list, nullptr);
    EXPECT_EQ(result, -1);
    IsNotEmpty();
    EXPECT_EQ(list->list_size, 10); 

    Clear();
}

// function: list_prepend -> multiple times
TEST_F(ListTest, PrependMultipleTest){
    int result; // return value of funtion 
    
    // fill list with some values
    FillList(list_prepend);
    
    // check each value in list
    node_t *list_iter = list->head;
    int value_index = 10;
    while(list_iter != nullptr){
        value_index--;
        EXPECT_EQ(*(int*)list_iter->item, testValues[value_index]);
        list_iter = list_iter->next;
    }

    // check if item is null
    result = list_prepend(list, nullptr);
    EXPECT_EQ(result, -1);
    IsNotEmpty();
    EXPECT_EQ(list->list_size, 10); 

    Clear();
}

// function: list_insert
TEST_F(ListTest, InsertTest){
    int result = 0; // return value of funtion 
    // fill list with values to make it not empty
    FillList(list_append);

    // insert as head item
    int v0 = 1;
    result = list_insert(list, &v0, 0);
    EXPECT_EQ(result, 0); 
    IsNotEmpty();
    EXPECT_EQ(*(int*)list->head->item, v0); 
    EXPECT_EQ(list->list_size, 11);
    
    // insert as last item
    int v1 = 1;
    result = list_insert(list, &v1, list->list_size);
    EXPECT_EQ(result, 0); 
    IsNotEmpty();
    EXPECT_EQ(*(int*)list->tail->item, v1);
    EXPECT_EQ(list->list_size, 12);

    // put it in the middle
    int v3 = 8;
    int position = 7;
    result = list_insert(list, &v3, position);
    EXPECT_EQ(result, 0); 
    IsNotEmpty();
    EXPECT_EQ(list->list_size, 13);

    node_t *list_iter = list->head;
    int count = 0;
    while (list_iter != nullptr) {
        if(position == count) break;
        count++;
        list_iter = list_iter->next;
    }
    EXPECT_EQ(*(int*)list_iter->item, v3);
    
    Clear();
}

// function: list_front
TEST_F(ListTest, FrontTest) {
    void* result; // return value of funtion 
    int v1 = 3, v2 = 0;

    result = list_front(list);
    EXPECT_EQ(result, nullptr);

    list_prepend(list, &v1);
    result = list_front(list);
    EXPECT_EQ(*(int*)result, v1);

    list_prepend(list, &v2);
    result = list_front(list);
    EXPECT_EQ(*(int*)result, v2);
    
    Clear();
}

// function: list_back
TEST_F(ListTest, BackTest){
    void* result; // return value of funtion 
    int v1 = 3, v2 = 0;

    result = list_back(list);
    EXPECT_EQ(result, nullptr);

    list_append(list, &v1);
    result = list_back(list);
    EXPECT_EQ(*(int*)result, v1);

    list_append(list, &v2);
    result = list_back(list);
    EXPECT_EQ(*(int*)result, v2);

    Clear();
}

// function: list_remove
TEST_F(ListTest, RemoveOnceTest){
    // Test bundle
    void* removed_item;
    int test_ints_count;
    node_t* test_iter;
    int test_ints_1[9] = {2, -1, 5, 7, 0, 4, 5, 3, 1};  // for Test 1
    int test_ints_2[8] = {2, -1, 5, 7, 0, 4, 5, 3};     // for Test 2
    int test_ints_3[7] = {2, -1, 5, 7, 4, 5, 3};        // for Test 3
    int test_ints_4[6] = {2, -1, 7, 4, 5, 3};           // for Test 4 and Test 5

    // Test 0 - only one item in list
    int once = 4;
    list_append(list, &once);
    removed_item = list_remove(list, &once, ListTest::RemoveCmp);
    EXPECT_EQ(*(int*)removed_item, once);
    IsEmpty();

    FillList(list_append);
    
    // Test 1 - Remove head item
    int head_key = 9; // remove 9 value
    removed_item = list_remove(list, &head_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(*(int*)removed_item, head_key);
    EXPECT_EQ(list->list_size, 9);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_1[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 2 - Remove tail item
    int tail_key = 1; // remove 1 value
    removed_item = list_remove(list, &tail_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(*(int*)removed_item, tail_key);
    EXPECT_EQ(list->list_size, 8);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_2[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 3 - Remove middle item
    int middle_key = 0; // remove 0 value
    removed_item = list_remove(list, &middle_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(*(int*)removed_item, middle_key);
    EXPECT_EQ(list->list_size, 7);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_3[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 4 - Remove value 5 (it must remove only first item with such value)
    int duplicate_key = 5;
    removed_item = list_remove(list, &duplicate_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(*(int*)removed_item, duplicate_key);
    EXPECT_EQ(list->list_size, 6);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_4[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 5 - Try to remove value which the list does not have
    int fake_key = 228;
    removed_item = list_remove(list, &fake_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_item, nullptr);
    EXPECT_EQ(list->list_size, 6);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_4[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    Clear();
}

// function: list_remove_all
TEST_F(ListTest, RemoveAllTest){
    // Test bundle
    int removed_items_count; // for return type
    int test_ints_count;
    node_t* test_iter;
    int test_ints_1[9] = {2, -1, 5, 7, 0, 4, 5, 3, 1};  // for Test 1
    int test_ints_2[8] = {2, -1, 5, 7, 0, 4, 5, 3};     // for Test 2
    int test_ints_3[7] = {2, -1, 5, 7, 4, 5, 3};        // for Test 3
    int test_ints_4[5] = {2, -1, 7, 4, 3};              // for Test 4 and Test 5

    // Test 0 - only one item in list
    int once = 4;
    list_append(list, &once);
    removed_items_count = list_remove_all(list, &once, ListTest::RemoveCmp);
    EXPECT_EQ(removed_items_count, 1);
    IsEmpty();

    // fill list with some values
    FillList(list_append);
    
    // Test 1 - Remove head item
    int head_key = 9; // remove 9 value
    removed_items_count = list_remove_all(list, &head_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_items_count, 1);
    EXPECT_EQ(list->list_size, 9);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_1[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 2 - Remove tail item
    int tail_key = 1; // remove 1 value
    removed_items_count = list_remove_all(list, &tail_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_items_count, 1);
    EXPECT_EQ(list->list_size, 8);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_2[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 3 - Remove middle item
    int middle_key = 0; // remove 0 value
    removed_items_count = list_remove_all(list, &middle_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_items_count, 1);
    EXPECT_EQ(list->list_size, 7);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_3[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 4 - Remove value 5 (it must remove all item with such value)
    int duplicate_key = 5; // remove all fives
    // added the same value more
    list_append(list, &duplicate_key);
    list_append(list, &duplicate_key);
    list_append(list, &duplicate_key);
    list_prepend(list, &duplicate_key);
    list_prepend(list, &duplicate_key);
    list_insert(list, &duplicate_key, 4);
    // start removing all fives
    removed_items_count = list_remove_all(list, &duplicate_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_items_count, 8);
    EXPECT_EQ(list->list_size, 5);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_4[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    // Test 5 - Try to remove value which the list does not have
    int fake_key = 228;
    removed_items_count = list_remove_all(list, &fake_key, ListTest::RemoveCmp);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(removed_items_count, 0);
    EXPECT_EQ(list->list_size, 5);
    // check each item value
    test_iter = list->head;
    test_ints_count = 0;
    while(test_iter){
        EXPECT_EQ(*(int*)test_iter->item, test_ints_4[test_ints_count]);
        test_iter = test_iter->next;
        test_ints_count++;
    }

    Clear();
}

// function: list_pop_front
TEST_F(ListTest, PopFrontTest){
    int val = 22;
    void* item;

    //empty
    item = list_pop_front(list);
    EXPECT_EQ(item, nullptr);

    // Remove when it has only one item
    list_prepend(list, &val);
    item = list_pop_front(list);
    IsEmpty();
    EXPECT_EQ(*(int*)item, val);

    // Remove when several items
    FillList(list_append);
    item = list_pop_front(list);
    EXPECT_EQ(*(int*)item, 9);
    IsNotEmpty();
    EXPECT_EQ(list->list_size, 9);

    Clear();
}

// function: list_pop_back
TEST_F(ListTest, PopBackTest) {
    int val = 22;
    void* item;

    // empty
    item = list_pop_front(list);
    EXPECT_EQ(item, nullptr);

    // Pop when it has only one item    
    list_append(list, &val);
    item = list_pop_back(list);
    IsEmpty();
    EXPECT_EQ(*(int*)item, val);

    // Pop when several items
    FillList(list_append);

    item = list_pop_back(list);
    EXPECT_EQ(*(int*)item, 1);
    IsNotEmpty();
    EXPECT_EQ(list->list_size, 9);

    Clear();
}

TEST_F(ListTest, AtTest) {
    void* item;

    // empty list
    item = list_at(list, 0);
    EXPECT_EQ(item, nullptr);
    IsEmpty();

    // prepare values
    FillList(list_append);

    // try to get value by valid index
    // scan all values
    for(int i = 0; i < 10; i++) {
        item = list_at(list, i);
        EXPECT_NE(item, nullptr);
        EXPECT_EQ(*(int*)item, testValues[i]);
        IsNotEmpty();
    }

    // try to get value by invalid index
    // scan 10 invalid indexes
    for(int i = 10; i < 20; i++){
        item = list_at(list, i);
        EXPECT_EQ(item, nullptr);
        IsNotEmpty();
    }

    Clear();
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}