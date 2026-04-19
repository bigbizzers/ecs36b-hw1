#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1, 2, 3};
    int* sorted = get_sorted(arr, 3);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);

    free(sorted);

}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {3, 2, 1};
    int* sorted = get_sorted(arr, 3);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);

    free(sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {3, 1, 2};
    int* sorted = get_sorted(arr, 3);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);

    free(sorted);

}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {3, 1, 3, 2};
    int* sorted = get_sorted(arr, 4);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);
    EXPECT_EQ(sorted[3], 3);

    free(sorted);

}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {3, 1, 2};
    int* sorted = get_sorted(arr, 3);

    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 2);

    free(sorted);

}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {3, 1, 2};
    int* sorted = get_sorted(arr, 3);

    EXPECT_NE(sorted, arr);
    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);

    free(sorted);

}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* sorted = get_sorted(arr, values.size());

    for (size_t i = 0; i + 1 < values.size(); i++ ) {
        RC_ASSERT(sorted[i] <= sorted[i+1]);
    }
    free(arr);
    free(sorted);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* original_arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, original_arr);

    int* sorted = get_sorted(arr, values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(arr[i] == original_arr[i]);
    }
    free(arr);
    free(original_arr);
    free(sorted);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */


        int* arr = (int*)malloc(sizeof(int) * values.size());
        copy_vector_to_array(values, arr);

        int* sorted = get_sorted(arr, values.size());

        RC_ASSERT(sorted != arr);

        free(arr);
        free(sorted);
}











