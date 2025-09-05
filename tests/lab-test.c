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


void test_list_null_and_bounds(void) {
    // Test NULL list handling
    TEST_ASSERT_FALSE(list_append(NULL, NULL));
    TEST_ASSERT_FALSE(list_insert(NULL, 0, NULL));
    TEST_ASSERT_NULL(list_remove(NULL, 0));
    TEST_ASSERT_NULL(list_get(NULL, 0));
    TEST_ASSERT_EQUAL(0, list_size(NULL));
    TEST_ASSERT_FALSE(list_is_empty(NULL));

    // Create a list and test out-of-bounds
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);

    int *val = malloc(sizeof(int));
    *val = 123;
    TEST_ASSERT_TRUE(list_append(list, val));
    TEST_ASSERT_NULL(list_get(list, 1));
    TEST_ASSERT_FALSE(list_insert(list, 2, val));
    TEST_ASSERT_NULL(list_remove(list, 2));

    list_destroy(list, free);
}

void test_list_insert_remove_get(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    *a = 1; *b = 2; *c = 3;

    // Insert at index 0 (should fail, list is empty)
    TEST_ASSERT_FALSE(list_insert(list, 1, a));
    TEST_ASSERT_TRUE(list_append(list, a));
    TEST_ASSERT_TRUE(list_insert(list, 0, b)); // Insert at front
    TEST_ASSERT_TRUE(list_insert(list, 1, c)); // Insert in middle

    TEST_ASSERT_EQUAL_PTR(b, list_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(c, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(a, list_get(list, 2));

    // Remove from middle
    int *removed = list_remove(list, 1);
    TEST_ASSERT_EQUAL_PTR(c, removed);
    free(removed);

    // Remove from front
    removed = list_remove(list, 0);
    TEST_ASSERT_EQUAL_PTR(b, removed);
    free(removed);

    // Remove last
    removed = list_remove(list, 0);
    TEST_ASSERT_EQUAL_PTR(a, removed);
    free(removed);

    TEST_ASSERT_TRUE(list_is_empty(list));
    list_destroy(list, NULL);
}

void test_list_destroy_free_func(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);

    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    *x = 10; *y = 20;

    TEST_ASSERT_TRUE(list_append(list, x));
    TEST_ASSERT_TRUE(list_append(list, y));

    // Destroy with free_func
    list_destroy(list, free);
}


int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_list_basic);
  RUN_TEST(test_list_null_and_bounds);
  RUN_TEST(test_list_insert_remove_get);
  RUN_TEST(test_list_destroy_free_func);
  return UNITY_END();
}
