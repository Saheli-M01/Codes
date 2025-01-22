import java.util.Arrays;

public class MergeSort {

    public static void merge(int[] array, int start, int end) {
        int middle = (start + end) / 2;

        int leftSize = middle - start + 1;
        int rightSize = end - middle;

        int[] leftArray = new int[leftSize];
        int[] rightArray = new int[rightSize];

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
    }

    public static void mergeSort(int[] array, int start, int end) {
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

    public static void main(String[] args) {
        int[] numbers = {3, 7, 0, 1, 5, 8, 3, 2, 34, 66, 87, 23, 12, 12, 12};
        int size = numbers.length;

        mergeSort(numbers, 0, size - 1);

        System.out.println(Arrays.toString(numbers));
    }
}
