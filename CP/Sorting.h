#include "stdafx.h"

class Sorting
{

private:
	int m_nHeapSize;

	void swap(int& First, int& Second)
	{
		int nTemp = First;
		First = Second;
		Second = nTemp;
	}

	int getParent(int nIndex)
	{
		return((nIndex - 1) / 2);
	}

	int getLeft(int nIndex)
	{
		return ((2 * nIndex) + 1);
	}

	int getRight(int nIndex)
	{
		return ((2 * nIndex) + 2);
	}

	void minHeapify(int array[], int nSize, int nIndex)
	{
		int nSmallestIndex = nIndex;
		int nLeft = getLeft(nIndex);
		int nRight = getRight(nIndex);
		if ((nLeft < nSize) && (array[nLeft] < array[nSmallestIndex]))
		{
			nSmallestIndex = nLeft;
		}

		if ((nRight < nSize) && (array[nRight] < array[nSmallestIndex]))
		{
			nSmallestIndex = nRight;
		}

		if (nIndex != nSmallestIndex)
		{
			swap(array[nIndex], array[nSmallestIndex]);
			minHeapify(array, nSize, nSmallestIndex);
		}
	}

	void maxHeapify(int array[], int nSize, int nIndex)
	{
		int nLargestIndex = nIndex;
		int nLeft = getLeft(nIndex);
		int nRight = getRight(nIndex);
		if ((nLeft < nSize) && (array[nLeft] > array[nLargestIndex]))
		{
			nLargestIndex = nLeft;
		}

		if ((nRight < nSize) && (array[nRight] > array[nLargestIndex]))
		{
			nLargestIndex = nRight;
		}

		if (nIndex != nLargestIndex)
		{
			swap(array[nIndex], array[nLargestIndex]);
			maxHeapify(array, nSize, nLargestIndex);
		}
	}

	int QuickSortPartition(int array[], int nLow, int nHigh)
	{
		int pivot = array[nHigh];    // pivot
		int nSortedIndex = nLow - 1;  // Index of smaller element

		for (int nIndex = nLow; nIndex <= nHigh - 1; nIndex++)
		{
			// If current element is smaller than or
			// equal to pivot
			if (array[nIndex] <= pivot)
			{
				nSortedIndex++;    // increment index of smaller element
				swap(array[nSortedIndex], array[nIndex]);
			}
		}
		swap(array[nSortedIndex + 1], array[nHigh]);
		return nSortedIndex + 1;
	}

	// A function to merge the two half into a sorted data.
	void Merge(int array[], int nLow, int nHigh, int nMid)
	{
		// We have low to mid and mid+1 to high already sorted.
		int FirstHalfIndex, SecondHalfIndex, newArraySize;
		int* temp = new int[(nHigh - nLow) + 1];
		FirstHalfIndex = nLow;
		newArraySize = 0;
		SecondHalfIndex = nMid + 1;

		// Merge the two parts into temp[].
		while (FirstHalfIndex <= nMid && SecondHalfIndex <= nHigh)
		{
			if (array[FirstHalfIndex] < array[SecondHalfIndex])
			{
				temp[newArraySize] = array[FirstHalfIndex];
				newArraySize++;
				FirstHalfIndex++;
			}
			else
			{
				temp[newArraySize] = array[SecondHalfIndex];
				newArraySize++;
				SecondHalfIndex++;
			}
		}

		// Insert all the remaining values from i to mid into temp[].
		while (FirstHalfIndex <= nMid)
		{
			temp[newArraySize] = array[FirstHalfIndex];
			newArraySize++;
			FirstHalfIndex++;
		}

		// Insert all the remaining values from j to high into temp[].
		while (SecondHalfIndex <= nHigh)
		{
			temp[newArraySize] = array[SecondHalfIndex];
			newArraySize++;
			SecondHalfIndex++;
		}


		// Assign sorted data stored in temp[] to a[].
		for (FirstHalfIndex = nLow; FirstHalfIndex <= nHigh; FirstHalfIndex++)
		{
			array[FirstHalfIndex] = temp[FirstHalfIndex - nLow];
		}

		delete[] temp;
	}

public:

	Sorting()
	{
		m_nHeapSize = 0;
	}

	void quickSort(int array[], int nLow, int nHigh)
	{
		if (nLow < nHigh)
		{
			/* pivotIndex is partitioning index, arr[p] is now
			at right place */
			int pivotIndex = QuickSortPartition(array, nLow, nHigh);

			// Separately sort elements before
			// partition and after partition
			quickSort(array, nLow, pivotIndex - 1);
			quickSort(array, pivotIndex + 1, nHigh);
		}
	}

	// A function to split array into two parts.
	void MergeSort(int array[], int nLow, int nHigh)
	{
		int mid;
		if (nLow < nHigh)
		{
			mid = (nLow + nHigh) / 2;
			// Split the data into two half.
			MergeSort(array, nLow, mid);
			MergeSort(array, mid + 1, nHigh);

			// Merge them to get sorted output.
			Merge(array, nLow, nHigh, mid);
		}
	}

	void HeapSort(int array[], int nSize)
	{
		int nStartIndex = (nSize / 2) - 1;
		while (nStartIndex >= 0)
		{
			maxHeapify(array, nSize, nStartIndex);
			nStartIndex--;
		}

		for (int nIndex = nSize - 1; nIndex >= 0; nIndex--)
		{
			swap(array[0], array[nIndex]);
			maxHeapify(array, nIndex, 0);
		}
	}

	void printArray(int array[], int size)
	{
		for (int nIndex = 0; nIndex < size; nIndex++)
		{
			std::cout << array[nIndex] << std::endl;
		}
		std::cout << std::endl;
	}

};