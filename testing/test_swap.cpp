#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int x = 12;
    int y = 13;

    swap(&x, &y);

    EXPECT_EQ(x, 13);
    EXPECT_EQ(y, 12);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int arr[] = {10, 20, 30, 40};
    swap(&arr[1], &arr[3]);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 20);

}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    (void)a_start;
    (void)b_start;
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    (void)values;
}
