#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int arr[] = {1, 2, 3};

    int min = min_index_of_array(arr, 3);

    EXPECT_EQ(min, 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int arr[] = {3, 2, 1};

    int min = min_index_of_array(arr, 3);

    EXPECT_EQ(min, 2);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int arr[] = {3, 1, 2};

    int min = min_index_of_array(arr, 3);

    EXPECT_EQ(min, 1);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int arr[] = {3, 1, 2, 1};

    int min = min_index_of_array(arr, 4);

    EXPECT_EQ(min, 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int arr[] = {3, 1, 2};

    min_index_of_array(arr, 3);

    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              (const std::vector<int>& values)) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    RC_PRE(values.size() > 0u);

    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int min_i = min_index_of_array(arr, values.size());

    RC_ASSERT(min_i >= 0);
    RC_ASSERT((size_t)min_i < values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(arr[min_i] <= arr[i]);
    }
    free(arr);
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              (const std::vector<int>& values)) {

    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    RC_PRE(values.size() > 0u);

    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* original = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, original);

    min_index_of_array(arr, values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(arr[i] == original[i]);
    }
    free(arr);
    free(original);
}
