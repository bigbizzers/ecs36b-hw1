#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    }


auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> result;

    for (size_t i = 0; i < numbers.size(); ++i) {
        result.push_back(std::to_string(numbers[i]));
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    char* argv[] = {(char*)"SortInts", (char*)"25", (char*)"83", (char*)"17"};
    int argc = 4;

    int* arr = NULL;
    int len = 0;

    parse_args(argc, argv, &arr, &len);

    EXPECT_EQ(len, 3);
    EXPECT_EQ(arr[0], 25);
    EXPECT_EQ(arr[1], 83);
    EXPECT_EQ(arr[2], 17);

    free(arr);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    char* argv[] = {(char*)"SortInts"};
    int argc = 1;

    int* arr = NULL;
    int len = 0;

    parse_args(argc, argv, &arr, &len);

    EXPECT_EQ(len, 0);
    EXPECT_EQ(arr, nullptr);

}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              (const std::vector<int>& numbers)
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    RC_PRE(numbers.size() > 0u);

    std::vector<std::string> arg_strings;
    arg_strings.push_back("prog");

    std::vector<std::string> number_strings =
        vector_of_ints_to_vector_of_strings(numbers);

    for (size_t i = 0; i < number_strings.size(); ++i) {
        arg_strings.push_back(number_strings[i]);
    }
    std::vector<char*> argv;
    for (size_t i = 0; i < arg_strings.size(); ++i) {
        argv.push_back(&arg_strings[i][0]);
    }
    int* arr = NULL;
    int len = 0;

    parse_args((int)argv.size(), argv.data(), &arr, &len);

    RC_ASSERT(len == (int)numbers.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(numbers, arr));

    free(arr);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    char* argv[] = {(char*)"prog"};

    int* arr = NULL;
    int len = 0;

    parse_args(1, argv, &arr, &len);

    RC_ASSERT(len == 0);
    RC_ASSERT(arr == nullptr);
}
