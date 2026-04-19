#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*

     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1, 2, 3};
    int* copy = copy_array(arr, 3);

    EXPECT_EQ(copy[0], arr[0]);
    EXPECT_EQ(copy[1], arr[1]);
    EXPECT_EQ(copy[2], arr[2]);

    free(copy);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {4, 5, 6};
    int* copy = copy_array(arr, 3);

    copy[0] = 100;

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 5);
    EXPECT_EQ(arr[2], 6);

    free(copy);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1, 2, 3};
    int* copy = copy_array(arr, 3);

    EXPECT_NE(copy, arr);

    free(copy);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(values.size() > 0u);

    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* copy = copy_array(arr, values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(copy[i] == arr[i]);
    }
    free(arr);
    free(copy);
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(values.size() > 0u);

    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* original = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, original);

    int* copy = copy_array(arr, values.size());

    for (size_t i = 0; i < values.size(); ++i) {
        RC_ASSERT(arr[i] == original[i]);
    }
    free(arr);
    free(original);
    free(copy);


}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    RC_PRE(values.size() > 0u);

    int* arr = (int*)malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, arr);

    int* copy = copy_array(arr, values.size());

    RC_ASSERT(copy != arr);

    free(arr);
    free(copy);
}



