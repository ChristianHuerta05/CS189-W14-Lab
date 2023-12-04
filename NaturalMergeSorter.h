#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H
#include <iostream>
#include <vector>
class NaturalMergeSorter
{
public:
    virtual int GetSortedRunLength(int *array, int arrayLength, int startIndex)
    {
        if (startIndex >= arrayLength)
        {
            return 0;
        }

        int counter = 0;
        for (int i = startIndex; i < arrayLength; ++i)
        {

            if (i != startIndex && i != arrayLength)
            {

                if (array[i - 1] <= array[i])
                {
                    counter++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                counter++;
            }
        }

        return counter;
    }

    virtual void NaturalMergeSort(int *array, int arrayLength)
    {
        int i = 0;

        while (i < arrayLength)
        {
            int run1 = GetSortedRunLength(array, arrayLength, i);
            if (run1 == arrayLength)
            {
                return;
            }

            i += run1;

            if (i == arrayLength)
            {
                i = 0;
                continue;
            }

            int run2 = GetSortedRunLength(array, arrayLength, i);
            Merge(array, i - run1, i - 1, i + run2 - 1);

            i += run2;
            if (i == arrayLength)
            {
                i = 0;
            }
        }
    }

    virtual void Merge(int *numbers, int leftFirst, int leftLast,
                       int rightLast)
    {
        int mergedSize = rightLast - leftFirst + 1;
        int *mergedNumbers = new int[mergedSize];
        int mergePos = 0;
        int leftPos = leftFirst;
        int rightPos = leftLast + 1;

        while (leftPos <= leftLast && rightPos <= rightLast)
        {
            if (numbers[leftPos] <= numbers[rightPos])
            {
                mergedNumbers[mergePos] = numbers[leftPos];
                leftPos++;
            }
            else
            {
                mergedNumbers[mergePos] = numbers[rightPos];
                rightPos++;
            }
            mergePos++;
        }

        // If left partition isn't empty, add remaining elements to mergedNumbers
        while (leftPos <= leftLast)
        {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
            mergePos++;
        }

        // If right partition isn't empty, add remaining elements to mergedNumbers
        while (rightPos <= rightLast)
        {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
            mergePos++;
        }

        // Copy merged numbers back to numbers
        for (mergePos = 0; mergePos < mergedSize; mergePos++)
        {
            numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
        }

        // Free temporary array
        delete[] mergedNumbers;
    }
};

#endif