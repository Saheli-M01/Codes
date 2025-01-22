function merge(array, start, end) {
    const middle = Math.floor((start + end) / 2);

    const leftSize = middle - start + 1;
    const rightSize = end - middle;

    const leftArray = array.slice(start, middle + 1);
    const rightArray = array.slice(middle + 1, end + 1);

    let leftIndex = 0, rightIndex = 0;
    let currentIndex = start;

    // Merge the two sorted subarrays
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

function mergeSort(array, start, end) {
    if (start >= end) {
        return;
    }

    const middle = Math.floor((start + end) / 2);

    // Sort the left part
    mergeSort(array, start, middle);

    // Sort the right part
    mergeSort(array, middle + 1, end);

    // Merge the two sorted parts
    merge(array, start, end);
}

// Main execution
const numbers = [3, 7, 0, 1, 5, 8, 3, 2, 34, 66, 87, 23, 12, 12, 12];
const size = numbers.length;

mergeSort(numbers, 0, size - 1);

console.log(numbers);
