#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// Comparison function for qsort
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Backtracking function to generate subsets
void backtrack(int* nums, int numsSize, int** result, int* colSizes, int* returnSize, int* temp, int start, int depth) {
    result[*returnSize] = (int*)malloc(depth * sizeof(int));
    memcpy(result[*returnSize], temp, depth * sizeof(int));
    colSizes[*returnSize] = depth;
    (*returnSize)++;

    for (int i = start; i < numsSize; i++) {
        if (i > start && nums[i] == nums[i - 1]) continue; // Skip duplicates
        temp[depth] = nums[i];
        backtrack(nums, numsSize, result, colSizes, returnSize, temp, i + 1, depth + 1);
    }
}

// Main function to generate subsets with duplicates
int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int maxSets = 1 << numsSize; // Maximum possible subsets
    int** result = (int**)malloc(maxSets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxSets * sizeof(int));
    *returnSize = 0;

    int* temp = (int*)malloc(numsSize * sizeof(int));
    qsort(nums, numsSize, sizeof(int), cmp); // Sort the array to handle duplicates

    backtrack(nums, numsSize, result, *returnColumnSizes, returnSize, temp, 0, 0);
    free(temp);
    return result;
}

// Helper function to print the result
void printResult(int** result, int returnSize, int* returnColumnSizes) {
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j + 1 < returnColumnSizes[i]) printf(",");
        }
        printf("]");
        if (i + 1 < returnSize) printf(",");
    }
    printf("]\n");
}

// Main function to test the subsetsWithDup function
int main() {
    // Example 1
    int nums1[] = {1, 2, 2};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int returnSize1;
    int* returnColumnSizes1;
    printf("Input: nums = [1,2,2]\n");
    int** result1 = subsetsWithDup(nums1, numsSize1, &returnSize1, &returnColumnSizes1);
    printf("Output: ");
    printResult(result1, returnSize1, returnColumnSizes1);

    // Free allocated memory for Example 1
    for (int i = 0; i < returnSize1; i++) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes1);

    // Example 2
    int nums2[] = {0};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int returnSize2;
    int* returnColumnSizes2;
    printf("Input: nums = [0]\n");
    int** result2 = subsetsWithDup(nums2, numsSize2, &returnSize2, &returnColumnSizes2);
    printf("Output: ");
    printResult(result2, returnSize2, returnColumnSizes2);

    // Free allocated memory for Example 2
    for (int i = 0; i < returnSize2; i++) {
        free(result2[i]);
    }
    free(result2);
    free(returnColumnSizes2);

    return 0;
}
