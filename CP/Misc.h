#include<iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>
#include <set>

using namespace std;

class B
{
public:
	virtual int shift(int n = 2) const
	{
		return n << 2;
	}

	void read() const
	{
		std::cout << "read in base" << std::endl;
	}
};

class D : public B
{
public:
	D(){}
	int shift(int n = 3) const
	{
		return n << 3;
	}
	/*void read() const
	{
		std::cout << "read in derived" << std::endl;
	}*/
};

string commonPrefixUtil(string str1, string str2)
{
	string strPrefix;
	int nLength = str1.length();
	if (nLength > str2.length())
	{
		nLength = str2.length();;
	}

	for (int nIndex = 0; nIndex < nLength; ++nIndex)
	{
		if (str1[nIndex] != str2[nIndex])
		{
			break;
		}
		strPrefix.push_back(str1[nIndex]);
	}
	return strPrefix;
}

// A Divide and Conquer based function to find the
// longest common prefix. This is similar to the
// merge sort technique
//Input: {“geeksforgeeks”, “geeks”, “geek”, “geezer”}
//Output: "gee"
string commonPrefix(vector<string> setOfStrings, int low, int high)
{
	if (low == high)
	{
		return (setOfStrings[low]);
	}

	if (high > low)
	{
		// Same as (low + high)/2, but avoids overflow for
		// large low and high
		int mid = low + (high - low) / 2;

		string str1 = commonPrefix(setOfStrings, low, mid);
		string str2 = commonPrefix(setOfStrings, mid + 1, high);

		return (commonPrefixUtil(str1, str2));
	}
}

string longestCommonPrefix(vector<string> setOfStrings) 
{
	if (setOfStrings.size() == 0)
	{
		return "";
	}
	return commonPrefix(setOfStrings, 0, setOfStrings.size() - 1);
}

/*
Given an array nums of n integers, 
are there elements a, b, c in nums such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
[-1, 0, 1],
[-1, -1, 2]
]
*/
vector<vector<int>> threeSumWithExtraSpace(vector<int>& nums) 
{
	vector<vector<int>> resultSet;
	int nSize = nums.size();
	int nTriplet = 0;
	std::sort(nums.begin(), nums.end());
	for (int nIndex = 0; nIndex < nSize - 1; ++nIndex)
	{
		unordered_set<int> seenSet;
		for (int nInIndex = nIndex + 1; nInIndex < nSize; ++nInIndex)
		{
			nTriplet = -(nums[nIndex] + nums[nInIndex]);
			if (seenSet.end() != seenSet.find(nTriplet))
			{
				vector<int> result;
				result.push_back(nTriplet);
				result.push_back(nums[nIndex]);
				result.push_back(nums[nInIndex]);
				resultSet.push_back(result);
			}
			else
			{
				seenSet.insert(nums[nInIndex]);
			}
		}
	}

	return resultSet;
}

vector<vector<int>> threeSumWithoutExtraSpaceAndAvoidDup(vector<int>& nums)
{
	vector<vector<int>> resultSet;
	std::sort(nums.begin(), nums.end());
	int nSize = nums.size();
	for (int nIndex = 0; nIndex < nSize - 2 && nums[nIndex] <= 0; ++nIndex)
	{
		if (nIndex > 0 && nums[nIndex] == nums[nIndex - 1])
		{
			continue; // avoid duplicates
		}
		int twosum = 0 - nums[nIndex];
		int nLeftIndex = nIndex + 1;
		int nRightIndex = nSize - 1;
		while (nLeftIndex < nRightIndex)
		{
			int sum = nums[nLeftIndex] + nums[nRightIndex];
			if (sum < twosum)
			{
				++nLeftIndex;
			}
			else if (sum > twosum)
			{
				--nRightIndex;
			}
			else 
			{
				vector<int> result;
				result.push_back(nums[nIndex]);
				result.push_back(nums[nLeftIndex]);
				result.push_back(nums[nRightIndex]);
				resultSet.push_back(result);
				++nLeftIndex;
				--nRightIndex;
				while (nLeftIndex < nRightIndex && nums[nLeftIndex] == nums[nLeftIndex - 1])
				{
					++nLeftIndex;  // avoid duplicates
				}
				while (nLeftIndex < nRightIndex && nums[nRightIndex] == nums[nRightIndex + 1])
				{
					--nRightIndex;  // avoid duplicates
				}
			}
		}
	}
	return resultSet;
}

/*
Given an array nums of n integers and an integer target, 
find three integers in nums such that the sum is closest to target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.
Given array nums = [-1, 2, 1, -4], and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
int threeSumClosest(vector<int>& nums, int target) 
{
	int nClosetSum = 0;
	int nMin = INT_MAX;
	std::sort(nums.begin(), nums.end());
	int nSize = nums.size();
	int nLeftIndex = 0;
	int nRightIndex = nSize - 1;
	int nDifference = 0;
	int nSum = 0;

	for (int nIndex = 0; nIndex < nSize - 2; ++nIndex)
	{
		nLeftIndex = nIndex + 1;
		nRightIndex = nSize - 1;
		while (nLeftIndex < nRightIndex)
		{
			nSum = nums[nIndex] + nums[nLeftIndex] + nums[nRightIndex];
			nDifference = abs(nSum - target);

			if (nDifference == 0)
			{
				return nSum;
			}
			if (nDifference < nMin)
			{
				nMin = nDifference;
				nClosetSum = nSum;
			}
			if (nSum <= target)
			{
				nLeftIndex++;
			}
			else
			{
				nRightIndex--;
			}
		}
	}
	return nClosetSum;
}

/*
Given a string and number of rows ‘n’.
Print the string formed by concatenating n rows when input string is written in row-wise Zig-Zag fashion.
Input: str = "ABCDEFGH"
n = 2
Output: "ACEGBDFH"
Explanation: Let us write input string in Zig-Zag fashion
in 2 rows.
A   C   E   G
B   D   F   H
Now concatenate the two rows and ignore spaces
in every row. We get "ACEGBDFH"

Input: str = "GEEKSFORGEEKS"
n = 3
Output: GSGSEKFREKEOE
Explanation: Let us write input string in Zig-Zag fashion
in 3 rows.
G       S       G       S
E   K   F   R   E   K
E       O       E
Now concatenate the two rows and ignore spaces
in every row. We get "GSGSEKFREKEOE"
*/
string printZigZagConcat(string str, int nRows)
{	
	if (nRows == 1)
	{
		return str;
	}

	int strLength = str.length();
	vector<string> strResult(nRows);

	int row = 0;
	bool down = true;
	for (int nIndex = 0; nIndex < strLength; ++nIndex)
	{
		strResult[row].push_back(str[nIndex]);

		if (row == nRows - 1)
		{
			down = false;
		}
		else if (row == 0)
		{
			down = true;
		}

		// If direction is down, increment, else decrement
		(down) ? (row++) : (row--);
	}

	str.clear();
	for (auto strRes : strResult)
	{
		str += strRes;
	}

	return str;
}

string getLetters(char digit)
{
	switch (digit)
	{
		case '2':
		{
			return "abc";
		}
		case '3':
		{
			return "def";
		}
		case '4':
		{
			return "ghi";
		}
		case '5':
		{
			return "jkl";
		}
		case '6':
		{
			return "mno";
		}
		case '7':
		{
			return "pqrs";
		}
		case '8':
		{
			return "tuv";
		}
		case '9':
		{
			return "wxyz";
		}
		default:
		{
			return "";
		}
	}
}

void combineLetters(string digits, vector<string>& outCombinations, int nCurrDigit, string& strEachComb)
{
	if (nCurrDigit == digits.length())
	{
		outCombinations.push_back(strEachComb);
		return;
	}

	for (int nIndex = 0; nIndex < getLetters(digits[nCurrDigit]).length(); nIndex++)
	{
		strEachComb[nCurrDigit] = getLetters(digits[nCurrDigit])[nIndex];
		combineLetters(digits, outCombinations, nCurrDigit + 1, strEachComb);
	}
}

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/
vector<string> letterCombinations(string digits) 
{
	string strComb;
	vector<string> outCombinations;
	if (digits.length() > 0)
	{
		strComb.resize(digits.length());
		combineLetters(digits, outCombinations, 0, strComb);
	}
	return outCombinations;
}

/*
Given an array nums of n integers and an integer target,
are there elements a, b, c, and d in nums such that a + b + c + d = target? 
Find all unique quadruplets in the array which gives the sum of target.
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
[-1,  0, 0, 1],
[-2, -1, 1, 2],
[-2,  0, 0, 2]
]
*/
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
	vector<vector<int>> resultSet;
	std::sort(nums.begin(), nums.end());
	int nSize = nums.size();
	for (int nOutIndex = 0; nOutIndex < nSize - 3; ++nOutIndex)
	{
		if (nOutIndex > 0 && nums[nOutIndex] == nums[nOutIndex - 1])
		{
			continue; // avoid duplicates
		}
		for (int nIndex = nOutIndex + 1; nIndex < nSize - 2; ++nIndex)
		{
			if (nIndex > nOutIndex + 1 && nums[nIndex] == nums[nIndex - 1])
			{
				continue; // avoid duplicates
			}
			int nLeftIndex = nIndex + 1;
			int nRightIndex = nSize - 1;
			while (nLeftIndex < nRightIndex)
			{
				int sum = nums[nOutIndex]+ nums[nIndex] + nums[nLeftIndex] + nums[nRightIndex];
				if (sum < target)
				{
					++nLeftIndex;
				}
				else if (sum > target)
				{
					--nRightIndex;
				}
				else
				{
					vector<int> result;
					result.push_back(nums[nOutIndex]);
					result.push_back(nums[nIndex]);
					result.push_back(nums[nLeftIndex]);
					result.push_back(nums[nRightIndex]);
					resultSet.push_back(result);
					++nLeftIndex;
					--nRightIndex;
					while (nLeftIndex < nRightIndex && nums[nLeftIndex] == nums[nLeftIndex - 1])
					{
						++nLeftIndex;  // avoid duplicates
					}
					while (nLeftIndex < nRightIndex && nums[nRightIndex] == nums[nRightIndex + 1])
					{
						--nRightIndex;  // avoid duplicates
					}
				}
			}
		}
	}
	return resultSet;
}

/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Input: "()"
Output: true

Input: "()[]{}"
Output: true

Input: "(]"
Output: false
*/
bool isValid(string s)
{
	if (s.empty())
	{
		return true;
	}

	stack<char> bracStack;
	int nLength = s.length();
	if (nLength == 1)
	{
		return false;
	}
	for (int nIndex = 0; nIndex < nLength; ++nIndex)
	{
		if (s[nIndex] == '(' || s[nIndex] == '[' || s[nIndex] == '{')
		{
			bracStack.push(s[nIndex]);
		}
		else if (s[nIndex] == ')')
		{
			if (!bracStack.empty() && bracStack.top() == '(')
			{
				bracStack.pop();
			}
			else
			{
				return false;
			}
		}
		else if(s[nIndex] == '}')
		{
			if (!bracStack.empty() && bracStack.top() == '{')
			{
				bracStack.pop();
			}
			else
			{
				return false;
			}
		}
		else if (s[nIndex] == ']')
		{
			if (!bracStack.empty() && bracStack.top() == '[')
			{
				bracStack.pop();
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return bracStack.empty();
}

/*
Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Given nums = [1,1,2],
Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.
It doesn't matter what you leave beyond the returned length.

Given nums = [0,0,1,1,1,2,2,3,3,4],
Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.
It doesn't matter what values are set beyond the returned length.
*/
int removeDuplicates(vector<int>& nums) 
{
	int nSize = nums.size();
	if (nSize == 0)
	{
		return 0;
	}
	int nNewIndex = 0;
	for (int nIndex = 1; nIndex < nSize; nIndex++)
	{
		if (nums[nIndex] != nums[nNewIndex])
		{
			nNewIndex++;
			nums[nNewIndex] = nums[nIndex];
		}
	}
	return nNewIndex + 1;
}

/*
Given an array nums and a value val, remove all instances of that value in-place and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example 1:
Given nums = [3,2,2,3], val = 3,
Your function should return length = 2, with the first two elements of nums being 2.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,1,2,2,3,0,4,2], val = 2,
Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
Note that the order of those five elements can be arbitrary.
It doesn't matter what values are set beyond the returned length.
*/
int removeElement(vector<int>& nums, int val)
{
	int nSize = nums.size();
	if (nSize == 0)
	{
		return 0;
	}
	int nNewIndex = 0;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (nums[nIndex] != val)
		{
			nums[nNewIndex] = nums[nIndex];
			nNewIndex++;
		}
	}
	return nNewIndex;
}

/*
Move zeros '0' s to the end of the array in O(n) time.
*/
void moveZeroes(vector<int>& nums)
{
	int nSize = nums.size();
	if (nSize == 0)
	{
		return;
	}
	int nNewIndex = 0;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (nums[nIndex] != 0)
		{
			swap(nums[nIndex], nums[nNewIndex]);
			nNewIndex++;
		}
	}
}


void backtrack(vector<string>& resultParanthesis, string currStr, int open, int close, int max)
{
	if (currStr.length() == max * 2) 
	{
		resultParanthesis.push_back(currStr);
		return;
	}

	if (open < max)
	{
		backtrack(resultParanthesis, currStr + "(", open + 1, close, max);
	}
	if (close < open)
	{
		backtrack(resultParanthesis, currStr + ")", open, close + 1, max);
	}
}

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]
*/
vector<string> generateParenthesis(int n)
{
	vector<string> ans;
	backtrack(ans, "", 0, 0, n);
	return ans;
}

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

Algorithm
Instead of finding every possible string and checking its validity, we can make use of stack while scanning
the given string to check if the string scanned so far is valid, and also the length of the longest valid string.
In order to do so, we start by pushing -1−1 onto the stack.
For every \text{‘(’}‘(’ encountered, we push its index onto the stack.
For every \text{‘)’}‘)’ encountered, we pop the topmost element and subtract the current element's index
from the top element of the stack, which gives the length of the currently encountered valid string of parentheses. 
If while popping the element, the stack becomes empty, we push the current element's index onto the stack.
In this way, we keep on calculating the lengths of the valid substrings, 
and return the length of the longest valid string at the end.
*/
int longestValidParentheses(string s)
{
	int nMaxLength = 0;
	int nLength = s.length();

	std::stack<int> ParanthesisIndexStack;
	ParanthesisIndexStack.push(-1);

	for (int nIndex = 0; nIndex < nLength; nIndex++)
	{
		if (s[nIndex] == '(')
		{
			ParanthesisIndexStack.push(nIndex);
		}
		else
		{
			ParanthesisIndexStack.pop();
			if (!ParanthesisIndexStack.empty())
			{
				nMaxLength = max(nMaxLength, nIndex - ParanthesisIndexStack.top());
			}
			else
			{
				ParanthesisIndexStack.push(nIndex);
			}
		}
	}
	return nMaxLength;
}

/*
Reverse string in O(logn).
*/
string reverseString(string s)
{
	int nLeft = 0;
	int nRight = s.length() - 1;
	while (nLeft < nRight)
	{
		swap(s[nLeft], s[nRight]);
		nLeft++;
		nRight--;
	}
	return s;
}

/*
Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.
Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]
*/
string reverseStr(string s, int k) 
{
	int nLength = s.length();

	for (int nIndex = 0; nIndex < nLength; nIndex += 2 * k)
	{
		int nLeft = nIndex;
		int nRight = min(nIndex + k - 1, nLength - 1);

		while (nLeft < nRight)
		{
			swap(s[nLeft++], s[nRight--]);
		}
	}

	return s;
}

/*
You are given coins of different denominations and a total amount of money. 
Write a function to compute the number of combinations that make up that amount.
You may assume that you have infinite number of each kind of coin.

Note: You can assume that
0 <= amount <= 5000
1 <= coin <= 5000
the number of coins is less than 500
the answer is guaranteed to fit into signed 32-bit integer

Example 1:
Input: amount = 5, coins = [1, 2, 5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

Example 2:
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.

Example 3:
Input: amount = 10, coins = [10]
Output: 1
*/
int findTotalCombinationsOfCoins(int coinArray[], int nSize, int nTotal)
{
	int** coinCombTable = new int*[nSize + 1];
	for (int nRowIndex = 0; nRowIndex < nSize + 1; ++nRowIndex)
	{
		coinCombTable[nRowIndex] = new int[nTotal + 1];
		coinCombTable[nRowIndex][0] = 1;
	}

	for (int nColIndex = 1; nColIndex < nTotal + 1; ++nColIndex)
	{
		coinCombTable[0][nColIndex] = 0;
	}

	for (int nCoinIndex = 1; nCoinIndex < nSize + 1; ++nCoinIndex)
	{
		for (int nTotalIndex = 1; nTotalIndex < nTotal + 1; ++nTotalIndex)
		{
			if (coinArray[nCoinIndex - 1] > nTotalIndex)
			{
				coinCombTable[nCoinIndex][nTotalIndex] = coinCombTable[nCoinIndex - 1][nTotalIndex];
			}
			else
			{
				coinCombTable[nCoinIndex][nTotalIndex] = coinCombTable[nCoinIndex][nTotalIndex - coinArray[nCoinIndex - 1]] + 
														 coinCombTable[nCoinIndex - 1][nTotalIndex];
			}
		}
	}

	return coinCombTable[nSize][nTotal];
}

int findTotalCombinationsOfCoinsOnSpace(int coinArray[], int nSize, int nTotal)
{

	int* coinCombTable = new int[nTotal + 1];
	for (int nIndex = 0; nIndex < nTotal + 1; nIndex++)
	{
		coinCombTable[nIndex] = 0;
	}
	coinCombTable[0] = 1;

	for (int nRowIndex = 0; nRowIndex < nSize; nRowIndex++)
	{
		for (int nColIndex = 1; nColIndex <= nTotal; nColIndex++)
		{
			if (nColIndex >= coinArray[nRowIndex])
			{
				coinCombTable[nColIndex] += coinCombTable[nColIndex - coinArray[nRowIndex]];
			}
		}
	}
	return coinCombTable[nTotal];
}

void printMinCombinations(int denominationArray[], int nTotalSize, int coinArray[])
{
	if (denominationArray[nTotalSize] == -1)
	{
		std::cout <<"No combination for the total " <<nTotalSize <<std::endl;
		return;
	}

	int nDenomIndex = nTotalSize;
	int den = 0;
	while (nDenomIndex != 0)
	{
		den = denominationArray[nDenomIndex];
		std::cout << coinArray[den] << " ";
		nDenomIndex = nDenomIndex - coinArray[den];
	}
	std::cout <<std::endl;
}

/*
You are given coins of different denominations and a total amount of money amount.
Write a function to compute the fewest number of coins that you need to make up that amount. 
If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1
Note:
You may assume that you have an infinite number of each kind of coin.
*/
int findMinCombinationsOfCoins(int coinArray[], int nSize, int nTotal)
{
	int* totalTable = new int[nTotal + 1];
	int* denominationTable = new int[nTotal + 1];
	//std::sort(coinArray, coinArray + nSize);
	for (int nIndex = 0; nIndex < nTotal + 1; ++nIndex)
	{
		totalTable[nIndex] = INT_MAX - 1;
		denominationTable[nIndex] = -1;
	}

	totalTable[0] = 1;

	for (int nCoinIndex = 0; nCoinIndex < nSize; ++nCoinIndex)
	{
		for (int nTotalIndex = 1; nTotalIndex < nTotal + 1; ++nTotalIndex)
		{
			if (nTotalIndex >= coinArray[nCoinIndex])
			{
				if (totalTable[nTotalIndex - coinArray[nCoinIndex]] + 1 < totalTable[nTotalIndex])
				{
					totalTable[nTotalIndex] = totalTable[nTotalIndex - coinArray[nCoinIndex]] + 1;
					denominationTable[nTotalIndex] = nCoinIndex;
				}
			}
		}
	}
	printMinCombinations(denominationTable, nTotal, coinArray);
	return totalTable[nTotal];
}

/*
Given an integer x, find square root of it. If x is not a perfect square, then return floor(√x)
*/

int floorSquareRoot(const int number)
{
	if (number == 0 || number == 1)
	{
		return number;
	}

	int start = 1;
	int mid = 1;
	int end = number / 2; //square root of number cannot be more than number/2 when number > 1.
	int result = 1;

	while (start <= end)
	{
		mid = (start + end) / 2;

		if (mid * mid == number)
		{
			result = mid;
			break;
		}
		else if (mid * mid < number)
		{
			result = mid;
			start = mid + 1;
		}
		else
		{
			end = mid;
		}
	}

	return result;
}

/*
Implement pow(x, n), which calculates x raised to the power n (xn).
*/
float calcPower(float base, int exp)
{
	float temp;
	if (exp == 0)
	{
		return 1;
	}
	temp = calcPower(base, exp / 2);
	if (exp % 2 == 0)
	{
		return temp*temp;
	}
	else
	{
		if (exp > 0)
		{
			return base*temp*temp;
		}
		else
		{
			return (temp*temp) / base;
		}
	}
}

void printPath(int pathArray[], int nSize)
{
	int nPath = nSize - 1;
	while (nPath)
	{
		std::cout << nPath << " ";
		nPath = pathArray[nPath];
	}
	std::cout << nPath <<std::endl;
}

/*
Given an array of integers where each element represents the max number of steps 
that can be made forward from that element. Write a function to return the minimum number
of jumps to reach the end of the array (starting from the first element). 
If an element is 0, then cannot move through that element.

Example:
Input: arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
Output: 3 (1-> 3 -> 8 ->9)
First element is 1, so can only go to 3. Second element is 3, so can make at most 3 steps eg to 5 or 8 or 9.
*/
int findMinJumpReqToReachEnd(int unSortedArray[], int nSize)
{
	int* minJumpArray = new int[nSize];
	std::fill(minJumpArray, minJumpArray + nSize, INT_MAX);
	minJumpArray[0] = 0;
	int* pathArray = new int[nSize];
	std::fill(pathArray, pathArray + nSize, 0);

	for (int nArrayIndex = 1; nArrayIndex < nSize; nArrayIndex++)
	{
		for (int nPathIndex = 0; nPathIndex < nArrayIndex; nPathIndex++)
		{
			if (nArrayIndex <= unSortedArray[nPathIndex] + nPathIndex)
			{
				if (minJumpArray[nPathIndex] + 1 < minJumpArray[nArrayIndex])
				{
					minJumpArray[nArrayIndex] = minJumpArray[nPathIndex] + 1;
					pathArray[nArrayIndex] = nPathIndex;
				}
			}
		}
		if (minJumpArray[nArrayIndex] == INT_MAX)
		{
			return -1;
		}
	}
	printPath(pathArray, nSize);
	return minJumpArray[nSize - 1];
}

int findMinJumpReqToReachEndWithOptimizeTime(int unSortedArray[], int nSize)
{
	//Base cases
	if ((nSize <= 1) || (unSortedArray[0] <= 0))
	{
		return 0;
	}
	int nMaxReach = unSortedArray[0];
	int nSteps = unSortedArray[0];
	int nMinJump = 1;
	std::vector<int> Path = { 0, nMaxReach };
	int nNewIndex = 0;

	for (int nArrayIndex = 1; nArrayIndex < nSize; nArrayIndex++)
	{
		if (nArrayIndex == nSize - 1)
		{
			break;
		}

		nNewIndex = nArrayIndex + unSortedArray[nArrayIndex];
		//Check whether the value in new index is greater than 0.
		//if not decrement the index until it becomes 0.
		while (nNewIndex)
		{
			if (nNewIndex < nSize && (unSortedArray[nNewIndex] > 0))
			{
				break;
			}
			nNewIndex--;
		}

		//Check whether the value in new index was negative and decremented, 
		//still not getting a positive index greater than 0 to move forward.
		if ((nNewIndex <= 0) && nMaxReach <= nArrayIndex)
		{
			return -1;
		}

		nMaxReach = max(nMaxReach, nNewIndex);
		nSteps--;

		if (nSteps == 0)
		{
			nMinJump++;

			// Check if the current index/position or lesser index
			// is the maximum reach point from the previous indexes
			if (nArrayIndex >= nMaxReach)
			{
				return -1;
			}
			Path.push_back(nMaxReach);
			// re-initialize the steps to the amount
			// of steps to reach maxReach from position nArrayIndex.
			nSteps = nMaxReach - nArrayIndex;
		}
	}

	//printPath(Path.data(), Path.size());
	return nMinJump;
}


void generateMagicSquareOfOddSize(int nSize)
{
	if (nSize % 2 == 0)
	{
		return;
	}

	int** MagicSquare = new int*[nSize];

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		MagicSquare[nIndex] = new int[nSize];
		memset(MagicSquare[nIndex], 0, sizeof(MagicSquare[nIndex]));
	}

	int nRow = nSize / 2;
	int nColomn = nSize - 1;
	for (int nIndex = 1; nIndex < nSize * nSize; )
	{
		if (nRow == -1 && nColomn == nSize)
		{
			nRow = 0;
			nColomn = nSize - 2;
		}
		else
		{
			if (nRow < 0)
			{
				nRow = nSize - 1;
			}

			if (nColomn == nSize)
			{
				nColomn = 0;
			}
		}

		if (MagicSquare[nRow][nColomn])
		{
			nRow++;
			nColomn -= 2;
			continue;
		}
		else
		{
			MagicSquare[nRow][nColomn] = nIndex++;
		}

		nRow--;
		nColomn++;
	}
}

bool checkMagicSquareOrNot(int** MagicSquare, int nSize)
{
	//Check prime diagonal
	int nSum = 0;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		nSum += MagicSquare[nIndex][nIndex];
	}

	//Check rows with diagonal sum
	int nRowSum = 0;
	for (int nRowIndex = 0; nRowIndex < nSize; nRowIndex++)
	{
		nRowSum = 0;
		for (int nColomnIndex = 0; nColomnIndex < nSize; nColomnIndex++)
		{
			nRowSum += MagicSquare[nRowIndex][nColomnIndex];
		}

		if (nSum != nRowSum)
		{
			return false;
		}
	}

	//Check colomns with diagonal sum
	int nColomnSum = 0;
	for (int nColomnIndex = 0; nColomnIndex < nSize; nColomnIndex++)
	{
		nColomnSum = 0;
		for (int nRowIndex = 0; nRowIndex < nSize; nRowIndex++)
		{
			nRowSum += MagicSquare[nRowIndex][nColomnIndex];
		}

		if (nSum != nColomnSum)
		{
			return false;
		}
	}

	return true;
}

vector<vector<int>> generatePascalTriangle(int numRows) 
{
	vector<vector<int>> PascalMatrix;
	int val = 1;
	vector<int> eachRow;
	for (int nRowIndex = 0; nRowIndex < numRows; nRowIndex++)
	{
		eachRow.clear();
		val = 1;
		for (int nColIndex = 0; nColIndex <= nRowIndex; nColIndex++)
		{
			if (nColIndex == 0)
			{
				eachRow.push_back(1);
			}
			else if (nRowIndex == nColIndex)
			{
				eachRow.push_back(1);
			}
			else
			{
				val = val * (nRowIndex - nColIndex + 1) / (nColIndex);
				eachRow.push_back(val);
			}
		}
		PascalMatrix.push_back(eachRow);
	}
	return PascalMatrix;
}

void createPascalTriangle(int nSize)
{
	int** PascalMatrix = new int*[nSize + 1];

	for (int nIndex = 0; nIndex <= nSize; ++nIndex)
	{
		PascalMatrix[nIndex] = new int[nSize + 1];
		memset(PascalMatrix[nIndex], 0, sizeof(PascalMatrix[nIndex]));
	}

	for (int nRowIndex = 0; nRowIndex <= nSize; nRowIndex++)
	{
		for (int nColIndex = 0; nColIndex <= nRowIndex; nColIndex++)
		{
			if (nColIndex == 0)
			{
				PascalMatrix[nRowIndex][nColIndex] = 1;
			}
			else if (nRowIndex == nColIndex)
			{
				PascalMatrix[nRowIndex][nColIndex] = 1;
			}
			else
			{
				PascalMatrix[nRowIndex][nColIndex] = PascalMatrix[nRowIndex - 1][nColIndex - 1] + PascalMatrix[nRowIndex - 1][nColIndex];
			}
		}
	}

	for (int nRowIndex = 0; nRowIndex <= nSize; nRowIndex++)
	{
		for (int nColIndex = 0; nColIndex <= nRowIndex; nColIndex++)
		{
			std::cout << PascalMatrix[nRowIndex][nColIndex] << " ";
		}
		std::cout << std::endl;
	}

}

void printPascal(int nSize)
{
	for (int nLineIndex = 1; nLineIndex <= nSize; nLineIndex++)
	{
		int nValue = 1;  // used to represent C(line, i)
		for (int nColIndex = 1; nColIndex <= nLineIndex; nColIndex++)
		{
			printf("%d ", nValue);  // The first value in a line is always 1
			nValue = nValue * (nLineIndex - nColIndex) / nColIndex;
		}
		printf("\n");
	}
}


float calculatePower1(float nBase, int nPower)
{
	if (nBase < 0)
	{
		return 0;
	}

	if ((nPower == 0) || (nBase == 1))
	{
		return 1;
	}

	float nResult = 1;

	while (nPower != 0)
	{
		if (nPower % 2 != 0)
		{
			if (nPower > 0)
			{
				nResult *= nBase;
			}
			else
			{
				nResult /= nBase; 
			}
		}

		nPower /= 2;
		nBase *= nBase;
	}

	return nResult;
}

bool DetectAnyCycleInArray(int unsortedArr[], int nLength) 
{
	int slow = 0;
	int fast = 0;
	int cur = 0;

	while (cur < nLength) 
	{
		if (unsortedArr[slow] >= 0 && unsortedArr[slow] < nLength)
		{
			slow = unsortedArr[slow];
		}
		else 
		{
			++slow;
			fast = slow;
			cur = slow;
			continue;
		}

		int i = 0;
		while (i < 2 && unsortedArr[fast] >= 0 && unsortedArr[fast] < nLength) 
		{ 
			//move fast two steps one time
			fast = unsortedArr[fast];
			++i;
		}

		if (i < 2)
		{
			//less than two steps
			++fast;
			slow = fast;
			cur = fast;
		}
		else
		{
			//already move two steps
			if (fast == slow) 
			{ 
				//if a cycle exists, they must meet
				return true;
			}
		}
	}

	return false;
}

bool DetectCycleInArrayFromStart(int unsortedArr[], int nLength)
{
	int nSlow = 0;
	int nFast = 0;

	while (true)
	{
		if (nSlow < 0 || nFast < 0 || nSlow >= nLength || nFast >= nLength)
		{
			return false;
		}

		nFast = unsortedArr[nFast];

		if (nFast == nSlow)
		{
			return true;
		}

		if (nFast < 0 || nFast >= nLength)
		{
			return false;
		}

		nFast = unsortedArr[nFast];

		if (nFast == nSlow)
		{
			return true;
		}

		nSlow = unsortedArr[nSlow];
		if (nFast == nSlow)
		{
			return true;
		}
	}
}

int calcDivision(int dividend, int divisor) 
{
	//handle special cases
	if (divisor == 0)
	{
		return INT_MAX;
	}
	if (divisor == -1 && dividend == INT_MIN)
	{
		return INT_MAX;
	}

	//get positive values
	long lDividend = abs((long)dividend);
	long lDivisor = abs((long)divisor);

	/**
	 * KEY INSIGHT:
	 * Every integer lDividend can be represented in terms of lDivisor and powers of 2 as follows,
	 * lDividend = c + lDivisor * Math.pow(2, n) + lDivisor * Math.pow(2, m) + .... +
	 *               + ... + lDivisor * Math.pow(2, 0)
	 * where,
	 * c is the remainder and c < lDivisor,
	 * n is the highest power of 2 such that lDivisor * Math.pow(2,n) <= lDividend,
	 * m is the second highest power of 2 such that lDivisor * Math.pow(2,m) <= lDividend and so on.
	 *
	 * Since every integer has such a binary representation, we can successively reduce lDividend by amount
	 * equal to (lDivisor * Math.pow(2, highestPowerOfTwo)) until lDividend becomes c.
 	 *
	 * This way our search for the quotient can finish in O(log N) time.
	 *
	 * EXAMPLE 1:
	 * lDividend = 29, lDivisor = 3
	 * Iteration 1:
	 * Highest power of two whose product with 3 is less than 29 is 8. quotient = 8, lDividend = 29 - (8 * 3) = 5
	 * Iteration 2:
	 * Highest power of two whose product with 3 is less than 5 is 1. quotient = 8 + 1 = 9, lDividend = 5 - (1 * 3) = 2
	 * Stop. (lDividend < lDivisor) i.e. (2 < 3)
	 * Return 9.
	 *
	 * EXAMPLE 2:
	 * lDividend = 15, lDivisor = 7
	 * Iteration 1:
	 * Highest power of two whose product with 7 is less than 15 is 2. quotient = 2, lDividend = 15 - (2 * 7) = 1
	 * Stop. (lDividend < lDivisor) i.e. (1 < 7)
	 * Return 2.
	 */
	int quotient = 0;
	int highestPowerOfTwo = 0;

	// NOTES ON SOME BIT HACKS: 
	// 1. x << n is equivalent to x * Math.pow(2, n). (<< is Leftshift Operator)
	// 2. 1 << x is equivalent to Math.pow(2, x). (<< is Leftshift Operator)
	// 3. x and y have opposite signs if (x ^ y) < 0. (^ is Bitwise XOR)
	while (lDividend >= lDivisor)
	{
		highestPowerOfTwo = 0;
		// Keep finding the highest number such that (lDivisor * Math.pow(2, highestPowerOfTwo)) <= lDividend
		while (lDividend >= (lDivisor << highestPowerOfTwo))
		{
			highestPowerOfTwo++;
		}

		// Latest highestPowerOfTwo took lDivisor higher than lDividend, so contend with (highestPowerOfTwo - 1)
		highestPowerOfTwo = highestPowerOfTwo - 1;

		// Add the highestPowerOfTwo to our result.
		quotient += 1 << highestPowerOfTwo;
		// Reduce lDividend by amount (lDivisor * Math.pow(2, highestPowerOfTwo))
		lDividend -= (lDivisor << highestPowerOfTwo);
	}
	// If dividend and divisor had opposite signs, then sign of the result is negative.
	// Otherwise, sign of the result is positive.
	return ((dividend ^ divisor) < 0) ? -quotient : quotient;
}


/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/
int searchInRotatedArray(int sortedArray[], int nLow, int nHigh, int nKey)
{
	if (nLow > nHigh)
	{
		return -1;
	}

	int nMid = (nHigh + nLow) / 2;
	if (sortedArray[nMid] == nKey)
	{
		return nMid;
	}

	/* If arr[l...mid] is sorted */
	if (sortedArray[nLow] < sortedArray[nMid])
	{
		/* As this subarray is sorted, we can quickly
		check if key lies in half or other half */
		if (nKey >= sortedArray[nLow] && nKey < sortedArray[nMid])
		{
			return searchInRotatedArray(sortedArray, nLow, nMid - 1, nKey);
		}

		return searchInRotatedArray(sortedArray, nMid + 1, nHigh, nKey);
	}
	else if (sortedArray[nLow] > sortedArray[nMid])
	{
		/* If arr[l..mid] is not sorted, then arr[mid... r]
		must be sorted*/
		if (nKey > sortedArray[nMid] && nKey <= sortedArray[nHigh])
		{
			return searchInRotatedArray(sortedArray, nMid + 1, nHigh, nKey);
		}

		return searchInRotatedArray(sortedArray, nLow, nMid - 1, nKey);
	}
	else
	{
		return searchInRotatedArray(sortedArray, nLow + 1, nHigh, nKey);
	}
}

int searchInRotatedArrayIterative(int sortedArray[], int nLow, int nHigh, int nKey)
{
	while (nLow <= nHigh)
	{
		int nMid = (nHigh + nLow) / 2;
		if (sortedArray[nMid] == nKey)
		{
			return nMid;
		}

		/* If arr[l...mid] is sorted */
		if (sortedArray[nLow] < sortedArray[nMid])
		{
			/* As this subarray is sorted, we can quickly
			check if key lies in half or other half */
			if (nKey >= sortedArray[nLow] && nKey < sortedArray[nMid])
			{
				nHigh = nMid - 1;
			}
			else
			{
				nLow = nMid + 1;
			}
		}
		else if (sortedArray[nLow] > sortedArray[nMid])
		{
			/* If arr[l..mid] is not sorted, then arr[mid... r]
			must be sorted*/
			if (nKey > sortedArray[nMid] && nKey <= sortedArray[nHigh])
			{
				nLow = nMid + 1;
			}
			else
			{
				nHigh = nMid - 1;
			}
		}
		else
		{
			nLow++;

		}
	}
	return -1;
}


/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
Find the minimum element.
You may assume no duplicate exists in the array.

Example 1:
Input: [3,4,5,1,2]
Output: 1

Example 2:
Input: [4,5,6,7,0,1,2]
Output: 0
*/
int findMinInRotateArray(int sortedArray[], int nLow, int nHigh)
{
	if (nLow > nHigh)
	{
		return -1;
	}

	if (sortedArray[nLow] <= sortedArray[nHigh])
	{
		return sortedArray[nLow];
	}

	while (nLow <= nHigh)
	{
		if (nHigh - nLow == 1)
		{
			return sortedArray[nLow];
		}

		int nMid = nLow + (nHigh - nLow) / 2;
		if (sortedArray[nMid] > sortedArray[nHigh])
		{
			nLow = nMid;
		}
		else
		{
			nHigh = nMid;
		}
	}
	return sortedArray[nLow];
}

/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
Find the minimum element.
The array may contain duplicates.

Example 1:
Input: [1,3,5]
Output: 1

Example 2:
Input: [2,2,2,0,1]
Output: 0
*/
int findMinInRotateArrayWithDuplicates(int sortedArray[], int nLow, int nHigh)
{
	if (nLow > nHigh)
	{
		return -1;
	}

	while (nLow + 1 < nHigh)
	{
		int nMid = nLow + (nHigh - nLow) / 2;

		if (sortedArray[nMid] > sortedArray[nHigh])
		{
			nLow = nMid;
		}
		else if (sortedArray[nMid] < sortedArray[nHigh])
		{
			nHigh = nMid;
		}
		else
		{
			nHigh--;
		}
	}
	return min(sortedArray[nLow], sortedArray[nHigh]);;
}


/*Find first and last positions of an element in a sorted array

Input: arr[] = { 1, 3, 5, 5, 5, 5, 67, 123, 125 }
	x = 5
Output : First Occurrence = 2
		 Last Occurrence = 5*/
vector<int> searchRange(int sortedArray[], int nLow, int nHigh, int target)
{
	vector<int> result;
	int nMid = 0;
	int nTempIndex = 0;
	if (nLow > nHigh)
	{
		result.push_back(-1);
		result.push_back(-1);
		return result;
	}
	while (nLow + 1  < nHigh)
	{
		nMid = nLow + (nHigh - nLow) / 2;
		if (sortedArray[nMid] == target)
		{
			nTempIndex = nMid;
			while (sortedArray[nTempIndex] == target && nTempIndex >= 0)
			{
				nTempIndex--;
			}
			nLow = nTempIndex + 1;

			nTempIndex = nMid;
			while (sortedArray[nTempIndex] == target && nTempIndex <= nHigh)
			{
				nTempIndex++;
			}
			nHigh = nTempIndex - 1;

			break;
		}
		else if (sortedArray[nMid] < target)
		{
			nLow = nMid;
		}
		else
		{
			nHigh = nMid;
		}
	}

	if (sortedArray[nLow] != target &&  sortedArray[nHigh] != target)
	{
		nLow = -1;
		nHigh = -1;
	}
	else if (sortedArray[nLow] != target || sortedArray[nHigh] != target)
	{
		sortedArray[nLow] != target ? nLow = nHigh : nHigh = nLow;
	}
	result.push_back(nLow);
	result.push_back(nHigh);
	return result;
}

/*
Write a function to check whether two given strings are anagram of each other or not. 
An anagram of a string is another string that contains same characters, 
only the order of characters can be different.
For example, “abcd” and “dabc” are anagram of each other.check-whether-two-strings-are-anagram-of-each-other

one is permuation of other
*/
bool areAnagram(char *str1, char *str2)
{
	// Create 2 count arrays and initialize all values as 0
	int count1[256] = { 0 };
	int count2[256] = { 0 };
	int i;

	// For each character in input strings, increment count in
	// the corresponding count array
	for (i = 0; str1[i] && str2[i]; i++)
	{
		count1[str1[i]]++;
		count2[str2[i]]++;
	}

	// If both strings are of different length. Removing this
	// condition will make the program fail for strings like
	// "aaca" and "aca"
	if (str1[i] || str2[i])
		return false;

	// Compare count arrays
	for (i = 0; i < 256; i++)
		if (count1[i] != count2[i])
			return false;

	return true;
}

/* find product except self
[1, 2, 3, 4]
[24, 12, 8, 6]

sol:
left - [1, 1, 2, 6]
ans - right - [24, 12, 8, 6]*/

vector<int> findProductExceptSelf(int unsortedArr[], int size)
{
	vector<int> Result(size, 1);

	int temp = 1;
	/* In this loop, temp variable contains product of
	elements on left side excluding unsortedArr[nIndex]*/
	for (int nIndex = 0; nIndex < size; nIndex++)
	{
		Result[nIndex] = temp;
		temp *= unsortedArr[nIndex];
	}
	
	temp = 1;

	/* In this loop, temp variable contains product of
	elements on right side excluding unsortedArr[nIndex]*/
	for (int nIndex = size - 1; nIndex >= 0; nIndex--)
	{
		Result[nIndex] *= temp;
		temp *= unsortedArr[nIndex];
	}

	return Result;
}

/*
Given two list of unsorted intervals V1 and V2 write 2 functions 'OR ' and 'And' to return a new list

OR Function (union of list ): Input V1 = (2,4) (6,8) (1,3) V2 = (7,9) (2,5)
output = (1,5) (6,9)

And function : This will be intersection function and will return intersection of the lists
output = (2,4) (7,8)
*/

std::vector<std::pair<int, int>> unionOfSetOfIntervals(const std::vector<std::pair<int, int>>& v1,
													   const std::vector<std::pair<int, int>>& v2)
{
	std::vector<std::pair<int, int>> result;
	std::map<int, int> data;

	for (const auto& p : v1)
	{
		data[p.first]++;
		data[p.second]--;
	}
	for (const auto& p : v2)
	{
		data[p.first]++;
		data[p.second]--;
	}
	int i = 0;
	int count = 0;
	for (const auto& p : data)
	{
		if (count == 0)
		{
			i = p.first;
		}
		count += p.second;
		if (count == 0)
		{
			result.push_back(std::make_pair(i, p.first));
		}
	}

	return result;
}


/**
* @brief adjacent means that this interval ends exactly where the "other" interval starts
*/
bool isAdjacent(const std::pair<int, int> interval1, const std::pair<int, int> interval2)
{ 
	return (interval1.second + 1) == interval2.first;
}

bool mergeIfAdjacent(std::pair<int, int>& interval1, const std::pair<int, int>& interval2)
{
	if (isAdjacent(interval1, interval2))
	{
		interval1.second = interval2.second;
		return true;
	}
	return false;
}

bool intersects(const std::pair<int, int>& interval1, const std::pair<int, int>& interval2)
{
	return (interval2.first > interval1.first && interval2.first < interval1.second) ||
		   (interval2.second > interval1.first && interval2.second < interval1.second);
}

std::pair<int, int> createIntersection(const std::pair<int, int>& interval1, const std::pair<int, int>& interval2)
{
	std::pair<int, int> result;
	result.first = max(interval1.first, interval2.first);
	result.second = min(interval1.second, interval2.second);
	return result;
}

std::vector<std::pair<int, int>> intersectionOfSetOfIntervals(const std::vector<std::pair<int, int>>& v1,
															  const std::vector<std::pair<int, int>>& v2)
{
	// v1 and v2 are sorted
	std::vector<std::pair<int, int>> Result;
	std::vector<std::pair<int, int> >::const_iterator iter1 = v1.begin();
	std::vector<std::pair<int, int> >::const_iterator iter2 = v2.begin();
	while ((iter1 != v1.end()) && (iter2 != v2.end())) 
	{
		std::pair<int, int> interval1 = *iter1;
		while ((iter1 + 1) != v1.end() && mergeIfAdjacent(interval1, *(iter1 + 1)))
		{
			++iter1;
		}
		std::pair<int, int> interval2 = *iter2;
		while ((iter2 + 1) != v2.end() && mergeIfAdjacent(interval2, *(iter2 + 1)))
		{
			++iter2;
		}
		if (intersects(interval1, interval2)) 
		{
			Result.push_back(createIntersection(interval1, interval2));
		}
		// Advance the lowest interval
		(interval1.first < interval2.first) ? ++iter1 : ++iter2;
	}

	return Result;
}

std::vector<std::pair<int, int>> intersectionOfSetOfSortedIntervals(const std::vector<std::pair<int, int>>& List1,
																	const std::vector<std::pair<int, int>>& List2)
{
	std::vector<std::pair<int, int>> Result;
	int LeftIndex = 0;
	int RightIndex = 0;
	int List1Size = List1.size();
	int List2Size = List2.size();
	int Start = 0;
	int End = 0;

	while (LeftIndex < List1Size && RightIndex < List2Size)
	{
		Start = max(List1[LeftIndex].first, List2[RightIndex].first);
		End = min(List1[LeftIndex].second, List2[RightIndex].second);

		if (Start < End)
		{
			Result.push_back(make_pair(Start, End));
		}

		(List1[LeftIndex].second < List2[RightIndex].second) ? LeftIndex++ : RightIndex++;
	}

	return Result;
}


/*
Implement strStr().
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2

Example 2:
Input: haystack = "aaaaa", needle = "bba"
Output: -1
Clarification:
What should we return when needle is an empty string? This is a great question to ask during an interview.
For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
*/
int strStr(string haystack, string needle) 
{
	if (needle.empty())
	{
		return 0;
	}

	int haystackLength = haystack.length();
	int needleLength = needle.length();

	if (needleLength > haystackLength)
	{
		return -1;
	}

	//Knuth–Morris–Pratt(KMP) Pattern Matching
	//Construct temporary array to maintain size of suffix which is same as prefix
	//Time / space complexity is O(size of pattern)
	//if i == j then ar = j + 1;
	// else j = ar[j -1]
	         //j i
	//patern   a b c a b y
	//temp arr 0 0 0 1 2 0

	int LeftIndex = 0;
	int RightIndex = 1;
	std::vector<int> suffprefArray(needleLength, 0);

	while (RightIndex < needleLength)
	{
		if (needle[LeftIndex] == needle[RightIndex])
		{
			suffprefArray[RightIndex] = LeftIndex + 1;
			LeftIndex++;
			RightIndex++;
		}
		else
		{
			//check it is first index
			if (LeftIndex != 0)
			{
				LeftIndex = suffprefArray[LeftIndex - 1];
			}
			else
			{
				suffprefArray[RightIndex] = 0;
				RightIndex++;
			}
		}
	}

	//Compare
	int haystackIndex = 0;
	int needleIndex = 0;

	while (haystackIndex < haystackLength && needleIndex < needleLength)
	{
		if (haystack[haystackIndex] == needle[needleIndex])
		{
			haystackIndex++;
			needleIndex++;
		}
		else
		{
			if (needleIndex != 0)
			{
				needleIndex = suffprefArray[needleIndex - 1];
			}
			else
			{
				haystackIndex++;
			}
		}
	}

	if (needleIndex == needleLength)
	{
		return (haystackIndex - RightIndex);
	}
	return -1;
}

/*
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.
*/
bool isValidSudoku(vector<vector<char>>& board)
{
	//each index of below rows, cols, squares represents a binary number 1 - 9.
	//each index of rows represent numbers in 0 - 8 cells in a row
	vector<short> rows(9, 0);
	vector<short> cols(9, 0);
	vector<short> squares(9, 0);

	int rowSize = board.size();
	int colomSize = board[0].size();

	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colomSize; col++) 
		{
			if (board[row][col] == '.')
			{
				continue;
			}

			/*
			if cell contains 1 -> (1 << '1' - '1') -> 1 << 0 ->000000001
			if cell contains 2 -> (1 << '2' - '1') -> 1 << 1 ->000000010
			*/
			short value = (short)(1 << (board[row][col] - '1'));

			//Note : The bitwise AND operator (&) compares each bit of the first operand to 
			//the corresponding bit of the second operand. If both bits are 1, the corresponding
			//result bit is set to 1. Otherwise, the corresponding result bit is set to 0.

			//Do binary "and"(&) operation to make sure value is not present in that row.
			//if it is already present then AND operation will return > 0
			//for example the value in 3rd cell in 1st row is 3, then the value is 
			//3 -> (1 << '3' - '1') -> 1 << 2 ->000000100
			//if the 1st row contains 3 in any of the cell then the value in
			//rows[1] -> 000000100 ->3rd pos from right should be "1"
			//then 000000100 & 000000100 -> 000000100 ie greater than 1.
			//if 3 is not there then 000000100 & 000000001 -> 000000000
			if ((value & rows[row]) > 0)
			{
				return false;
			}
			if ((value & cols[col]) > 0)
			{
				return false;
			}
			
			//squares[3 * (row / 3) + col / 3]
			//this is to find the cell of each square
			if ((value & squares[3 * (row / 3) + col / 3]) > 0)
			{
				return false;
			}

			//do OR operation to update the values
			rows[row] |= value;
			cols[col] |= value;
			squares[3 * (row / 3) + col / 3] |= value;
		}
	}

	return true;

}

/* Returns a boolean which indicates whether an assigned entry
in the specified row matches the given number. */
bool checkInRow(const vector<vector<int>>& Puzzle, int row, int numToCheck)
{
	for (int Index = 0; Index < Puzzle.size(); Index++)
	{
		if (Puzzle[row][Index] == numToCheck)
		{
			return true;
		}
	}
	return false;
}

/* Returns a boolean which indicates whether an assigned entry
in the specified column matches the given number. */
bool checkInCol(const vector<vector<int>>& Puzzle, int col, int numToCheck)
{
	for (int Index = 0; Index < Puzzle.size(); Index++)
	{
		if (Puzzle[Index][col] == numToCheck)
		{
			return true;
		}
	}
	return false;
}

/* Returns a boolean which indicates whether an assigned entry
within the specified 3x3 box matches the given number. */
bool CheckInBox(const vector<vector<int>>& Puzzle, int boxStartRow, int boxStartCol, int numToCheck)
{
	for (int RowIndex = 0; RowIndex < 3; RowIndex++)
	{
		for (int ColIndex = 0; ColIndex < 3; ColIndex++)
		{
			if (Puzzle[RowIndex + boxStartRow][ColIndex + boxStartCol] == numToCheck)
			{
				return true;
			}
		}
	}
	return false;
}

/* This function finds an entry in grid that is still unassigned.
 Searches the grid to find an entry that is still unassigned. If
found, the reference parameters row, col will be set the location
that is unassigned, and true is returned. If no unassigned entries
remain, false is returned. */
bool findAnyCellsUnAssigned(const vector<vector<int>>& Puzzle, int& rowIndex, int& colIndex)
{
	int rowSize = Puzzle.size();
	int colSize = rowSize;

	for (int RowIndex = 0; RowIndex < rowSize; RowIndex++)
	{
		for (int ColIndex = 0; ColIndex < colSize; ColIndex++)
		{
			if (Puzzle[RowIndex][ColIndex] == 0)
			{
				rowIndex = RowIndex;
				colIndex = ColIndex;
				return true;
			}
		}
	}

	return false;
}
/*
Given a partially filled 9×9 2D array ‘grid[9][9]’, the goal is to assign digits (from 1 to 9) 
to the empty cells so that every row, column, and subgrid of size 3×3 contains exactly one instance of the digits from 1 to 9.
*/
bool solveSudoko(vector<vector<int>>& Puzzle)
{
	int row = 0;
	int col = 0;
	int numSize = Puzzle.size();

	// If there is no unassigned location, we are done
	if (!findAnyCellsUnAssigned(Puzzle, row, col))
	{
		return true;
	}

	// consider digits 1 to grid size.
	for (int numToAssign = 1; numToAssign <= numSize; numToAssign++)
	{
		/* Check if 'num' is not already placed in current row,
		current column and current 3x3 box */
		if (!checkInCol(Puzzle, row, numToAssign) && !checkInRow(Puzzle, col, numToAssign) && 
			!CheckInBox(Puzzle, row - row % 3, col - col % 3, numToAssign))
		{
			Puzzle[row][col] = numToAssign;
		}

		//return, if success.
		if (solveSudoko(Puzzle))
		{
			return true;
		}

		// failure, unassign & try again
		Puzzle[row][col] = 0;
	}

	return false;
}


/*
Given a non-empty array of digits representing a non-negative integer, plus one to the integer.
The digits are stored such that the most significant digit is at the head of the list, 
and each element in the array contain a single digit.
You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:
Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
*/
vector<int> plusOne(vector<int>& digits)
{
	int Carry = 1;
	int Sum = 0;
	vector<int> Result;
	int Length = digits.size();
	if (Length < 1)
	{
		return Result;
	}
	for (int Index = Length - 1; Index >= 0; Index--)
	{
		Sum = digits[Index] + Carry;
		(Sum > 9) ? Carry = 1 : Carry = 0;
		digits[Index] = Sum % 10;
	}

	//Result.reserve(Length + Carry);
	if (Carry == 1)
	{
		Result.push_back(Carry);
		Carry = 0;
	}

	while (Carry < Length)
	{
		Result.push_back(digits[Carry]);
		Carry++;
	}
	return Result;
}

/*
Given a collection of intervals, merge all overlapping intervals.

Example 1:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considerred overlapping.
*/

struct Interval 
{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};
vector<Interval> mergeIntervals(vector<Interval>& intervals)
{
	int Size = intervals.size();
	//Sort in ascending order
	std::sort(intervals.begin(), intervals.end(),
		     [](Interval const& interval1, Interval const& interval2)
			  { return interval1.start < interval2.start; });

	int Index = 0;
	vector<Interval> Result;
	for (int IntIndex = 0; IntIndex < Size; IntIndex++)
	{
		if (Index != 0 && (Result[Index - 1].end >= intervals[IntIndex].start))
		{
			//This will merge more than 2 intervals like
			//Input: [[1,4],[0,2],[3,5]] -> [[0,2],[1,4],[3,5]]
			//Output:[[0,5]]
			Result[Index - 1].start = min(Result[Index - 1].start, intervals[IntIndex].start);
			Result[Index - 1].end = max(Result[Index - 1].end, intervals[IntIndex].end);
			Index--;
		}
		else
		{
			Result.push_back(intervals[IntIndex]);
		}
		Index++;
	}

	return Result;
}

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
*/
vector<Interval> insertIntervalinSortedIntervals(vector<Interval>& intervals, Interval newInterval)
{
	int Size = intervals.size();
	vector<Interval> Result;
	for (int IntIndex = 0; IntIndex < Size; IntIndex++)
	{
		//new interval is greater than the current one, then add current one to result. ie: insert after
		if (intervals[IntIndex].end < newInterval.start)
		{
			Result.push_back(intervals[IntIndex]);
		}
		//new interval is less than the current one, then add new interval to result. ie: insert before
		//and make current one as new interval.
		else if (intervals[IntIndex].start > newInterval.end)
		{
			Result.push_back(newInterval);
			newInterval = intervals[IntIndex];
		}
		//overlap, then merge intervals ie: insert in between
		else if (intervals[IntIndex].end >= newInterval.start || intervals[IntIndex].start <= newInterval.end)
		{
			newInterval.start = min(intervals[IntIndex].start, newInterval.start);
			newInterval.end = max(newInterval.end, intervals[IntIndex].end);
		}
	}

	Result.push_back(newInterval);
	return Result;
}


/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
Output: [1,2,2,3,5,6]
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
	int LeftIndex = 0;
	int RightIndex = 0;
	while (LeftIndex < m && RightIndex < n)
	{
		if (nums1[LeftIndex] < nums2[RightIndex])
		{
			LeftIndex++;
		}
		else if (nums1[LeftIndex] > nums2[RightIndex])
		{
			swap(nums1[LeftIndex], nums2[RightIndex]);
			int Index = RightIndex;
			while (Index < n - 1)
			{
				if (nums2[Index] > nums2[Index + 1])
				{
					swap(nums2[Index], nums2[Index + 1]);
				}
				Index++;
			}
			LeftIndex++;
		}
		else
		{
			LeftIndex++;
		}
	}

	while (LeftIndex < (m + n) && n > 0)
	{
		nums1[LeftIndex] = nums2[RightIndex];
		LeftIndex++;
		RightIndex++;
	}
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
{
	int m = obstacleGrid.size();
	int n = 0;
	if (m > 0)
	{
		n = obstacleGrid[0].size();
	}
	if (m == 0 || n == 0)
	{
		return 0;
	}
	if (obstacleGrid[0][0] == 1)
	{
		return 0;
	}

	int** temp = new int*[m];

	for (int Index = 0; Index < m; Index++)
	{
		temp[Index] = new int[n];
		memset(temp[Index], 0, sizeof(temp[Index]) * n);
	}

	for (int rowIndex = 0; rowIndex < m; rowIndex++)
	{
		for (int colIndex = 0; colIndex < n; colIndex++)
		{
			if (rowIndex == 0 && colIndex == 0 && obstacleGrid[rowIndex][colIndex] == 0)
			{
				temp[rowIndex][colIndex] = 1;
			}
			else if (rowIndex == 0 && (obstacleGrid[rowIndex][colIndex] == 0))
			{
				temp[rowIndex][colIndex] = max(temp[rowIndex][colIndex], temp[rowIndex][colIndex - 1]);
			}
			else if (colIndex == 0 && (obstacleGrid[rowIndex][colIndex] == 0))
			{
				temp[rowIndex][colIndex] = max(temp[rowIndex][colIndex], temp[rowIndex - 1][colIndex]);
			}
			else if (obstacleGrid[rowIndex][colIndex] == 0)
			{
				temp[rowIndex][colIndex] = temp[rowIndex - 1][colIndex] + temp[rowIndex][colIndex - 1];
			}
		}
	}

	int result = temp[m - 1][n - 1];
	for (int Index = 0; Index < m; Index++)
	{
		delete temp[Index];
	}
	delete[] temp;
	return result;
}

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.

Example 1:
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
jump length is 0, which makes it impossible to reach the last index.
*/
bool canJump(vector<int>& nums)
{
	int nSize = nums.size();
	int maxReach = nums[0];
	if (nSize <= 1)
	{
		return true;
	}
	//3,2,2,0,1
	//0,1,2,3,4
	for (int Index = 0; Index < nSize; Index++)
	{
		if (maxReach <= Index && nums[Index] <= 0)
		{
			return false;
		}

		if (Index + nums[Index] > maxReach)
		{
			maxReach = Index + nums[Index];
		}

		if (maxReach >= nSize - 1)
		{
			return true;
		}
	}

	return false;
}

/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:
Input:
[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:
Input:
[
[1, 2, 3, 4],
[5, 6, 7, 8],
[9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
	int rowSize = matrix.size();
	int colSize = 0;
	if (rowSize > 0)
	{
		colSize = matrix[0].size();
	}
	vector<int> spiralOrderResult;
	/*rowIndex - starting row index
	lastRow - ending row index
	colIndex - starting column index
	lastCol - ending column index
	Index - iterator*/
	int startRow = 0;
	int startCol = 0;
	int lastRow = rowSize - 1;
	int lastCol = colSize - 1;
	int Index = 0;

	while (startRow <= lastRow && startCol <= lastCol)
	{
		/* Print the first row from the remaining rows */
		for (Index = startCol; Index <= lastCol; Index++)
		{
			spiralOrderResult.push_back(matrix[startRow][Index]);
		}
		startRow++;

		/* Print the last column from the remaining columns */
		for (Index = startRow; Index <= lastRow; Index++)
		{
			spiralOrderResult.push_back(matrix[Index][lastCol]);
		}
		lastCol--;

		if (startRow <= lastRow)
		{
			/* Print the last row from the remaining rows */
			for (Index = lastCol; Index >= startCol; Index--)
			{
				spiralOrderResult.push_back(matrix[lastRow][Index]);
			}
			lastRow--;
		}

		if (startCol <= lastCol)
		{
			/* Print the first column from the remaining columns */
			for (Index = lastRow; Index >= startRow; Index--)
			{
				spiralOrderResult.push_back(matrix[Index][startCol]);
			}
			startCol++;
		}
	}
	return spiralOrderResult;
}

/*
Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:
Input: 3
Output:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]
*/
vector<vector<int>> generateMatrix(int n) 
{
	vector<vector<int>> spiralMatrix(n, vector<int>(n, 0));
	/*rowIndex - starting row index
	lastRow - ending row index
	colIndex - starting column index
	lastCol - ending column index
	Index - iterator*/
	int startRow = 0;
	int startCol = 0;
	int lastRow = n - 1;
	int lastCol = n - 1;
	int Index = 0;
	int number = 1;

	while (startRow <= lastRow && startCol <= lastCol)
	{
		/* Print the first row from the remaining rows */
		for (Index = startCol; Index <= lastCol; Index++)
		{
			spiralMatrix[startRow][Index] = number++;
		}
		startRow++;

		/* Print the last column from the remaining columns */
		for (Index = startRow; Index <= lastRow; Index++)
		{
			spiralMatrix[Index][lastCol] = number++;
		}
		lastCol--;

		if (startRow <= lastRow)
		{
			/* Print the last row from the remaining rows */
			for (Index = lastCol; Index >= startCol; Index--)
			{
				spiralMatrix[lastRow][Index] = number++;
			}
			lastRow--;
		}

		if (startCol <= lastCol)
		{
			/* Print the first column from the remaining columns */
			for (Index = lastRow; Index >= startRow; Index--)
			{
				spiralMatrix[Index][startCol] = number++;
			}
			startCol++;
		}
	}
	return spiralMatrix;
}


/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:
Input:
[
[1,1,1],
[1,0,1],
[1,1,1]
]
Output:
[
[1,0,1],
[0,0,0],
[1,0,1]
]
*/
void setZeroes(vector<vector<int>>& matrix) 
{
	int rowSize = matrix.size();
	int colSize = matrix[0].size();
	bool bFirstRowContainsZero = false;
	bool bFirstColContainsZero = false;

	//Check whether first row contains '0'
	for (int Index = 0; Index < colSize; Index++)
	{
		if (matrix[0][Index] == 0)
		{
			bFirstRowContainsZero = true;
			break;
		}
	}

	//Check whether first col contains '0'
	for (int Index = 0; Index < rowSize; Index++)
	{
		if (matrix[Index][0] == 0)
		{
			bFirstColContainsZero = true;
			break;
		}
	}

	//mark first row and col for any cells contains '0' 
	for (int rowIndex = 1; rowIndex < rowSize; rowIndex++)
	{
		for (int colIndex = 1; colIndex < colSize; colIndex++)
		{
			if (matrix[rowIndex][colIndex] == 0)
			{
				matrix[rowIndex][0] = 0;
				matrix[0][colIndex] = 0;
			}
		}
	}

	//set rows and cols marked as '0' 
	for (int rowIndex = 1; rowIndex < rowSize; rowIndex++)
	{
		for (int colIndex = 1; colIndex < colSize; colIndex++)
		{
			if (matrix[0][colIndex] == 0 || matrix[rowIndex][0] == 0)
			{
				matrix[rowIndex][colIndex] = 0;
			}
		}
	}

	//Set first row and col
	if (bFirstRowContainsZero)
	{
		for (int Index = 0; Index < colSize; Index++)
		{
			matrix[0][Index] = 0;
		}
	}

	if (bFirstColContainsZero)
	{
		for (int Index = 0; Index < rowSize; Index++)
		{
			matrix[Index][0] = 0;
		}
	}

}

/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
Example 1:

Input:
matrix = [
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
target = 3
Output: true
*/
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
	int rowSize = matrix.size();
	int colSize = 0;
	if (rowSize > 0)
	{
		colSize = matrix[0].size();
	}

	if (colSize <= 0)
	{
		return false;
	}

	int rowIndex = -1;

	for (int Index = 0; Index < rowSize; Index++)
	{
		if (matrix[Index][0] == target)
		{
			return true;
		}
		else if (matrix[Index][0] > target)
		{
			rowIndex = Index - 1;
			break;
		}
	}

	if (rowIndex == -1)
	{
		rowIndex = rowSize - 1;
	}
	for (int Index = 0; Index < colSize; Index++)
	{
		if (matrix[rowIndex][Index] == target)
		{
			return true;
		}
	}

	return false;
}

/*
Search a value in a sorted matrix.
1, 2, 3, 4
7, 10, 13, 12,
22, 23, 24, 25
*/
bool binarysearchMatrix(vector<vector<int>>& matrix, int target)
{
	int rowSize = matrix.size();
	int colSize = 0;
	if (rowSize > 0)
	{
		colSize = matrix[0].size();
	}

	if (colSize <= 0)
	{
		return false;
	}

	int start = 0;
	int end = rowSize * colSize - 1;

	while (start <= end)
	{
		int mid = (start + end) / 2;
		int midX = mid / colSize;
		int midY = mid % colSize;

		if (matrix[midX][midY] == target)
		{
			return true;
		}

		if (matrix[midX][midY]<target)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	return false;
}

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

Example:
Input: n = 4, k = 2
Output:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
void combDFS(vector<vector<int>>& resultSet, vector<int>& eachComb, int num,
	int kSize, int start)
{
	if (eachComb.size() == kSize)
	{
		resultSet.push_back(eachComb);
		return;
	}

	/*
	((start != 1) || (Index + (kSize - 1))
	above condition is to avoid extra iteraions like below.
	input : 1, 2, 3, 4, 5 and k = 3
	with 4 and 5 cannot make a combination of k = 3, can be make with start index - 1, 2, 3.
	so exit loop, when (start == 1) && (Index + (k - 1)) > num ie. when start index = 4, start = 1 then (4 + (3 - 1)) > 5
	*/
	for (int Index = start; Index <= num && ((start != 1) || (Index + (kSize - 1)) <= num); Index++)
	{
		eachComb.push_back(Index);
		combDFS(resultSet, eachComb, num, kSize, Index + 1);
		eachComb.pop_back();
	}
}

vector<vector<int>> combine(int n, int k)
{
	vector<vector<int>> resultSet;
	vector<int> eachCombSet;
	if (n >= 0 && n >= k)
	{
		combDFS(resultSet, eachCombSet, n, k, 1);
	}
	return resultSet;
}

/*
Another method
For example, the (4, 2) test case yields:

Incremented element at index 0
[1, 0]
Moved index to the right, and copied the value from the left
[1, 1]
Incremented element at index 1
[1, 2]
Combination found!
Added [1, 2] as an answer!
Incremented element at index 1
[1, 3]
Combination found!
Added [1, 3] as an answer!
Incremented element at index 1
[1, 4]
Combination found!
Added [1, 4] as an answer!
Incremented element at index 1
[1, 5]
n exceeded at 1, moving index to the left
Incremented element at index 0
[2, 5]
Moved index to the right, and copied the value from the left
[2, 2]
Incremented element at index 1
[2, 3]
Combination found!
Added [2, 3] as an answer!
Incremented element at index 1
[2, 4]
Combination found!
Added [2, 4] as an answer!
Incremented element at index 1
[2, 5]
n exceeded at 1, moving index to the left
Incremented element at index 0
[3, 5]
Moved index to the right, and copied the value from the left
[3, 3]
Incremented element at index 1
[3, 4]
Combination found!
Added [3, 4] as an answer!
Incremented element at index 1
[3, 5]
n exceeded at 1, moving index to the left
Incremented element at index 0
[4, 5]
Moved index to the right, and copied the value from the left
[4, 4]
Incremented element at index 1
[4, 5]
n exceeded at 1, moving index to the left
Incremented element at index 0
[5, 5]
n exceeded at 0, moving index to the left
[[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]
*/
vector<vector<int>> findCombination(int num, int ksize)
{
	vector<vector<int>> resultSet;
	vector<int> eachCombSet(ksize, 0);
	int Index = 0;
	if (num >= 0 && num >= ksize)
	{
		while (Index >= 0)
		{
			eachCombSet[Index]++;

			if (eachCombSet[Index] > num)
			{
				Index--;
			}
			else if (Index == (ksize - 1))
			{
				resultSet.push_back(eachCombSet);
			}
			else
			{
				++Index;
				eachCombSet[Index] = eachCombSet[Index - 1];
			}
		}
	}
	return resultSet;
}

/*
Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:
Input: nums = [1,2,3]
Output:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
*/
void subsetsDFS(vector<vector<int>>& resultSet, vector<int>& eachComb, vector<int>& nums,			
				int Size, int start)
{
	resultSet.push_back(eachComb);

	for (int Index = start; Index < Size; Index++)
	{
		eachComb.push_back(nums[Index]);
		subsetsDFS(resultSet, eachComb, nums, Size, Index + 1);
		eachComb.pop_back();
	}
}

vector<vector<int>> subsets(vector<int>& nums)
{
	vector<vector<int>> resultSet;
	vector<int> eachSet;
	int Size = nums.size();
	subsetsDFS(resultSet, eachSet, nums, Size, 0);
	return resultSet;
}

/*
With dup
[1,2,2]
*/
void dupsubsetsDFS(vector<vector<int>>& resultSet, vector<int>& eachComb, vector<int>& nums,
	int Size, int start)
{
	resultSet.push_back(eachComb);

	for (int Index = start; Index < Size; Index++)
	{
		eachComb.push_back(nums[Index]);
		dupsubsetsDFS(resultSet, eachComb, nums, Size, Index + 1);
		eachComb.pop_back();
		//check duplicates at end of each index iteration and increment index.
		//after 0th index iteration -> [], [1], [1,2], [1,2,2]
		//1th index -> [2], [2, 2]
		//end of 1th index will check dup (1 + 1) < 3 &&(2 == 2) so Index++ -> becomes 2, then again for loop
		//also increase Index++ -> 3 exiyt the loop.
		while (Index + 1 < Size && nums[Index] == nums[Index + 1])
		{
			Index++;
		}
	}
}

vector<vector<int>> subsetsdup(vector<int>& nums)
{
	vector<vector<int>> resultSet;
	vector<int> eachSet;
	std::sort(nums.begin(), nums.end());
	int Size = nums.size();
	dupsubsetsDFS(resultSet, eachSet, nums, Size, 0);
	return resultSet;
}

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells
are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example:
board =
[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
*/
bool DFS(vector<vector<char>>& board, string word, int rowIndex, int colIndex, int wordIndex)
{
	int rowSize = board.size();
	int colSize = board[0].size();

	if (rowIndex < 0 || colIndex < 0 || rowIndex >= rowSize || colIndex >= colSize)
	{
		return false;
	}

	if (board[rowIndex][colIndex] == word[wordIndex])
	{
		board[rowIndex][colIndex] = '#';
		if (wordIndex == word.size() - 1)
		{
			return true;
		}
		else if (DFS(board, word, rowIndex - 1, colIndex, wordIndex + 1) ||
			DFS(board, word, rowIndex + 1, colIndex, wordIndex + 1) ||
			DFS(board, word, rowIndex, colIndex - 1, wordIndex + 1) ||
			DFS(board, word, rowIndex, colIndex + 1, wordIndex + 1))
		{
			return true;
		}
		board[rowIndex][colIndex] = word[wordIndex];
	}
	return false;
}

bool exist(vector<vector<char>>& board, string word)
{
	int rowSize = board.size();
	int colSize = 0;
	if (rowSize > 0)
	{
		colSize = board[0].size();
	}

	int wordIndex = 0;

	for (int rowIndex = 0; rowIndex < rowSize; rowIndex++)
	{
		for (int colIndex = 0; colIndex < colSize; colIndex++)
		{
			if (DFS(board, word, rowIndex, colIndex, 0))
			{
				return true;
			}
		}
	}
	return false;
}

/*
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
[7],
[2,2,3]
]
Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
[2,2,2,2],
[2,3,3],
[3,5]
]
*/
void subsetsDFSCombSum(vector<vector<int>>& resultSet, vector<int>& eachComb, vector<int>& candidates,
				int Size, int start, const int& target)
{
	if (target < 0 || start > candidates.size())
	{
		return;
	}
	else if (target == 0)
	{
		resultSet.push_back(eachComb);
		return;
	}

	for (int Index = start; Index < Size && candidates[Index] <= target; Index++)
	{
		eachComb.push_back(candidates[Index]);
		subsetsDFSCombSum(resultSet, eachComb, candidates, Size, Index, target - candidates[Index]);
		eachComb.pop_back();
	}
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
{
	vector<vector<int>> resultSet;
	vector<int> eachSet;
	std::sort(candidates.begin(), candidates.end());
	int Size = candidates.size();
	subsetsDFSCombSum(resultSet, eachSet, candidates, Size, 0, target);
	return resultSet;
}

/*
Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
[1,2,2],
[5]
]
*/
void subsetsDFSCombSum2(vector<vector<int>>& resultSet, vector<int>& eachComb, vector<int>& candidates,
						int Size, int start, const int& target)
{
	if (target < 0 || start > candidates.size())
	{
		return;
	}
	else if (target == 0)
	{
		resultSet.push_back(eachComb);
		return;
	}

	for (int Index = start; Index < Size && candidates[Index] <= target; Index++)
	{
		eachComb.push_back(candidates[Index]);
		subsetsDFSCombSum2(resultSet, eachComb, candidates, Size, Index + 1, target - candidates[Index]);
		eachComb.pop_back();
		//check duplicates at end of each index iteration and increment index.
		//after 0th index iteration -> [], [1], [1,2], [1,2,2]
		//1th index -> [2], [2, 2]
		//end of 1th index will check dup (1 + 1) < 3 &&(2 == 2) so Index++ -> becomes 2, then again for loop
		//also increase Index++ -> 3 exiyt the loop.
		while (Index + 1 < Size && candidates[Index] == candidates[Index + 1])
		{
			Index++;
		}
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
	vector<vector<int>> resultSet;
	vector<int> eachSet;
	std::sort(candidates.begin(), candidates.end());
	int Size = candidates.size();
	subsetsDFSCombSum2(resultSet, eachSet, candidates, Size, 0, target);
	return resultSet;
}

/*
Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Example 1:
Given nums = [1,1,1,2,2,3],
Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It doesn't matter what you leave beyond the returned length.
*/
int removeDuplicatesInPlace(vector<int>& nums) 
{
	int Size = nums.size();
	if (Size < 3)
	{
		return Size;
	}
	int newIndex = 1;
	int count = 1;

	for (int Index = 1; Index < Size; Index++)
	{
		if (nums[Index] != nums[Index - 1])
		{
			nums[newIndex++] = nums[Index];
			count = 1;
		}
		else if (count == 1)
		{
			nums[newIndex++] = nums[Index];
			count = 2;
		}
	}
	return newIndex;
}

/*
Question 1: Write a function which accepts an integer array and its size and modifies the array in the following manner:
1) If the elements of index i and (i+1) are equal then, double the value at index i
and replace the element at index (i+1) with 0.

2) If the element at index i is 0, then ignore it.

3) Any number (element in an array) must be modified only once.

4) At the end, shift all the zeros (0s) to the right of the array and remaining
nonzeros to the left of the array.

Example:
Input: 2 2 0 4 0 8
Output: 4 4 8 0 0 0

Input: 2 2 0 4 0 2
Output: 4 4 2 0 0 0
*/
vector<int> modifyArray(vector<int> inputArray)
{
	int Size = inputArray.size();
	int NewIndex = 0;
	for (int Index = 0; Index < Size; Index++)
	{
		if ((Index + 1) < Size && inputArray[Index] == inputArray[Index + 1] && inputArray[Index] != 0)
		{
			inputArray[Index] *= inputArray[Index];
			swap(inputArray[NewIndex], inputArray[Index]);
			inputArray[Index + 1] = 0;
			NewIndex++;
		}
		else if (inputArray[Index] != 0)
		{
			swap(inputArray[NewIndex], inputArray[Index]);
			NewIndex++;
		}
	}
	return inputArray;
}

/*
Write a function which accepts an integer array and its size and 
returns the maximum index difference i.e. (i-j) such that array[i] < array[j] and i < j.
If there is no such case, return -1 .

Input: 2 0 3 5 6 1
Output: 4

There was only one test case given which is mentioned above. But I am providing the below
one of the sample cases which is an important thing to be noted. It returns -1 because all the
elements after any given element are smaller than it. DO take care of such cases.

Input: 9 8 7 6 5
Output: -1
*/
int maxIndicesDiff(vector<int> inputArray)
{
	int Size = inputArray.size();
	vector<int> minArray(Size, 0);
	vector<int> maxArray(Size, 0);
	
	//Fill minArray with min values from left to right.
	for (int Index = 0; Index < Size; Index++)
	{
		if (Index > 0)
		{
			minArray[Index] = min(minArray[Index - 1], inputArray[Index]);
		}
		else
		{
			minArray[Index] = inputArray[Index];
		}
	}

	//Fill maxArray with max values from right to left.
	for (int Index = Size - 1; Index >= 0; Index--)
	{
		if ((Index + 1) < Size)
		{
			maxArray[Index] = max(maxArray[Index + 1], inputArray[Index]);
		}
		else
		{
			maxArray[Index] = inputArray[Index];
		}
	}

	//Calculate maxDiff of indexes of min and max array and increase i and j
	/* Traverse both arrays from left to right to find optimum j - i
	This process is similar to merge() of MergeSort */

	int i = 0;
	int j = 0;
	int maxDiff = -1;

	while (i < Size && j < Size)
	{
		if (minArray[i] < maxArray[j])
		{
			maxDiff = max(maxDiff, j - i);
			j++;
		}
		else
		{
			i++;
		}
	}

	return maxDiff;
}

/*
We can avoid checking the whole array by starting from the maximum difference of j-i 
and comparing arr[j]>arr[i] for all the possible combinations j and i for that particular
maximum difference Whenever we get a combination of (j,i) with arr[j]>arr[i] we can exit the loop
*/
int maxIndexDiff(vector<int> inputArray)
{
	int Size = inputArray.size();
	//initialize max index diff as Size - 1.
	int maxDiff = Size - 1;
	int i, j;
	//logic is assuming maxDiff as size - 1 and for each max diff
	//start j from size - 1 and find i ie j - i = maxDiff, then i = j - maxDiff
	//whenever arr[j] > arr[i] retrun maxDiff, since we start maxDiff from size - 1, 
	//that would be the maximum value.
	while (maxDiff > 0)
	{
		j = Size - 1;
		while (j >= maxDiff)
		{
			i = j - maxDiff;
			if (inputArray[j] > inputArray[i])
			{
				return maxDiff;
			}
			j--;
		}
		maxDiff--;
	}
	return -1;
}

/*
Find the minimum distance between two numbers
Given an unsorted array arr[] and two numbers x and y, find the minimum distance between x and y in arr[].
The array might also contain duplicates. You may assume that both x and y are different and present in arr[].

Examples:
Input: arr[] = {1, 2}, x = 1, y = 2
Output: Minimum distance between 1 and 2 is 1.

Input: arr[] = {3, 4, 5}, x = 3, y = 5
Output: Minimum distance between 3 and 5 is 2.

Input: arr[] = {3, 5, 4, 2, 6, 5, 6, 6, 5, 4, 8, 3}, x = 3, y = 6
Output: Minimum distance between 3 and 6 is 4.

Input: arr[] = {2, 5, 3, 5, 4, 4, 2, 3}, x = 3, y = 2
Output: Minimum distance between 3 and 2 is 1.
*/
int findMinDistance(vector<int> unsortedArray, int x, int y)
{
	int Size = unsortedArray.size();
	int prevVal = -1;
	int minDist = Size - 1;

	for (int Index = 0; Index < Size; Index++)
	{
		if (unsortedArray[Index] == x || unsortedArray[Index] == y)
		{
			if (prevVal != -1)
			{
				if (unsortedArray[Index] != unsortedArray[prevVal])
				{
					minDist = min(minDist, Index - prevVal);
				}
			}
			prevVal = Index;
		}
	}
	return minDist;
}

/*
Given a rectangle of size AxB we had to find minimum number of squares that could be formed from that particular rectangle.
Input  : 13 x 29
Output : 9
Explanation :
2 (squares of size 13x13) +
4 (squares of size 3x3) +
3 (squares of size 1x1)=9

Input  : 4 x 5
Output : 5
Explanation :
1 (squares of size 4x4) +
4 (squares of size 1x1)
*/
int findMinimumSquares(int width, int height)
{
	int result = 0;
	int rem = 0;
	if (width < height)
	{
		swap(width, height);
	}

	while (height > 0)
	{
		result += width / height;
		rem = width % height;
		width = height;
		height = rem;
	}
	return result;
}

/*
Factorial of large number
Input : 100
Output : 933262154439441526816992388562667004-
907159682643816214685929638952175999-
932299156089414639761565182862536979-
208272237582511852109168640000000000-
00000000000000

Input :50
Output : 3041409320171337804361260816606476884-
4377641568960512000000000000
The idea is to use simple school mathematics. We one by one multiply x with every digit of res[]. 
The important point to note here is digits are multiplied from rightmost digit to leftmost digit. 
If we store digits in same order in res[], then it becomes difficult to update res[] without extra space. 
That is why res[] is maintained in reverse way, i.e., digits from right to left are stored.

multiply(res[], x)
1) Initialize carry as 0.
2) Do following for i = 0 to res_size – 1
….a) Find value of res[i] * x + carry. Let this value be prod.
….b) Update res[i] by storing last digit of prod in it.
….c) Update carry by storing remaining digits in carry.
3) Put all digits of carry in res[] and increase res_size by number of digits in carry.
*/
int calcFact(int number, std::vector<long long>& factorial, int size)
{
	int carry = 0;
	int result = 0;

	for (int Index = 0; Index < size; Index++)
	{
		result = factorial[Index] * number + carry;
		factorial[Index] = result % 10;
		carry = result / 10;
	}

	while (carry)
	{
		factorial[size] = carry % 10;
		carry = carry / 10;
		size++;
	}
	return size;
}

std::vector<long long> findFactorialofLargeNum(int number, long long outSize)
{
	std::vector<long long> factorial;
	if (outSize > 0)
	{
		factorial.resize(outSize, 0);
		factorial[0] = 1;
		int size = 1;

		for (int nIndex = 2; nIndex <= number; nIndex++)
		{
			size = calcFact(nIndex, factorial, size);

		}

		int zeroCount = 0;
		for (int Index = size - 1; Index >= 0; Index--)
		{
			if (factorial[Index] == 0)
			{
				zeroCount++;
			}
			cout << factorial[Index];
		}

		cout << "Count of Zeros : " << zeroCount;
	}
	return factorial;
}

/*
Given an integer n, write a function that returns count of trailing zeroes in n!.

Examples :

Input: n = 5
Output: 1
Factorial of 5 is 120 which has one trailing 0.

Input: n = 20
Output: 4
Factorial of 20 is 2432902008176640000 which has
4 trailing zeroes.

Input: n = 100
Output: 24
*/
int countTrailingZerosOfFactorial(int number)
{
	int zeroCount = 0;
	int Index = 5;
	int num = number / Index;
	while (num > 0)
	{
		zeroCount += num;
		Index *= 5;
		num = (number / Index);
	}
	return zeroCount;
}


/*
Given an array of non negative numbers and a total, is there subset of numbers in this array which adds up to given total.

Arr - [2, 3, 7, 8, 10] sum - 11
ans - [8, 3]


* Time complexity - O(input.size * total_sum)
* Space complexity - O(input.size*total_sum)
*/
bool findSubSetSum(vector<int> inputArray, int Sum)
{
	int Size = inputArray.size();
	if (Size > 0)
	{
		vector<vector<bool>> DPTable(Size + 1, vector<bool>(Sum + 1, false));

		int rowSize = Size + 1;
		int colSize = Sum + 1;

		for (int rowIndex = 0; rowIndex < rowSize; rowIndex++)
		{
			for (int colIndex = 0; colIndex < colSize; colIndex++)
			{
				//base case with '0' value to make '0' sum.
				if (rowIndex == 0 && colIndex == 0)
				{
					DPTable[rowIndex][colIndex] = true;
				}
				else if (rowIndex != 0)
				{
					if (inputArray[rowIndex - 1] > colIndex)
					{
						DPTable[rowIndex][colIndex] = DPTable[rowIndex - 1][colIndex];
					}
					else
					{
						DPTable[rowIndex][colIndex] = DPTable[rowIndex - 1][colIndex] ||
													  DPTable[rowIndex - 1][colIndex - inputArray[rowIndex - 1]];
					}
				}
			}
		}

		//print subset
		if (DPTable[rowSize - 1][colSize - 1])
		{
			int colIndex = colSize - 1;
			int rowIndex = rowSize - 1;
			while (colIndex > 0 && rowIndex >= 0)
			{
				if (DPTable[rowIndex - 1][colIndex] == false)
				{
					cout << inputArray[rowIndex - 1]<<" ";
					colIndex = colIndex - inputArray[rowIndex - 1];
				}
				else
				{
					rowIndex--;
				}
			}
		}
		return DPTable[rowSize - 1][colSize - 1];
	}

	return false;
}

/*
Partition problem is to determine whether a given set can be partitioned into two 
subsets such that the sum of elements in both subsets is same.

Examples

arr[] = {1, 5, 11, 5}
Output: true
The array can be partitioned as {1, 5, 5} and {11}

arr[] = {1, 5, 3}
Output: false
The array cannot be partitioned into equal sum sets.
*/
bool findPartitionedSubSetsWithEqualSum(vector<int> inputArray)
{
	int Size = inputArray.size();
	if (Size > 0)
	{
		int Sum = 0;
		for (int Index = 0; Index < Size; Index++)
		{
			Sum += inputArray[Index];
		}

		if (Sum % 2 != 0)
		{
			return false;
		}

		Sum = Sum / 2;

		vector<vector<bool>> DPTable(Size + 1, vector<bool>(Sum + 1, false));

		int rowSize = Size + 1;
		int colSize = Sum + 1;

		for (int rowIndex = 0; rowIndex < rowSize; rowIndex++)
		{
			for (int colIndex = 0; colIndex < colSize; colIndex++)
			{
				//base case with '0' value to make '0' sum.
				if (rowIndex == 0 && colIndex == 0)
				{
					DPTable[rowIndex][colIndex] = true;
				}
				else if (rowIndex != 0)
				{
					if (inputArray[rowIndex - 1] > colIndex)
					{
						DPTable[rowIndex][colIndex] = DPTable[rowIndex - 1][colIndex];
					}
					else
					{
						DPTable[rowIndex][colIndex] = DPTable[rowIndex - 1][colIndex] ||
							DPTable[rowIndex - 1][colIndex - inputArray[rowIndex - 1]];
					}
				}
			}
		}

		//print subsets with equa sum
		if (DPTable[rowSize - 1][colSize - 1])
		{
			int colIndex = colSize - 1;
			int rowIndex = rowSize - 1;
			vector<int> firstSet;
			cout << "First set :" << endl;
			while (colIndex > 0 && rowIndex >= 0)
			{
				if (DPTable[rowIndex - 1][colIndex] == false)
				{
					cout << inputArray[rowIndex - 1] << " ";
					firstSet.push_back(inputArray[rowIndex - 1]);
					colIndex = colIndex - inputArray[rowIndex - 1];
				}
				else
				{
					rowIndex--;
				}
			}
			cout << endl <<"Second set :" << endl;

			for (int Index = 0; Index < Size; Index++)
			{
				if (std::find(firstSet.begin(), firstSet.end(), inputArray[Index]) == firstSet.end())
				{
					cout << inputArray[Index] << " ";
				}
			}

		}
		return DPTable[rowSize - 1][colSize - 1];
	}

	return false;
}

/*
Write a function to parse the full qualified name of a directory from examples below
C:\a\b\c\d\edsfdsf dfssdf\..\f\..\g\.\.\..\h  -> C:\a\b\c\d\h
..\C:\a\b\c\d\e\..\f\..\g\.\.\..\h
.\C:\a\b\c\d\e\..\f\..\g\.\.\..h

C:\a\b\c\d\h
"C:\\a\\b\\ff"
*/
std::string validPath(std::string strDirectPath)
{
	stack<string> PathStack;
	//vector<string> PathStack;
	int length = strDirectPath.length();

	int start = 0;
	string temp;
	for (int Index = 0; Index < length; Index++)
	{
		if (strDirectPath[Index] == '\\')
		{
			if ((Index - start) > 0)
			{
				temp = strDirectPath.substr(start, (Index - start) + 1);
			}
			else
			{
				temp = "";
			}
			if (temp == "..\\")
			{
				if (!PathStack.empty())
				{
					PathStack.pop();
					//PathStack.pop_back();
				}
			}
			else if ((temp != ".\\") && (!temp.empty()))
			{
				if (PathStack.empty())
				{
					if (temp.find(":") == std::string::npos)
					{
						start = Index + 1;
						continue;
					}
				}
				PathStack.push(temp);
				//PathStack.push_back(temp);
			}
			start = Index + 1;
		}
	}

	if ((length - start) > 0)
	{
		//PathStack.push_back(strDirectPath.substr(start, (length - start)));
		PathStack.push(strDirectPath.substr(start, (length - start)));
	}
	temp = "";
	/*stack<string> tmpStack;
	while(!PathStack.empty())
	{
		tmpStack.push(PathStack.top());
		PathStack.pop();
	}*/
	int size = PathStack.size();
	start = 0;
	//while (!tmpStack.empty())
	while (start < size)
	{
		temp = PathStack.top() + temp;
		PathStack.pop();
		start++;
		//temp += PathStack[start++];
	}

	if (temp[temp.size() - 1] == '\\')
	{
		temp.erase(temp.size() - 1, 1);
	}
	return temp;
}


/*
A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. 
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), 
write a program to output the skyline formed by these buildings collectively (Figure B).

Buildings  Skyline Contour
The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], 
where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively,
and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. 
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely 
defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, 
where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height.
Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. 
For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5
should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
*/

int getMaxHeight(const std::multiset<int>& HeightList)
{
	if (HeightList.empty())
	{
		return 0;
	}
	return *(HeightList.rbegin());
}

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings)
{
	vector<pair<int, int>> result;
	//multiset is needed to handle multiple buildings with same height.
	std::multiset<int> HeightList;

	vector<pair<int, int>> PointHeightPair;

	for (const auto& building : buildings)
	{
		//building[0] represents start point of building.
		//building[1] represents end point of building.
		//to identify start of building, keep height building[2] as positive
		//to identify end of building, keep height building[2] as negative
		PointHeightPair.emplace_back(building[0], building[2]);
		PointHeightPair.emplace_back(building[1], -building[2]);
	}

	//Sort PointHeightPair based on start and end points.
	//first compare by x that represents start and end points.
	//If they are same then use this logic
	//if two starts are compared then higher height building should be picked first
	// [0, 3, s], [0, 2, s], then take [0, 3, s] first
	//if two ends are compared then lower height building should be picked first
	// [5, 3, e], [5, 2, e], then [5, 2, e] first
	//if one start and end is compared then start should appear before end
	//[6, 2, s], [7, 2, e], [7, 3, s], [8, 3, e] -> [6, 2, s], [7, 3, s], [7, 2, e], [8, 3, e]

	sort(PointHeightPair.begin(), PointHeightPair.end(), [](const pair<int, int>& building1, const pair<int, int>& building2)
														 {
															 if (building1.first == building2.first)
															 {
																return building1.second > building2.second;
															 }
															 return building1.first < building2.first;
														 });
	int point = 0;
	bool isEntering = false;
	int height = 0;
	for (const auto& buildingEntry : PointHeightPair)
	{
		point = buildingEntry.first;
		height = abs(buildingEntry.second);
		isEntering = (buildingEntry.second > 0);

		if (isEntering)
		{
			if (height > getMaxHeight(HeightList))
			{
				result.emplace_back(point, height);
			}
			HeightList.insert(height);
		}
		else
		{
			//equal range will return lower bound and upper bound of same value in multi set. ie> first returns lowerbound
			//ie it will erase and lower bound and merge bildings like [2,0], [5,0] -> [5,0]
			HeightList.erase(HeightList.equal_range(height).first);
			if (height > getMaxHeight(HeightList))
			{
				result.emplace_back(point, getMaxHeight(HeightList));
			}
		}
	}

	return result;
}

/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.
*/
int largestRectangleArea(vector<int>& heights) 
{
	int Size = heights.size();
	int area = 0;
	int maxArea = -1;
	int Index = 0;
	stack<int> HistogramIndexStack;
	int top = 0;
	for (Index = 0; Index < Size;)
	{
		if (HistogramIndexStack.empty() || heights[Index] >= heights[HistogramIndexStack.top()])
		{
			HistogramIndexStack.push(Index++);
		}
		else
		{
			top = HistogramIndexStack.top();
			HistogramIndexStack.pop();
			//if stack is empty means everything till Index has to be
			//greater or equal to heights[top] so get area by heights[top] * Index;
			if (HistogramIndexStack.empty())
			{
				area = heights[top] * Index;
			}
			else
			{
				//if stack is not empty then everything from Index-1 to stack.top() + 1
				//has to be greater or equal to heights[top]
				//so area = heights[top]*(Index - stack.top - 1);
				area = heights[top] * (Index - HistogramIndexStack.top() - 1);
			}
			maxArea = max(area, maxArea);
		}
	}

	while (!HistogramIndexStack.empty())
	{
		top = HistogramIndexStack.top();
		HistogramIndexStack.pop();
		if (HistogramIndexStack.empty())
		{
			area = heights[top] * Index;
		}
		else
		{
			area = heights[top] * (Index - HistogramIndexStack.top() - 1);
		}
		maxArea = max(area, maxArea);
	}

	return maxArea;
}

/*
find maximum sum of subsequence of non-adjacent elements in an array

4, 1, 1, 4, 2, 1 -> 4 + 4 + 1 = 9
2, 5, 3, 1 ,7 -> 5 + 7 = 12
*/

int findMaxSumSubSeqNonAdjElmnts(vector<int> InputArray)
{
	int Size = InputArray.size();
	int maxSum = 0;
	int temp = 0;
	int inclucive = 0;
	int exclusive = 0;

	for (int Index = 0; Index < Size; Index++)
	{
		temp = inclucive;
		inclucive = max(InputArray[Index] + exclusive, inclucive);
		exclusive = temp;
	}

	maxSum = max(inclucive, exclusive);
	return maxSum;
}
	

/**
* Find maximum subsquare in a matrix made up of Xs and Os such that all four sides of subsquare are Xs.
It does not matter what is inside the subsquare. All 4 sides should be made up entirely of Xs
*
* e.g
* 0 0 0 0 0 X         0,0  0,0  0,0  0,0  0,0  1,1
* 0 X 0 X X X         0,0  1,1  0,0  1,1  1,2  2,3
* 0 X 0 X 0 X         0,0  2,1  0,0  2,1  0,0  3,1
* 0 X X X X X         0,0  3,1  1,2  3,3  1,4  4,5
* 0 0 0 0 0 0         0,0  0,0  0,0  0,0  0,0  0,0
*
* Output of above program should be 3
*
* Solution
* Have another matrix which is capable of holding 2 values hori and ver.
* Ver stores how far vertically you can see Xs. Hori stores how far horizontally you can see Xs.
* Once this matrix is build look for biggest subsquare by getting min of hori and ver at each point and checking
* if subsquare can be formed from value min to 1.
*
* Test cases:
* Matrix entirely made up of Xs
* Matrix entirely made up of Os
* Matrix with Xs and Os but maximum subsquare is length 1
*/

struct Cell
{
	int Horizontal;
	int Vertical;

	Cell() : Horizontal(0), Vertical(0)
	{}
};

int findMaxSubSquareSurroundedWithX(vector<vector<char>> InputMatrix)
{
	int RowSize = InputMatrix.size();
	int ColSize = 0;
	(RowSize > 0) ? ColSize = InputMatrix[0].size() : ColSize = 0;
	vector<vector<Cell>> DPTable(RowSize, vector<Cell>(ColSize));

	for (int RowIndex = 0; RowIndex < RowSize; RowIndex++)
	{
		for (int ColIndex = 0; ColIndex < ColSize; ColIndex++)
		{
			if (InputMatrix[RowIndex][ColIndex] == 'X')
			{
				if (RowIndex == 0 && ColIndex == 0)
				{
					DPTable[RowIndex][ColIndex].Horizontal = 1;
					DPTable[RowIndex][ColIndex].Vertical = 1;
				}
				else if (RowIndex == 0)
				{
					DPTable[RowIndex][ColIndex].Horizontal = DPTable[RowIndex][ColIndex - 1].Horizontal + 1;
					DPTable[RowIndex][ColIndex].Vertical = 1;
				}
				else if (ColIndex == 0)
				{
					DPTable[RowIndex][ColIndex].Horizontal = 1;
					DPTable[RowIndex][ColIndex].Vertical = DPTable[RowIndex - 1][ColIndex].Vertical + 1;
				}
				else
				{
					DPTable[RowIndex][ColIndex].Horizontal = DPTable[RowIndex][ColIndex - 1].Horizontal + 1;
					DPTable[RowIndex][ColIndex].Vertical = DPTable[RowIndex - 1][ColIndex].Vertical + 1;
				}
			}
		}
	}

	//start iterating from bottom right corner and find min of hori or ver at every cell.
	//If this is greater than 1 then see if you can find a number between this min and 1
	//such that on left's ver and top's hori is greater greater than or equal to minIndex.

	int maxSquare = 0;
	int minVal = 0;
	int minIndex = 0;
	for (int RowIndex = RowSize - 1; RowIndex >= 0; RowIndex--)
	{
		for (int ColIndex = ColSize - 1; ColIndex >= 0; ColIndex--)
		{
			minVal = min(DPTable[RowIndex][ColIndex].Horizontal, DPTable[RowIndex][ColIndex].Vertical);
			if (minVal > maxSquare && minVal > 0)
			{
				for (minIndex = minVal; minIndex > 0 && minIndex > maxSquare; minIndex--)
				{
					if (DPTable[RowIndex][ColIndex - minIndex + 1].Vertical >= minIndex &&
						DPTable[RowIndex - minIndex + 1][ColIndex].Horizontal >= minIndex)
					{
						break;
					}
				}
				maxSquare = max(maxSquare, minIndex);
			}
		}
	}

	return maxSquare;
}

/*
Given a list of 100 songs on your cell phone, find a way for each user to hear the songs without repeating songs,
you need to use an algorithm that uses shuffle for songs
*/
void playSongs(vector<int> PlayList)
{
	int SongToPlay = PlayList.size();
	int selectedSong = 0;
	while (SongToPlay > 0)
	{
		//selectedSong gets range between 1 and SongToPlay.-> ex: 1 - 100
		selectedSong = rand() % SongToPlay + 1;
		swap(PlayList[selectedSong - 1], PlayList[SongToPlay - 1]);
		cout << PlayList[SongToPlay - 1] << "->";
		SongToPlay--;
	}
}


/*
Print strem of characters in MS word format
1. Left align - 5 chars
2. Right allign - 75 chars
3. Start of paragraph - 5 space from left margin
4. Do not end line with half word.
5. Distribute spaces uniformly in between words, if the end of line is not enough to hold one word fully.
6. Last line of paragraph should not be aligned with spaces, if there is extra space to meet 70 chars.
*/
void print(const vector<string>& wordsList, int numOfEmptyChars)
{
	int numOfWords = wordsList.size();
	int numOfWordsUsed = numOfWords - 1;
	string lastWord = wordsList[numOfWords - 1];
	if (lastWord[lastWord.length() - 1] == ' ')
	{
		numOfEmptyChars++;
	}
	string strLine;
	for (int Index = 0; Index < numOfWords; Index++)
	{
		strLine += wordsList[Index];
		if (numOfEmptyChars > 0 && Index != (numOfWords - 1))
		{
			if (numOfEmptyChars < numOfWordsUsed)
			{
				strLine += " ";
			}
			else
			{
				for (int zeroIndex = 0; zeroIndex < (numOfEmptyChars / numOfWordsUsed); zeroIndex++)
				{
					strLine += " ";
				}
			}
			numOfEmptyChars--;
			numOfWordsUsed--;
		}
		else if (Index == numOfWords - 1)
		{
			if (strLine[strLine.length() - 1] == ' ')
			{
				strLine.erase(strLine.end() - 1);
			}
		}
	}
	cout << "Length "<<strLine.length() << std::endl;
	cout << strLine << std::endl;
}

void formatCharStream(string charStream)
{
	int charIndex = 0;
	int wordIndex = charIndex;
	int lineLength = 5;
	vector<string> wordsList{"     "};

	while (charStream[charIndex])
	{
		if (charStream[charIndex] == ' ')
		{
			wordsList.push_back(charStream.substr(wordIndex, (charIndex - wordIndex) + 1));
			lineLength += (charIndex - wordIndex) + 1;
			//add space char also ie + 1.
			wordIndex = charIndex + 1;
		}

		//since index starts with 0 and fisrt line should start with 5 space, add current space also -> 5 + 1 + 1 - add 7.
		if ((charIndex + 6) % 20 == 0)
		{
			print(wordsList, 20 - lineLength);
			wordsList.clear();
			lineLength = 0;
		}
		charIndex++;
	}
	if (charIndex != wordIndex)
	{
		wordsList.push_back(charStream.substr(wordIndex, (charIndex - wordIndex)));
		print(wordsList, 0);
	}
}

/*
Find a subsequence in given array in which the subsequence's elements are
in sorted order, lowest to highest, and in which the subsequence is as long as possible
Input  : arr[] = {3, 10, 2, 1, 20}
Output : Length of LIS = 3
The longest increasing subsequence is 3, 10, 20

Input  : arr[] = {3, 2}
Output : Length of LIS = 1
The longest increasing subsequences are {3} and {2}

Input : arr[] = {50, 3, 10, 7, 40, 80}
Output : Length of LIS = 4
The longest increasing subsequence is {3, 7, 40, 80}

Time complexity is O(n^2).
Space complexity is O(n)
*/

int longIncreasingSubSeq(vector<int> SeqArray)
{
	int seqSize = SeqArray.size();
	if (seqSize <= 1)
	{
		return seqSize;
	}

	vector<int> resultArray(seqSize, 1);
	vector<int> IncreasingSeq(seqSize, 0);

	for (int currIndex = 1; currIndex < seqSize; currIndex++)
	{
		IncreasingSeq[currIndex] = currIndex;
		for (int IndexFromStartTo_currIndex = 0; IndexFromStartTo_currIndex < currIndex; IndexFromStartTo_currIndex++)
		{
			if (SeqArray[currIndex] >= SeqArray[IndexFromStartTo_currIndex])
			{
				if (resultArray[currIndex] < resultArray[IndexFromStartTo_currIndex] + 1)
				{
					resultArray[currIndex] = resultArray[IndexFromStartTo_currIndex] + 1;
					//set the IncreasingSeq to point to guy before me
					//ex 7 3 1 5 6
					//   1 1 1 1 1 -> 1 1 2 1 1 -> 1 1 2 3 1 -> 1 1 2 3 4
					//   0 1 2 3 4 -> 0 1 1 3 4 -> 0 1 1 2 4 -> 0 1 1 2 3
					IncreasingSeq[currIndex] = IndexFromStartTo_currIndex;
				}
			}
		}
	}

	int maxIndex = 0;
	for (int Index = 0; Index < seqSize; Index++)
	{
		if (resultArray[Index] > resultArray[maxIndex])
		{
			maxIndex = Index;
		}
	}

	int tmpIndex = 0;
	int nextIndex = maxIndex;

	while (tmpIndex != nextIndex)
	{
		tmpIndex = nextIndex;
		cout << SeqArray[tmpIndex] << " ";
		nextIndex = IncreasingSeq[tmpIndex];
	}
	return resultArray[maxIndex];
}


/*
* Returns index in Table array for ceiling of s
*/
int findCeilIndex(const vector<int>& SeqArray, const vector<int>& IncTable, int end, int valueToBeInserted)
{
	int start = 0;
	int middle = 0;
	int len = end;
	while (start <= end)
	{
		middle = (start + end) / 2;
		if (middle < len && SeqArray[IncTable[middle]] < valueToBeInserted && valueToBeInserted <= SeqArray[IncTable[middle + 1]])
		{
			return middle + 1;
		}
		else if (SeqArray[IncTable[middle]] < valueToBeInserted)
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return -1;
}

/*
Find a subsequence in given array in which the subsequence's elements are
in sorted order, lowest to highest, and in which the subsequence is as long as possible
Input  : arr[] = {3, 10, 2, 1, 20}
Output : Length of LIS = 3
The longest increasing subsequence is 3, 10, 20

Input  : arr[] = {3, 2}
Output : Length of LIS = 1
The longest increasing subsequences are {3} and {2}

Input : arr[] = {50, 3, 10, 7, 40, 80}
Output : Length of LIS = 4
The longest increasing subsequence is {3, 7, 40, 80}

Time complexity is O(nlogn).
Space complexity is O(n)
*/

int longIncreasngSubSeq(vector<int> SeqArray)
{
	int seqSize = SeqArray.size();
	if (seqSize <= 1)
	{
		return seqSize;
	}

	vector<int> IncTable(seqSize, -1);
	vector<int> ResultArray(seqSize, -1);
	int LengthOfIncSubSeq = 0;

	for (int Index = 0; Index < seqSize; Index++)
	{
		//if index == 0, then add that index to table array.
		if (Index == 0)
		{
			IncTable[LengthOfIncSubSeq] = Index;
		}
		//check whether value of current index is greater than max value in table array(max vaue is last updated index in table array)
		else if (SeqArray[Index] > SeqArray[IncTable[LengthOfIncSubSeq]])
		{
			LengthOfIncSubSeq++;
			IncTable[LengthOfIncSubSeq] = Index;
			ResultArray[Index] = IncTable[LengthOfIncSubSeq - 1];
		}
		//check whether current index value is less than min vale(min value is 0th index in table array)
		else if (SeqArray[Index] < SeqArray[IncTable[0]])
		{
			IncTable[0] = Index;
		}
		//other wise value lies between min and max, update the correct index
		else
		{
			int tmpLen = 0;
			//find position of the value to be inserted
			/*while (tmpLen <= LengthOfIncSubSeq)
			{
				if (SeqArray[Index] > SeqArray[IncTable[tmpLen]])
				{
					tmpLen++;
				}
				else
				{
					IncTable[tmpLen] = Index;
					ResultArray[Index] = IncTable[tmpLen - 1];
					break;
				}
			}*/
			//Do binary search
			int insertIndex = findCeilIndex(SeqArray, IncTable, LengthOfIncSubSeq, SeqArray[Index]);
			IncTable[insertIndex] = Index;
			ResultArray[Index] = IncTable[insertIndex - 1];
		}
	}

	//Print subseq
	int tmpIndex = IncTable[LengthOfIncSubSeq];
	while (tmpIndex != -1)
	{
		cout << SeqArray[tmpIndex] << " ";
		tmpIndex = ResultArray[tmpIndex];
	}

	//Length starts with '0' so return + 1.
	return LengthOfIncSubSeq + 1;
}

/*
find the element in the array have odd number of occurence
array have only one element with odd occurence
ex: [2, 3, 4, 2, 3, 5, 5] -> 4
*/
int findOddOccuredElement(vector<int> ArrOfElem)
{
	int size = ArrOfElem.size();
	unordered_set<int> oddElementList;
	for (int Index = 0; Index < size; Index++)
	{
		if (oddElementList.find(ArrOfElem[Index]) != oddElementList.end())
		{
			oddElementList.erase(ArrOfElem[Index]);
		}
		else
		{
			oddElementList.insert(ArrOfElem[Index]);
		}
	}
	return *oddElementList.begin();
}

/*
Egg Dropping Puzzle
k ==> Number of floors
n ==> Number of Eggs
eggDrop(n, k) ==> Minimum number of trials needed to find the critical
floor in worst case.
eggDrop(n, k) = 1 + min{max(eggDrop(n - 1, x - 1), eggDrop(n, k - x)):
x in {1, 2, ..., k}}
*/
int findMinTriesToBreakEggFromFloor(int NumEggs, int NumFloors)
{
	//Allocate DP table with 1 extra row and colom, sice egg and floors starts with '1' and fill 0th row as'0' 
	vector<vector<int>> EggDP(NumEggs + 1, vector<int>(NumFloors + 1, 0));
	//Fill 1st row with '1' egg minimum tries in all floors
	for (int floorIndex = 1; floorIndex <= NumFloors; floorIndex++)
	{
		EggDP[1][floorIndex] = floorIndex;
	}

	//Start filling from 2nd row means with "More than 1 egg"
	int minTry = 0;
	for (int eggIndex = 2; eggIndex <= NumEggs; eggIndex++)
	{
		for (int floorIndex = 1; floorIndex <= NumFloors; floorIndex++)
		{
			//assign cell with max value, since during calculation will find the min of all tries.
			EggDP[eggIndex][floorIndex] = INT_MAX;
			//iterate from 1st floor to floorIndex floor to find min tries
			for (int currFloorIndex = 1; currFloorIndex <= floorIndex; currFloorIndex++)
			{
				//Ex : floors -> 1 2 3
				//				 1 + max(0, 2) -> 0 -> egg drop from 1st floor and it breaks. 
				//									   if it doesnt breaks 2 floors and 1 egg, that is already calculates as '2'.
				//               1 + max(1, 1) -> 1 -> egg drop at 2nd floor and breaks, so prev 1 egg on 1 floor.
				//									   if it doesnt break 1 egg on 3rd floor is pending.
				//for each floor calculate current one and max of floors
				minTry = 1 + max(EggDP[eggIndex - 1][currFloorIndex - 1], EggDP[eggIndex][floorIndex - currFloorIndex]);
				if (minTry < EggDP[eggIndex][floorIndex])
				{
					EggDP[eggIndex][floorIndex] = minTry;
				}
			}
		}
	}

	return EggDP[NumEggs][NumFloors];
}