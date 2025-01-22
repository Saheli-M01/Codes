def merge(array, start, end):
    middle = (start + end) // 2

    leftSize = middle - start + 1
    rightSize = end - middle

    leftArray = array[start:middle + 1]
    rightArray = array[middle + 1:end + 1]

    leftIndex = rightIndex = 0
    currentIndex = start

    while leftIndex < leftSize and rightIndex < rightSize:
        if leftArray[leftIndex] < rightArray[rightIndex]:
            array[currentIndex] = leftArray[leftIndex]
            leftIndex += 1
        else:
            array[currentIndex] = rightArray[rightIndex]
            rightIndex += 1
        currentIndex += 1

    while leftIndex < leftSize:
        array[currentIndex] = leftArray[leftIndex]
        leftIndex += 1
        currentIndex += 1

    while rightIndex < rightSize:
        array[currentIndex] = rightArray[rightIndex]
        rightIndex += 1
        currentIndex += 1


def mergeSort(array, start, end):
    if start >= end:
        return

    middle = (start + end) // 2
    mergeSort(array, start, middle)
    mergeSort(array, middle + 1, end)
    merge(array, start, end)


if __name__ == "__main__":
    numbers = [3, 7, 0, 1, 5, 8, 3, 2, 34, 66, 87, 23, 12, 12, 12]
    size = len(numbers)
    mergeSort(numbers, 0, size - 1)
    print(numbers)
