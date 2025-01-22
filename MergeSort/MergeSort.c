#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int start, int end) {
    int middle = (start + end) / 2;

    int leftSize = middle - start + 1;
    int rightSize = end - middle;

    int *leftArray = (int *)malloc(leftSize * sizeof(int));
    int *rightArray = (int *)malloc(rightSize * sizeof(int));

    // Copy values to the left subarray
    int currentIndex = start;
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = array[currentIndex++];
    }

    // Copy values to the right subarray
    currentIndex = middle + 1;
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = array[currentIndex++];
    }

    // Merge the two sorted subarrays
    int leftIndex = 0, rightIndex = 0;
    currentIndex = start;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] < rightArray[rightIndex]) {
            array[currentIndex++] = leftArray[leftIndex++];
        } else {
            array[currentIndex++] = rightArray[rightIndex++];
        }
    }

    // Copy any remaining elements from the left subarray
    while (leftIndex < leftSize) {
        array[currentIndex++] = leftArray[leftIndex++];
    }

    // Copy any remaining elements from the right subarray
    while (rightIndex < rightSize) {
        array[currentIndex++] = rightArray[rightIndex++];
    }

    // Free dynamically allocated memory
    free(leftArray);
    free(rightArray);
}

void mergeSort(int *array, int start, int end) {
    if (start >= end) {
        return;
    }

    int middle = (start + end) / 2;

    // Sort the left part
    mergeSort(array, start, middle);

    // Sort the right part
    mergeSort(array, middle + 1, end);

    // Merge the two sorted parts
    merge(array, start, end);
}

int main() {
    int numbers[] = {3, 7, 0, 1, 5, 8, 3, 2, 34, 66, 87, 23, 12, 12, 12};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    mergeSort(numbers, 0, size - 1);

    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
