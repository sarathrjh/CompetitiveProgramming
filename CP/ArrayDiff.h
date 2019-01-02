
#include <map>
#include <vector>

struct Pair
{
	int nSmall;
	int nLarge;

	Pair() : nSmall(-1), nLarge(-1)
	{}
};

class QueueUsingStack
{
public:
	QueueUsingStack()
	{
		m_nLength = -1;
	}

	void insertToQueue(int nData)
	{
		if (m_nLength == 256)
		{
			printf("Queue is full \n");
			return;
		}

		m_nStack[++m_nLength] = nData;
	}

	int recurDequeue()
	{
		if (m_nLength == -1)
		{
			printf("Queue is empty\n");
			return -1;
		}

		if (m_nLength == 0)
		{
			return m_nStack[m_nLength--];
		}

		int curVal = m_nStack[m_nLength--];
		int res = recurDequeue();
		m_nStack[++m_nLength] = curVal;
		return res;
	}
private:
	int m_nLength;
	int m_nStack[256];
};


class Stock
{
public:

	int maxDiff(int arr[], int n)
	{
		// Create a diff array of size n-1. The array will hold
		//  the difference of adjacent elements
		int *diff = new int[n - 1];
		for (int i = 0; i < n - 1; i++)
			diff[i] = arr[i + 1] - arr[i];

		// Now find the maximum sum subarray in diff array
		int max_diff = diff[0];
		for (int i = 1; i<n - 1; i++)
		{
			if (diff[i - 1] > 0)
				diff[i] += diff[i - 1];
			if (max_diff < diff[i])
				max_diff = diff[i];
		}
		return max_diff;
	}

	std::map<int, Pair> getMaxProfit(int stockArray[], int nLength)
	{
		Pair stkPair;
		std::map<int, Pair> StockPair;
		int nBuyIndex = 0;
		int nSellIndex = 0;
		int nMinIndex = 0;
		int nProfit = 0;

		for (int nIndex = 0; nIndex < nLength; nIndex++)
		{
			if (stockArray[nIndex] < stockArray[nMinIndex])
			{
				nMinIndex = nIndex;
			}
			else if ((stockArray[nIndex] - stockArray[nMinIndex]) > nProfit)
			{
				nBuyIndex = nMinIndex;
				nSellIndex = nIndex;
				nProfit = stockArray[nIndex] - stockArray[nMinIndex];
			}
		}
		stkPair.nSmall = nBuyIndex;
		stkPair.nLarge = nSellIndex;
		StockPair[nProfit] = stkPair;
		return StockPair;
	}

	/*Input: [3,3,5,0,0,3,1,4]
	Output: 6
	algorithm to find the maximum profit. You may complete at most two transactions.
	Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.*/

	int findMaxProfitWithAtMost2Transaction(int stockPrices[], int size)
	{
		if (size < 2)
		{
			return 0;
		}
		std::vector<int> leftStock(size, 0);
		int minVal = stockPrices[0];
		for (int Index = 1; Index < size; Index++)
		{
			minVal = min(minVal, stockPrices[Index]);
			leftStock[Index] = max(leftStock[Index - 1], (stockPrices[Index] - minVal));
		}

		int temp = 0;
		int maxVal = stockPrices[size - 1];
		int profit = max(temp, leftStock[size - 1]);
		for (int Index = size - 2; Index >= 0; Index--)
		{
			maxVal = max(maxVal, stockPrices[Index]);
			temp = max(temp, (maxVal - stockPrices[Index]));
			profit = max(profit, (temp + leftStock[Index]));
		}

		return profit;
	}

	int maxDiff_opt(int arr[], int n)
	{
		// Initialize diff, current sum and max sum
		int diff = -1;// arr[1] - arr[0];
		int curr_sum = diff;
		int max_sum = curr_sum;

		for (int i = 0; i < n - 1; i++)
		{
			// Calculate current diff
			diff = arr[i + 1] - arr[i];

			// Calculate current sum
			if (curr_sum > 0)
				curr_sum += diff;
			else
				curr_sum = diff;

			// Update max sum, if needed
			if (curr_sum > max_sum)
			{
				max_sum = curr_sum;
			}
		}
		return max_sum;
	}

	std::vector<int> findIntersection(int Array1[], int Array2[], int nSize1, int nSize2)
	{
		std::vector<int> intersectionVector;
		if (nSize1 > 0 && nSize2 > 0)
		{
			std::map<int, int> FirstArray;

			for (int nIndex = 0; nIndex < nSize1; nIndex++)
			{
				FirstArray[Array1[nIndex]] = Array1[nIndex];
			}

			for (int nIndex2 = 0; nIndex2 < nSize2; nIndex2++)
			{
				if ((FirstArray.find(Array2[nIndex2]) != FirstArray.end()) &&
					(std::find(intersectionVector.begin(), intersectionVector.end(), Array2[nIndex2]) == intersectionVector.end()))
				{
					intersectionVector.push_back(Array2[nIndex2]);
				}
			}
		}
		return intersectionVector;
	}

	std::vector<int> findArrayIntersection(int Array1[], int Array2[], int nSize1, int nSize2)
	{
		std::vector<int> intersectionVector;
		if (nSize1 > 0 && nSize2 > 0)
		{
			int nArray1Index = 0;
			int nArray2Index = 0;
			while (nArray1Index < nSize1 && nArray2Index < nSize2)
			{
				if (Array1[nArray1Index] == Array2[nArray2Index])
				{
					intersectionVector.push_back(Array1[nArray1Index]);
					++nArray1Index;
					++nArray2Index;
				}
				else if (Array1[nArray1Index] < Array2[nArray2Index])
				{
					++nArray1Index;
				}
				else
				{
					++nArray2Index;
				}
			}
		}
		return intersectionVector;
	}
};
