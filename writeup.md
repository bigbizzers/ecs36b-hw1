# Google Test And Debugging Writeup

## Things I Thought To Test
1. For `swap`, I tested using swap on two different numbers, with the expectation that both of those numbers would be swapped (i.e., their order changed).

2. For `copy_array`, I tested whether a new array created by calling `copy_array` contained the same elements as its input, and if modifying one of these arrays would modify the other.

3. For `min_index_of_array`, I tested it when the smallest number is located at the first index of the array, and when it is found at some later position in the array.

4. For `make_sorted`, I wanted to see how it performs when creating a sorted version from an initially unsorted array and then when creating a sorted version from an array that is already sorted.

5. For `get_sorted`, I wanted to confirm that it returns an ordered array while leaving unchanged the initial array passed into `get_sorted`.

6. For `parse_args`, I wanted to verify that it correctly parses ordinary integers for `args` but will fail when called with no `args`.
...

## Bugs

### Bug 1

### Location

Lines 63-73

```c++
void swap(int* a, int* b) {
    int* temp = a;
    a = b;
    b = temp;
}
```

### How the bug was located

This bug was discovered when I ran my simple swap tests on the file test_swap.cpp. When I wrote a swap test where two values were being swapped using an object’s swap method, it failed because the values being swapped didn’t change after calling swap.

### Description

In its current form the function is simply swapping the local pointers a and b rather than swapping the actual integer values contained in memory at those locations that a and b are pointing to. Therefore nothing has been altered from within the caller.

### Fix 

To repair this problem I made the necessary changes to the code so as to make sure it swaps the values that each of the pointers are pointing to (i.e., *a and *b) as opposed to merely switching what each of the local pointers a and b are pointing to.

```c++
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

### Bug 2

### Location

Lines 44-61

```c++
int min_index_of_array(int* ar, int len) {
    int min_index = 0;

    for (int i = 1; i < len; ++i) {
        if (ar[i] > ar[min_index]) {
            min_index = i;
        }
    }
    return ar[min_index];
}
```

### How the bug was located

The bug was discovered by running all the min_index_of_array tests in test_min_index_of_array.cpp. One of those tests has an array with the first element being the smallest. It didn't pass; therefore we knew that min_index wasn't working as expected.

### Description

There were two problems with this method. First, it uses > (greater than) as opposed to < (less than), so it's always going to find the max rather than the min. Secondly, it returns ar[min_index] which is the actual number at the min_index position versus simply the index itself.

### Fix

To fix both of these issues I updated the code to check each time through if ar[index] is less than ar[previousMinIndex]. If it is then previousMinIndex = index. Then when finished looping I returned min_index as opposed to ar[min_index];

```c++
int min_index_of_array(int* ar, int len) {
    int min_index = 0;

    for (int i = 1; i < len; ++i) {
        if (ar[i] < ar[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}
```

### Bug 3

### Location


 Lines 4-14
```c++
int* get_sorted(int* ar, int len) {
    int* sorted_ar = copy_array(ar, len);
    make_sorted(ar, len);
    return sorted_ar;
}
```

### How the bug was located

I came across this bug when creating the get_sorted tests and running them in the test_get_sorted.cpp file. The primary failing tests were those testing reverse sort and that the original array was left intact. The test for reverse sort failed as it did not return a reversed sorted version; the test that checked if the original array had been changed passed due to the fact that the returned version was just as messed up as the original.

### Description

The method was successful at making a copy of the data entered into it. However, after that it took the source array (ar) and sorted it versus taking a copy of it (sorted_ar) and sorting that. So although the method returned a new copy of the data which was incorrect, it also destroyed the source array.

### Fix

To fix the bug, I altered the line of code from "sort(ar);" to "sort(sorted_ar);" to ensure that the source is preserved.

```c++
int* get_sorted(int* ar, int len) {
    int* sorted_ar = copy_array(ar, len);
    make_sorted(sorted_ar, len);
    return sorted_ar;
}
```