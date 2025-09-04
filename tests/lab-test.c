#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"


void setUp(void) {
  printf("Setting up tests...\n");
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

void test_list_basic(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_TRUE(list_is_empty(list));
    TEST_ASSERT_EQUAL(0, list_size(list));

    int *val1 = malloc(sizeof(int));
    int *val2 = malloc(sizeof(int));
    *val1 = 42;
    *val2 = 99;

    TEST_ASSERT_TRUE(list_append(list, val1));
    TEST_ASSERT_FALSE(list_is_empty(list));
    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL_PTR(val1, list_get(list, 0));

    TEST_ASSERT_TRUE(list_insert(list, 0, val2));
    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL_PTR(val2, list_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(val1, list_get(list, 1));

    int *removed = list_remove(list, 0);
    TEST_ASSERT_EQUAL_PTR(val2, removed);
    free(removed);
    TEST_ASSERT_EQUAL(1, list_size(list));

    list_destroy(list, free);
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_list_basic);
  return UNITY_END();
}
