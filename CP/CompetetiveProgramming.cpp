// TrieTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "CompetetiveProgramming.h"
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <algorithm>
#include <cctype>
#include "LinkedList.h"
#include "BinaryTree.h"
#include "Stock.h"
#include "PriorityQueue.h"
#include "Sorting.h"
//#include "Matrices.h"
#include "BitOperations.h"
#include "Misc.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;



struct RecPoint
{
	int x;
	int y;
	RecPoint::RecPoint()
	{
		x = 0;
		y = 0;
	}

	RecPoint::RecPoint(int xP, int yP)
	{
		x = xP;
		y = yP;
	}
};

class TrieTreeNode
{
public:
	TrieTreeNode();
	~TrieTreeNode();
	void insertWord(char* pWord);
	void displayWords(TrieTreeNode* pTreeNode, vector<char> LetterList, vector<string>& WordsList);
	bool searchWord(char* pWord);
	bool deleteWord(TrieTreeNode* pTreeNode, char* pWord, bool& bDeleted);
	bool hasChildNode(TrieTreeNode* pTreeNode);
	vector<string> matchWordsFromPrefix(char* pPrefix);

private:
	TrieTreeNode* m_pParent;
	std::map<char, TrieTreeNode*> m_ChildList;
	unsigned int m_nWordOccurence;
};

TrieTreeNode::TrieTreeNode()
{
	//for (int nIndex = 0; nIndex < 26; ++nIndex)
	//		m_pChild[nIndex] = NULL;
	m_pParent = NULL;
	m_nWordOccurence = 0;
}

TrieTreeNode::~TrieTreeNode()
{
	//delete[] m_pChild;
	for (const auto& TreeNode : m_ChildList)
	{
		delete TreeNode.second;
	}
	//delete m_pParent;
}

void TrieTreeNode::insertWord(char* pWord)
{
	TrieTreeNode* pTempRootNode = this;
	while (*pWord != '\0')
	{
		if (pTempRootNode->m_ChildList.end() == pTempRootNode->m_ChildList.find(*pWord))
		{
			pTempRootNode->m_ChildList[*pWord] = new TrieTreeNode();
			//pTempRootNode->m_ChildList[*pWord]->m_pParent = pTempRootNode;
		}
		pTempRootNode = pTempRootNode->m_ChildList[*pWord];
		++pWord;
	}
	pTempRootNode->m_nWordOccurence++;
}

vector<string> TrieTreeNode::matchWordsFromPrefix(char* pPrefix)
{
	vector<string> matchWordsList;
	vector<char> Word;
	TrieTreeNode* pTempRootNode = this;
	while (*pPrefix != '\0')
	{
		if (pTempRootNode->m_ChildList.end() != pTempRootNode->m_ChildList.find(*pPrefix))
		{
			pTempRootNode = pTempRootNode->m_ChildList[*pPrefix];
			Word.push_back(*pPrefix);
			pPrefix++;
		}
		else
		{
			return matchWordsList;
		}
	}
	displayWords(pTempRootNode, Word, matchWordsList);
	return matchWordsList;
}

bool TrieTreeNode::searchWord(char* pWord)
{
	string strWord(pWord);
	TrieTreeNode* pTempRootNode = this;
	while (*pWord != '\0')
	{
		if (pTempRootNode->m_ChildList.end() != pTempRootNode->m_ChildList.find(*pWord))
		{
			pTempRootNode = pTempRootNode->m_ChildList[*pWord];
			pWord++;
		}
		else
		{
			break;
		}
	}

	if (pTempRootNode->m_nWordOccurence > 0)
	{
		cout << "Word " <<strWord.c_str()<<" found \n";
		return true;
	}
	else
	{
		cout << "Word " << strWord.c_str() << " not found \n";
		return false;
	}
}

bool TrieTreeNode::hasChildNode(TrieTreeNode* pTreeNode)
{
	bool bChildNode = false;
	for (const auto& TreeNode : pTreeNode->m_ChildList)
	{
		if (TreeNode.second)
		{
			bChildNode = true;
			break;
		}
	}
	return bChildNode;
}

bool TrieTreeNode::deleteWord(TrieTreeNode* pTreeNode, char* pWord, bool& bDeleted)
{
	if ((pTreeNode) && (pTreeNode->m_nWordOccurence > 0) && (*pWord == '\0'))
	{
		pTreeNode->m_nWordOccurence--;
		bDeleted = true;
		return (!hasChildNode(pTreeNode));
	}
	while (*pWord != '\0')
	{
		if (pTreeNode->m_ChildList.end() != pTreeNode->m_ChildList.find(*pWord))
		{
			TrieTreeNode* pTempRootNode = pTreeNode->m_ChildList[*pWord];
			pWord++;
			if (deleteWord(pTempRootNode, pWord, bDeleted))
			{
				char letterToDelete = *(pWord-1);
				delete pTreeNode->m_ChildList[letterToDelete];
				pTreeNode->m_ChildList.erase(pTreeNode->m_ChildList.find(letterToDelete));
				return((pTreeNode->m_nWordOccurence == 0) && (!hasChildNode(pTreeNode)));
			}
			return false;
		}
		else
		{
			cout << "Word not found \n";
			return false;
		}
	}
	return false;
}

void TrieTreeNode::displayWords(TrieTreeNode* pTreeNode, vector<char> LetterList, vector<string>& WordsList)
{
	if ((pTreeNode) && (pTreeNode->m_nWordOccurence > 0))
	{ 
		/*std::for_each(LetterList.begin(), LetterList.end(),
			[](char letter)
		{
			cout << letter;
		}
		);*/
		WordsList.push_back(string(LetterList.begin(), LetterList.end()));
		cout << WordsList.front().c_str()<<"->";
	}

	for (const auto& TreeNode : pTreeNode->m_ChildList)
	{
		LetterList.push_back(TreeNode.first);
		displayWords(TreeNode.second, LetterList, WordsList);
		LetterList.pop_back();
	}
}

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node1 {
public:
	Node1()
	{
		terminal_ = false;
	}
	~Node1()
	{
		for (auto it = children_.begin(); it != children_.end(); ++it) {
			delete it->second;
		}
		children_.clear();
	}
	Node1 *AddChild(char c)
	{
		Node1 *n = Child(c);
		if (n == NULL) {
			n = new Node1();
			children_[c] = n;
		}
		return n;
	}
	Node1 *Child(char c)
	{
		auto it = children_.find(c);
		return it == children_.end() ? NULL : it->second;
	}

	bool terminal_;

private:
	unordered_map<char, Node1 *> children_;
};

class Trie {
public:
	void Add(string const &s)
	{
		Node1 *n = &root_;
		for (char c : s) {
			n = n->AddChild(c);
		}
		n->terminal_ = true;
	}
	Node1 *Root()
	{
		return &root_;
	}

private:
	Node1 root_;
};

int Count(Trie &trie, string const &s, vector<int> &memo, int idx = 0)
{
	if (idx < 0 ||
		idx > s.size())
	{
		return 0;
	}
	if (idx == s.size()) {
		return (idx == 0) ? 0 : 1;
	}

	if (memo.size() < s.size()) {
		memo.resize(s.size(), -1);
	}
	if (memo[idx] != -1) {
		return memo[idx];
	}

	int count = 0;
	Node1 *n = trie.Root();
	for (int i = idx; i < s.size(); ++i) 
	{
		n = n->Child(s[i]);
		if (!n) 
		{
			break;
		}
		if (n->terminal_) 
		{
			count += Count(trie, s, memo, i + 1);
		}
	}

	memo[idx] = count;
	return memo[idx];
}

string intToStr(int num)
{
	string strNum;
	while (num > 0)
	{
		strNum += (num % 10) +'0';
		num = num / 10;
	}

	return strNum;
}

/*
Implement atoi which converts a string to an integer.
The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, 
and interprets them as a numerical value.
The string can contain additional characters after those that form the integral number, 
which are ignored and have no effect on the behavior of this function.
If the first sequence of non-whitespace characters in str is not a valid integral number, 
or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
If no valid conversion could be performed, a zero value is returned.

Note:
Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
Example 1:
Input: "42"
Output: 42

Example 2:
Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
Then take as many numerical digits as possible, which gets 42.

Example 3:
Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:
Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical
digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:
Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
Thefore INT_MIN (−231) is returned.
*/
int stringToInt(string strNum)
{
	int num = 0;
	int eachDigit = 0;
	bool bNegative = false;
	for (int nIndex = 0; nIndex < strNum.length(); nIndex++)
	{
		if ((num == 0) && (strNum[nIndex] == ' '))
		{
			continue;
		}
		if ((num == 0) && (strNum[nIndex] == '-'))
		{
			bNegative = false;
		}
		else
		{
			eachDigit = strNum[nIndex] - '0';
			if ((eachDigit < 0 || eachDigit > 9))
			{
				break;
			}
		}

		if ((num > INT_MAX / 10 || (num == INT_MAX / 10)) || (num < INT_MIN / 10 || (num == INT_MIN / 10)))
		{
			if (bNegative)
			{
				num = INT_MIN;
			}
			else
			{
				num = INT_MAX;
			}
			break;
		}
		num = (num * 10) + eachDigit;
	}

	if (bNegative)
	{
		num = num * -1;
	}
	return num;
}

float stringToFloat(string strNum, int frac)
{
	float num = 0.0;
	int n =0, i = 0;
	for (int nIndex = 0; nIndex < strNum.length(); nIndex++)
	{
		if (strNum[nIndex] != '.')
		{
			i = strNum[nIndex] - '0';
			n = (n * 10) + i;
		}
	}

	num = floor(n / pow(10, frac));
	return num;
}

void ftoa(float n)
{
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - ipart;

	// convert integer part to string
	//int i = intToStr(ipart, res, 0);

	// check for display option after point
	//if (afterpoint != 0)
	{
		//res[i] = '.';  // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, 3);

		//intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

void swap(char& firstLetter, char& secondLetter)
{
	char temp;
	temp = firstLetter;
	firstLetter = secondLetter;
	secondLetter = temp;
}

/* 
Below are the permutations of string ABC.
ABC ACB BAC BCA CBA CAB
Note: permutation comes with all elements not partial like AB is not a permutation of ABC, but it is a combination.
Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permutation(string strWord, int nIndex, int nSize)
{
	if (nIndex == nSize)
		cout << strWord << "\t";
	else
	{
		for (int nStrIndex = nIndex; nStrIndex < strWord.length(); nStrIndex++)
		{
			swap(strWord[nIndex], strWord[nStrIndex]);
			permutation(strWord, nIndex + 1, nSize);
			swap(strWord[nIndex], strWord[nStrIndex]);
		}
	}
}

int power(int nBase, unsigned int nExponent)
{
	int temp;
	if (nExponent == 0)
	{
		return 1;
	}
	temp = power(nBase, nExponent / 2);
	if (nExponent % 2 == 0)
	{
		return temp*temp;
	}
	else
	{
		return nBase*temp*temp;
	}
}

void shuffle(int card[], int nSize)
{
	// Initialize seed randomly
	srand(time(0));

	for (int nIndex = 0; nIndex<nSize; nIndex++)
	{
		// Random for remaining positions.
		int randPos = rand();
		int newPos = (randPos % (nSize - nIndex));
		int randomIndex = nIndex + newPos;

		swap(card[nIndex], card[randomIndex]);
	}
}


struct Point
{
	int x;
	int y;
};

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	// for details of below formula.
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// A utility function to print a substring str[low..high]
void printSubStr(char* str, int low, int high)
{
	for (int i = low; i <= high; ++i)
		printf("%c", str[i]);
}

// This function prints the longest palindrome substring (LPS)
// of str[]. It also returns the length of the longest palindrome
int longestPalSubstr(char *str)
{
	int maxLength = 1;  // The result (length of LPS)

	int start = 0;
	int len = strlen(str);

	int low, high;

	// One by one consider every character as center point of 
	// even and length palindromes
	for (int i = 1; i < len; ++i)
	{
		// Find the longest even length palindrome with center points
		// as i-1 and i.  
		low = i - 1;
		high = i;
		while (low >= 0 && high < len && str[low] == str[high])
		{
			if (high - low + 1 > maxLength)
			{
				start = low;
				maxLength = high - low + 1;
			}
			--low;
			++high;
		}

		// Find the longest odd length palindrome with center 
		// point as i
		low = i - 1;
		high = i + 1;
		while (low >= 0 && high < len && str[low] == str[high])
		{
			if (high - low + 1 > maxLength)
			{
				start = low;
				maxLength = high - low + 1;
			}
			--low;
			++high;
		}
	}

	printf("Longest palindrome substring is: ");
	printSubStr(str, start, start + maxLength - 1);

	return maxLength;
}

/*
Longest palindrome subsequence

1. a d b b c a   -> a b b a (4)
2. p q r d r p d -> p r d r p (5)
3. p q r r q p   -> p q r r q p (6)

Dynamic programming
*/
int findLongestPalSubSequence(string strWord)
{
	int wordSize = strWord.length();
	int maxPalSize = 0;
	vector<vector<int>> PalMatrix(wordSize, vector<int>(wordSize, 0));

	//Fill the diagonal cells with '1' as value, bcoz each char itself is a palindrome
	for (int Index = 0; Index < wordSize; Index++)
	{
		PalMatrix[Index][Index] = 1;
	}

	//We need to fill values diagonally, like first find palindrome of 1 char, then 2 chars, 3 chars etc.
	int rowIndex = 0;
	int colIndex = 0;
	for (int charLength = 2; charLength <= wordSize; charLength++)
	{
		for (rowIndex = 0; rowIndex < wordSize - charLength + 1; rowIndex++)
		{
			colIndex = rowIndex + charLength - 1;
			/*if (strWord[rowIndex] == strWord[colIndex] && charLength == 2)
			{
				PalMatrix[rowIndex][colIndex] = 2;
			}*/
			//if characters matches then add diagonal value + 2.
			if (strWord[rowIndex] == strWord[colIndex])
			{
				PalMatrix[rowIndex][colIndex] = PalMatrix[rowIndex + 1][colIndex - 1] + 2;
			}
			else
			{
				PalMatrix[rowIndex][colIndex] = max(PalMatrix[rowIndex][colIndex - 1], PalMatrix[rowIndex + 1][colIndex]);
			}
		}
	}

	maxPalSize = PalMatrix[0][wordSize - 1];
	int tmpSize = maxPalSize;
	vector<char> PalString(tmpSize);
	int leftPtr = 0;
	int rightPtr = tmpSize - 1;
	rowIndex = 0;
	colIndex = wordSize - 1;
	while (leftPtr < rightPtr && rowIndex >= 0 && rowIndex < wordSize && colIndex >= 0 && colIndex < wordSize)
	{
		if (strWord[rowIndex] == strWord[colIndex])
		{
			PalString[leftPtr++] = strWord[rowIndex];
			PalString[rightPtr--] = strWord[rowIndex];
			rowIndex++;
			colIndex--;
		}
		else
		{
			if (PalMatrix[rowIndex][colIndex - 1] == PalMatrix[rowIndex][colIndex])
			{
				colIndex--;
			}
			else
			{
				rowIndex++;
			}
		}
	}

	return maxPalSize;
}

/*
Given two strings, find the length of longest subsequence present in both of them.
ABCDGH  ADH -> 3
AEDFHR

AGGTAB   GTAB -> 4
GXTXAYB
*/

int longestSubSequenceOfStrings(string strOne, string strTwo)
{
	int strOneLength = strOne.length();
	int strTwoLength = strTwo.length();
	int LengthOfLongestSubSeq = 0;

	//plus '1' is to fill 0th row and col with 0's
	//if strOne[i] != strTwo[j], then it should take the value from previous cell.
	//when iteration starts with 0th index of string previous cell will have 0.
	vector<vector<int>> SubSeqDP(strOneLength + 1, vector<int>(strTwoLength + 1, 0));
	int rowIndex = 0;
	int colIndex = 0;
	for (rowIndex = 0; rowIndex <= strOneLength; rowIndex++)
	{
		for (colIndex = 0; colIndex <= strTwoLength; colIndex++)
		{
			if (rowIndex == 0 || colIndex == 0)
			{
				//continue, already filled with 0.
				continue;
			}
			else if (strOne[rowIndex - 1] == strTwo[colIndex - 1])
			{
				SubSeqDP[rowIndex][colIndex] = SubSeqDP[rowIndex - 1][colIndex - 1] + 1;
			}
			else
			{
				SubSeqDP[rowIndex][colIndex] = max(SubSeqDP[rowIndex - 1][colIndex], SubSeqDP[rowIndex][colIndex - 1]);
			}
		}
	}

	LengthOfLongestSubSeq = SubSeqDP[strOneLength][strTwoLength];
	int tmpIndex = LengthOfLongestSubSeq - 1;
	rowIndex = strOneLength;
	colIndex = strTwoLength;
	vector<char> CommonSubSeq(LengthOfLongestSubSeq);
	while (rowIndex > 0 && colIndex > 0 && tmpIndex >= 0)
	{
		if (strOne[rowIndex - 1] == strTwo[colIndex - 1])
		{
			CommonSubSeq[tmpIndex--] = strOne[rowIndex - 1];
			rowIndex--;
			colIndex--;
		}
		else if (SubSeqDP[rowIndex - 1][colIndex] > SubSeqDP[rowIndex][colIndex - 1])
		{
			rowIndex--;
		}
		else
		{
			colIndex--;
		}
	}
	return LengthOfLongestSubSeq;
}


#define my_sizeof(type) (char *)(&type+1)-(char*)(&type)

struct GetSize
{
	int num;
	char nam;
	char* pl;
	char jj;
	void* p;
};

std::string removeSpaces(std::string sentence)
{
	int nIndex = 0;
	int jIndex = 0;
	while (sentence[nIndex])
	{
		if ((sentence[nIndex] != ' ') || (sentence[nIndex] == ' ' && sentence[nIndex + 1] != ' '))
		{
			sentence[jIndex] = sentence[nIndex];
			++jIndex;
		}
		nIndex++;
	}
	sentence.resize(jIndex);
	/* remove space at the end */
	if (sentence[jIndex - 1] == ' ')
		sentence.erase(sentence.end() - 1);
	/* remove space at the begin */
	if (sentence[0] == ' ')
		sentence.erase(sentence.begin());
	return sentence;
}

void Initialize(interval_map<int, char>& myMap, char first)
{
	myMap.initialize('A');
	myMap.assign(5, 10, 'B');
	myMap.assign(10, 15, 'C');
	myMap.assign(15, 20, 'D');
	myMap.assign(20, 25, 'E');
	myMap.assign(25, 30, 'F');
	myMap.assign(30, 35, 'G');

}

int segregate(int array[], int nSize)
{
	int nNewIndex = 0;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (array[nIndex] > 0)
		{
			swap(array[nIndex], array[nNewIndex]);
			nNewIndex++;
		}
	}
	return nNewIndex;
}

int findMissingSmallestInteger(int array[], int nSize)
{
	nSize = segregate(array, nSize);
	if (nSize == 0)
	{
		return 1;
	}
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		//take the value of in the index
		int arrayVal = abs(array[nIndex]);
		//since index starts from '0', check the value - 1 less than the size of array and 
		//array value in value - 1 index greater than '0', then make it -ve
		if ((arrayVal - 1) < nSize && array[(arrayVal - 1)] > 0)
		{
			array[(arrayVal - 1)] = -array[(arrayVal - 1)];
		}
	}

	for (int nJndex = 0; nJndex < nSize; nJndex++)
	{
		if (array[nJndex] > 0)
		{
			return nJndex + 1;
		}
	}
	return nSize + 1;
}


bool isArraySorted(int array[], int nSize)
{
	int nIndex;
	for (nIndex = 0; nIndex < nSize - 1; nIndex++)
	{
		if (array[nIndex] <= array[nIndex + 1])
		{
			continue;
		}
		else
		{
			break;
		}
	}
	if (nIndex == nSize - 1)
	{
		return true;
	}
	for (nIndex = 0; nIndex < nSize - 1; nIndex++)
	{
		if (array[nIndex] >= array[nIndex + 1])
		{
			continue;
		}
		else
		{
			break;
		}
	}
	if (nIndex == nSize - 1)
	{
		return true;
	}
	return false;
}

int convertBinaryToDecimal(long long n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder*pow(2, i);
		++i;
	}
	return decimalNumber;
}

long long convertDecimalToBinary(int n)
{
	long long binaryNumber = 0;
	int remainder, i = 1, step = 1;

	while (n != 0)
	{
		remainder = n % 2;
		cout << "Step " << step++ << ": " << n << "/2, Remainder = " << remainder << ", Quotient = " << n / 2 << endl;
		n /= 2;
		binaryNumber += remainder*i;
		i *= 10;
	}
	return binaryNumber;
}

unsigned int AddBinaryNumbers(unsigned int Number1, unsigned int Number2)
{
	unsigned int nCarry = 0;
	unsigned int nResult = 0;
	std::vector<unsigned int> BinaryResult;

	while (Number1 != 0 || Number2 != 0)
	{
		int n = ((Number1 % 10) + (Number2 % 10) + nCarry);
		BinaryResult.push_back((((Number1 % 10) + (Number2 % 10) + nCarry) % 2));
		nCarry = (((Number1 % 10) + (Number2 % 10) + nCarry) / 2);
		Number1 = Number1 / 10;
		Number2 = Number2 / 10;
	}

	if (nCarry != 0)
	{
		BinaryResult.push_back( nCarry );
	}

	for (auto iterator = BinaryResult.rbegin(); iterator != BinaryResult.rend(); ++iterator)
	{
		nResult = (nResult * 10) + *iterator;
	}
	return nResult;
}

std::string AddBinaryStrings(std::string binString1, std::string binString2)
{
	std::string strResult;
	int nSum = 0;
	int nBin1Length = binString1.size() - 1;
	int nBin2Length = binString2.size() - 1;

	while(nBin1Length >= 0 || nBin2Length >= 0 || nSum == 1)
	{
		// Comput sum of last digits and carry
		nSum += ((nBin1Length >= 0) ? binString1[nBin1Length] - '0' : 0);
		nSum += ((nBin2Length >= 0) ? binString2[nBin2Length] - '0' : 0);

		// If current digit sum is 1 or 3, add 1 to result
		strResult = char(nSum % 2 + '0') + strResult;

		// Compute carry
		nSum /= 2;

		// Move to next digits
		nBin1Length--;
		nBin2Length--;
	}

	return strResult;
}

unsigned int findMaxSquare(unsigned int inputMat[][5], unsigned int cacheMat[][5], int nLength, int nWidth)
{
	unsigned int nMax = 0;
	for (int nRowIndex = 0; nRowIndex < nLength; ++nRowIndex)
	{
		for (int nColomIndex = 0; nColomIndex < nWidth; ++nColomIndex)
		{
			if (nRowIndex == 0 || nColomIndex == 0)
			{
				cacheMat[nRowIndex][nColomIndex] = inputMat[nRowIndex][nColomIndex];
			}
			else if (inputMat[nRowIndex][nColomIndex] != 0)
			{
				unsigned int minValue = min(cacheMat[nRowIndex][nColomIndex - 1], min(cacheMat[nRowIndex - 1][nColomIndex], cacheMat[nRowIndex - 1][nColomIndex - 1]));
				cacheMat[nRowIndex][nColomIndex] = minValue + inputMat[nRowIndex][nColomIndex];
			}

			nMax = max(cacheMat[nRowIndex][nColomIndex], nMax);
		}
	}
	return nMax;
}

/*
Given a sequence of integers as an array, determine whether it is possible to obtain a strictly 
increasing sequence by removing no more than one element from the array.

Example
For sequence = [1, 3, 2, 1], the output should be almostIncreasingSequence(sequence) = false;
There is no one element in this array that can be removed in order to get a strictly increasing sequence.
For sequence = [1, 3, 2], the output should be almostIncreasingSequence(sequence) = true;
You can remove 3 from the array to get the strictly increasing sequence [1, 2].
Alternately, you can remove 2 to get the strictly increasing sequence [1, 3]
*/
bool checkAlmostIncreasingSequence(int seqArray[], int nLength)
{
	unsigned int remcount = 0;
	for (int nIndex = 1; nIndex < nLength; ++nIndex)
	{
		if (seqArray[nIndex] < seqArray[nIndex - 1])
		{
			++remcount;
			if (remcount > 1)
			{
				return false;
			}
			
			if ((nIndex >= 2) && ((nIndex + 1) <= (nLength - 1)))
			{
				//[1,2,1,2]
				if ((seqArray[nIndex] < seqArray[nIndex - 2]) && (seqArray[nIndex + 1] < seqArray[nIndex - 1]))
				{
					return false;
				}
			}
		}
	}
	return true;
}

/*
There are n stairs, a person standing at the bottom wants to reach the top. 
The person can climb either 1 stair or 2 stairs at a time. Count the number of ways, the person can reach the top.

Input: n = 1
Output: 1
There is only one way to climb 1 stair

Input: n = 2
Output: 2
There are two ways: (1, 1) and (2)

Input: n = 4
Output: 5
(1, 1, 1, 1), (1, 1, 2), (2, 1, 1), (1, 2, 1), (2, 2)
*/
unsigned int numwaysofsteps(unsigned int numofsteps)
{
	unsigned int numways = 0;
	if (numofsteps == 0 || numofsteps == 1)
	{
		numways = 1;
		return numways;
	}

	std::vector<unsigned int> nums(numofsteps + 1);
	nums[0] = 1;
	nums[1] = 1;
	for (unsigned int nIndex = 2; nIndex <= numofsteps; ++nIndex)
	{
		nums[nIndex] = nums[nIndex - 1] + nums[nIndex - 2];
	}
	return nums[numofsteps];
}

bool checkRectanglesOverlap(RecPoint rec1bottom, RecPoint rec1top, RecPoint rec2bottom, RecPoint rec2top)
{
	int xDist = (min(rec1top.x, rec2top.x)) - (max(rec1bottom.x, rec2bottom.x));
	int yDist = (min(rec1top.y, rec2top.y)) - (max(rec1bottom.y, rec2bottom.y));

	if (xDist <= 0 || yDist <= 0)
	{
		return false;
	}

	return true;
}

/*
Given an array, find the most frequent element in it. If there are multiple elements that appear maximum number of times,
print any one of them.

Examples:

Input : arr[] = {1, 3, 2, 1, 4, 1}
Output : 1
1 appears three times in array which
is maximum frequency.

Input : arr[] = {10, 20, 10, 20, 30, 20, 20}
Output : 20
*/
int mostFrequent(int sortedArr[], int nSize)
{
	// find the max frequency using linear traversal
	int max_count = 1;
	int result = sortedArr[0];
	int curr_count = 1;
	for (int nIndex = 1; nIndex < nSize; nIndex++) 
	{
		if (sortedArr[nIndex] == sortedArr[nIndex - 1])
		{
			curr_count++;
		}
		else 
		{
			if (curr_count > max_count) 
			{
				max_count = curr_count;
				result = sortedArr[nIndex - 1];
			}
			curr_count = 1;
		}
	}

	// If last element is most frequent
	if (curr_count > max_count)
	{
		max_count = curr_count;
		result = sortedArr[nSize - 1];
	}

	return result;
}

/*
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/
std::vector<std::queue<int>> mostKFrequent(int arr[], int nSize, int kTimes)
{
	std::vector<std::queue<int>> ResultList;
	std::unordered_map<int, int> freqMap;
	//create the output vector with size of input array + 1.
	//and insert elements againest frequency
	//[1, 1, 2, 3, 3, 4, 5]
	//[0,   1,       2,   3, 4, 5, 6, 7]
	//[0, [2,4,5], [1,3], 0, 0, 0, 0, 0]
	std::vector<std::queue<int>> IndexVec(nSize + 1);

	for (int nIndex = 0; nIndex < nSize; ++nIndex)
	{
		freqMap[arr[nIndex]]++;
	}

	for (auto freqMapIt = freqMap.begin(); freqMapIt != freqMap.end(); ++freqMapIt)
	{
		IndexVec[(*freqMapIt).second].push((*freqMapIt).first);
	}

	int nCount = 0;
	for (int nIndex = IndexVec.size() - 1; nIndex > 0, nCount < kTimes; --nIndex)
	{
		if (IndexVec[nIndex].size() > 0)
		{
			nCount = IndexVec[nIndex].size();
			ResultList.push_back(IndexVec[nIndex]);
		}
	}
	return ResultList;
}


// comparison function defined for the priority queue
class compare
{
public:
	bool operator()(pair<int, int> p1, pair<int, int> p2)
	{
		// if frequencies of two elements are same
		// then the larger number should come first
		if (p1.second == p2.second)
			return p1.first < p2.first;

		// insert elements in the priority queue on the basis of
		// decreasing order of frequencies    
		return p1.second < p2.second;
	}
};

// funnction to print the k numbers with most occurrences
void print_N_mostFrequentNumber(int arr[], int nSize, int kTimes)
{
	unordered_map<int, int> freqMap;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		freqMap[arr[nIndex]]++;
	}

	// priority queue 'freqArrQue' implemented as max heap on the basis
	// of the comparison operator 'compare'
	// element with the highest frequency is the root of 'freqArrQue'
	// in case of conflicts, larger element is the root
	priority_queue<pair<int, int>, vector<pair<int, int> >, compare> freqArrQue(freqMap.begin(), freqMap.end());

	// display the the top k numbers
	cout << kTimes << " numbers with most occurrences are:\n";
	for (int nindex = 1; nindex <= kTimes; nindex++)
	{
		cout << freqArrQue.top().first << " ";
		freqArrQue.pop();
	}
}

/*
Given an array of integers, and a number ‘sum’, find the number of pairs of integers in the array whose sum is equal to ‘sum’.

Examples:
Input  :  arr[] = {1, 5, 7, -1},
sum = 6
Output :  2
Pairs with sum 6 are (1, 5) and (7, -1)

Input  :  arr[] = {1, 5, 7, -1, 5},
sum = 6
Output :  3
Pairs with sum 6 are (1, 5), (7, -1) &
(1, 5)

Input  :  arr[] = {1, 1, 1, 1},
sum = 2
Output :  6
There are 3! pairs with sum 2.

Input  :  arr[] = {10, 12, 10, 15, -1, 7, 6,
5, 4, 2, 1, 1, 1},
sum = 11
Output :  9
*/
std::vector<pair<int, int>> findPairThatHasSum(int sortedArr[], int nSize, int nSum)
{
	std::vector<pair<int, int>> ResultSet;
	int nStart = 0;
	int nEnd = nSize - 1;

	while (nStart < nEnd)
	{
		if (sortedArr[nStart] + sortedArr[nEnd] == nSum)
		{
			ResultSet.push_back(std::make_pair(sortedArr[nStart], sortedArr[nEnd]));
			nStart++;
			nEnd--;
		}
		else if (sortedArr[nStart] + sortedArr[nEnd] < nSum)
		{
			nStart++;
		}
		else
		{
			nEnd--;
		}
	}
	return ResultSet;
}

std::vector<int> findIndicesThatHasSumUnsorted(int unsortedArr[], int nSize, int nSum)
{
	std::vector<int> ResultSet;
	int nTemp = 0;
	std::unordered_map<int, int> seenMap;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		nTemp = nSum - unsortedArr[nIndex];
		auto iterator = seenMap.find(nTemp);
		if (iterator != seenMap.end())
		{
			ResultSet.push_back(iterator->second);
			ResultSet.push_back(nIndex);
			break;
		}
		seenMap[unsortedArr[nIndex]] = nIndex;
	}
	return ResultSet;
}

std::vector<pair<int, int>> findPairThatHasSumUnsorted(int unsortedArr[], int nSize, int nSum)
{
	std::vector<pair<int, int>> ResultSet;
	int nTemp = 0;
	std::unordered_set<int> seenSet;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		nTemp = nSum - unsortedArr[nIndex];
		if (seenSet.find(nTemp) != seenSet.end())
		{
			ResultSet.push_back(std::make_pair(unsortedArr[nIndex], nTemp));
		}
		seenSet.insert(unsortedArr[nIndex]);
	}
	return ResultSet;
}

/*
Given an array of integers, find the length of the longest sub-sequence such that elements
in the subsequence are consecutive integers, the consecutive numbers can be in any order.

Examples

Input: arr[] = {1, 9, 3, 10, 4, 20, 2};
Output: 4
The subsequence 1, 3, 4, 2 is the longest subsequence
of consecutive elements

Input: arr[] = {36, 41, 56, 35, 44, 33, 34, 92, 43, 32, 42}
Output: 5
The subsequence 36, 35, 33, 34, 32 is the longest subsequence
of consecutive elements.
*/
unsigned int findLongConsecutiveSubSequence(int unsortedArr[], int nSize)
{
	unsigned int longestSubSeqCount = 0;
	std::unordered_set<int> DataSet;
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		DataSet.insert(unsortedArr[nIndex]);
	}

	int nTemp = 0;
	for (auto dataNum : DataSet)
	{
		//find smallest num first eg; 3, 2, 1, 5, 6 then iterate till it reaches 1.
		if (DataSet.find(dataNum - 1) == DataSet.end())
		{
			nTemp = dataNum;
			while (DataSet.find(nTemp) != DataSet.end())
			{
				nTemp++;
			}
			longestSubSeqCount = max(longestSubSeqCount, (nTemp - dataNum));
		}
	}

	return longestSubSeqCount;
}

int findSmallestElement(int unsortedArr[], int nSize)
{
	int nSmall = INT_MAX;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (unsortedArr[nIndex] < nSmall)
		{
			nSmall = unsortedArr[nIndex];
		}
	}
	return nSmall;
}

int findTwoSmallestElement(int unsortedArr[], int nSize)
{
	int nFirstSmall = INT_MAX;
	int nSecondSmall = INT_MAX;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (unsortedArr[nIndex] < nFirstSmall)
		{
			nSecondSmall = nFirstSmall;
			nFirstSmall = unsortedArr[nIndex];
		}
		else if (unsortedArr[nIndex] < nSecondSmall && unsortedArr[nIndex] != nFirstSmall)
		{
			nSecondSmall = unsortedArr[nIndex];
		}
	}
	return nFirstSmall + nSecondSmall;
}

int findLargestElement(int unsortedArr[], int nSize)
{
	int nLarge = 0;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (unsortedArr[nIndex] > nLarge)
		{
			nLarge = unsortedArr[nIndex];
		}
	}
	return nLarge;
}

/*
find the sum of contiguous subarray within a one-dimensional array of numbers which has the largest sum.

[-2, -3, 4, -1, -2, 1, 5, -3]

ans -> 4 + -1+ -2 + 1 + 5 = 7
*/
int maxSubArraySum(int unsortedArr[], int nSize)
{
	int max_so_far = unsortedArr[0];
	int curr_max = unsortedArr[0];

	for (int nIndex = 1; nIndex < nSize; nIndex++)
	{
		curr_max = max(unsortedArr[nIndex], curr_max + unsortedArr[nIndex]);
		max_so_far = max(max_so_far, curr_max);
	}
	return max_so_far;
}

int maxSubArraySumWithIndex(int unsortedArr[], int nSize)
{
	int max_sum_so_far = INT_MIN;
	int max_ending_here = 0;
	int nStartIndex = 0;
	int nEndIndex = 0;
	int nNewIndex = 0;

	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		max_ending_here += unsortedArr[nIndex];

		if (max_sum_so_far < max_ending_here)
		{
			max_sum_so_far = max_ending_here;
			nStartIndex = nNewIndex;
			nEndIndex = nIndex;
		}

		if (max_ending_here <= 0)
		{
			max_ending_here = 0;
			nNewIndex = nIndex + 1;
		}
	}

	return max_sum_so_far;
}

int lengthOfLongestSubstring(std::string s) 
{
	int n = s.length(), ans = 0;
	int* index = new int[128]; // current index of character
	// try to extend the range [i, j]
	for (int j = 0, i = 0; j < n; j++) 
	{
		i = max(index[s[j]], i);
		ans = max(ans, j - i + 1);
		index[s[j]] = j + 1;
	}
	return ans;
}

double findMedianSortedArrays(int nums1[], int nums2[], int nSize1, int nSize2)
{
	vector<int> Result(nSize1 + nSize2);
	int nArray1Index = 0;
	int nArray2Index = 0;
	int nIndex = 0;
	while (nArray1Index < nSize1 || nArray2Index < nSize2)
	{
		if (nArray1Index < nSize1 && nArray2Index < nSize2)
		{
			if (nums1[nArray1Index] < nums2[nArray2Index])
			{
				Result[nIndex++] = (nums1[nArray1Index]);
				++nArray1Index;
			}
			else if (nums1[nArray1Index] > nums2[nArray2Index])
			{
				Result[nIndex++] = (nums2[nArray2Index]);
				++nArray2Index;
			}
		}
		else if (nArray1Index >= nSize1)
		{
			Result[nIndex++] = (nums2[nArray2Index]);
			++nArray2Index;
		}
		else if (nArray2Index >= nSize2)
		{
			Result[nIndex++] = (nums1[nArray1Index]);
			++nArray1Index;
		}
	}

	int nResultSize = nSize1 + nSize2;
	int nMid = 0;
	double nMedian = 0;
	if (nResultSize % 2 == 0)
	{
		nMid = (nResultSize / 2) - 1;
		double first = Result[nMid];
		double second = Result[nMid + 1];
		nMedian = (first + second) / 2;
	}
	else
	{
		nMid = (nResultSize / 2);
		nMedian = Result[nMid];
	}

	return nMedian;
}

double findMedianSortedArraysWithDiffSize(int nums1[], int nums2[], int nSize1, int nSize2)
{
	if (nSize1 == 0 && nSize2 == 0)
	{
		return -1;
	}
	if (nSize1 > nSize2)
	{
		return findMedianSortedArraysWithDiffSize(nums2, nums1, nSize2, nSize1);
	}
	int low = 0;
	int high = nSize1;
	while (low <= high)
	{
		int partitionX = (low + high) / 2;
		int partitionY = (nSize1 + nSize2 + 1) / 2 - partitionX;

		int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
		int minX = (partitionX == nSize1) ? INT_MAX : nums1[partitionX];

		int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
		int minY = (partitionY == nSize2) ? INT_MAX : nums2[partitionY];

		if (maxX <= minY && maxY <= minX)
		{
			if ((nSize1 + nSize2) % 2 == 0)
			{
				return (max(maxX, maxY) + min(minX, minY)) / 2.0;
			}
			else
			{
				return max(maxX, maxY);
			}
		}
		else if (maxX > minY)
		{
			high = partitionX - 1;
		}
		else
		{
			low = partitionX + 1;
		}
	}
	return  -1;
}

vector<long long> sortSquares(int sortedArray[], int nSize)
{
	int arrIndex = 0;
	for (arrIndex = 0; arrIndex < nSize; ++arrIndex)
	{
		if (sortedArray[arrIndex] >= 0)
		{
			break;
		}
	}

	int firstHalfIndex = arrIndex - 1;
	int secondHalfIndex = arrIndex;

	vector<long long> resultArray(nSize);
	int nTempIndex = 0;
	long long firstval = (long long)INT_MAX * INT_MAX;
	long long secondval = 0;
	while (firstHalfIndex >= 0 || secondHalfIndex < nSize)
	{
		firstval = static_cast<long long>(sortedArray[firstHalfIndex] * sortedArray[firstHalfIndex]);
		secondval = static_cast<long long>(sortedArray[secondHalfIndex] * sortedArray[secondHalfIndex]);
		if ((secondHalfIndex > nSize) || (firstval < secondval))
		{
			resultArray[nTempIndex] = firstval;
			firstHalfIndex--;
		}
		else if ((firstHalfIndex < 0) || (firstval >= secondval))
		{
			resultArray[nTempIndex] = (secondval);
			secondHalfIndex++;
		}
		nTempIndex++;
	}

	return resultArray;
}

vector<long long> sortedSquare(int sortedArray[], int nSize)
{
	vector<long long> sortedSquare(nSize);
	int front = 0;
	int back = nSize - 1;
	int currentPos = nSize - 1;
	while (front <= back)
	{
		int frontSq = sortedArray[front] * sortedArray[front];
		int backSq = sortedArray[back] * sortedArray[back];

		if (frontSq <= backSq)
		{
			sortedSquare[currentPos--] = backSq;
			--back;
		}
		else
		{
			sortedSquare[currentPos--] = frontSq;
			++front;
		}
	}

	return sortedSquare;
}

/*
Active and Inactive cells after k Days
Given a binary array of size n where n > 3. A true (or 1) value in the array means active and false (or 0) means inactive. 
Given a number k, the task is to find count of active and inactive cells after k days. After every day, 
status of i’th cell becomes active if left and right cells are not same and inactive if left and right cell are same (both 0 or both 1).
Since there are no cells before leftmost and after rightmost cells, 
the value cells before leftmost and after rightmost cells is always considered as 0 (or inactive).

Recommended: Please try your approach on {IDE} first, before moving on to the solution.
Examples:

Input  : cells[] = {1, 0, 1, 1}, k = 2
Output : Active cells = 3, Inactive cells = 1
After 1 day,  cells[] = {0, 0, 1, 1}
After 2 days, cells[] = {0, 1, 1, 1}

Input : cells[] = {0, 1, 0, 1, 0, 1, 0, 1},  k = 3
Output: Active Cells = 2 , Inactive Cells = 6
Explanation :
After 1 day, cells[] = {1, 0, 0, 0, 0, 0, 0, 0}
After 2 days, cells[] = {0, 1, 0, 0, 0, 0, 0, 0}
After 3 days, cells[] =  {1, 0, 1, 0, 0, 0, 0, 0}

Input : cells[] = {0, 1, 1, 1, 0, 1, 1, 0},  k = 4
Output: Active Cells = 3 , Inactive Cells = 5
*/
vector<int> findStates(int cellStates[], int nSize, int nDays)
{
	vector<int> tempStates(nSize);
	for (int nIndex = 0; nIndex < nSize; ++nIndex)
	{
		tempStates[nIndex] = cellStates[nIndex];
	}

	while (nDays--)
	{
		tempStates[0] = 0 ^ cellStates[1];
		tempStates[nSize - 1] = 0 ^ cellStates[nSize - 2];

		for (int nCellIndex = 1; nCellIndex < nSize - 1; ++nCellIndex)
		{
			tempStates[nCellIndex] = cellStates[nCellIndex - 1] ^ cellStates[nCellIndex + 1];
		}

		for (int nIndex = 0; nIndex < nSize; ++nIndex)
		{
			cellStates[nIndex] = tempStates[nIndex];
		}
	}

	return tempStates;
}

int gcd(int a, int b) 
{
	int temp;
	while (b > 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

// Function to return gcd of a and b
int calculateGCD(int firstNum, int secondNum)
{
	if (firstNum == 0)
	{
		return secondNum;
	}
	return calculateGCD(secondNum % firstNum, firstNum);
}

int findGCD(int numArray[], int nSize)
{
	int result = numArray[0];
	for (int nIndex = 1; nIndex < nSize; nIndex++)
	{
		result = calculateGCD(numArray[nIndex], result);
	}
	return result;
}

// Returns LCM of array elements
long long findLCM(int inputArr[], int nSize)
{
	// Initialize result
	long long result = inputArr[0];

	// ans contains LCM of arr[0], ..arr[i]
	// after i'th iteration,
	for (int nIndex = 1; nIndex < nSize; nIndex++)
	{
		result = (((inputArr[nIndex] * result)) / (calculateGCD(inputArr[nIndex], result)));
	}
	return result;
}

unsigned int calcLCM(int firstNum, int secondNum)
{
	unsigned int largeNum = (firstNum > secondNum) ? firstNum : secondNum;

	while (true)
	{
		if (largeNum % firstNum == 0 && largeNum % secondNum == 0)
		{
			return largeNum;
		}
		++largeNum;
	}
}


string longestPalindrome(string s)
{
	int maxLength = 1;
	int startIndex = 0;
	int lowIndex = 0;
	int highIndex = 0;
	int stringLength = s.size();

	for (int nIndex = 1; nIndex < stringLength; ++nIndex)
	{
		// Find the longest even length palindrome with center points
		// as i-1 and i.  
		lowIndex = nIndex - 1;
		highIndex = nIndex;
		while (lowIndex >= 0 && highIndex < stringLength && s[lowIndex] == s[highIndex])
		{
			if (highIndex - lowIndex + 1 > maxLength)
			{
				startIndex = lowIndex;
				maxLength = highIndex - lowIndex + 1;
			}
			--lowIndex;
			++highIndex;
		}

		// Find the longest odd length palindrome with center 
		// point as i
		lowIndex = nIndex - 1;
		highIndex = nIndex + 1;
		while (lowIndex >= 0 && highIndex < stringLength && s[lowIndex] == s[highIndex])
		{
			if (highIndex - lowIndex + 1 > maxLength)
			{
				startIndex = lowIndex;
				maxLength = highIndex - lowIndex + 1;
			}
			--lowIndex;
			++highIndex;
		}
	}

	string strResult = s.substr(startIndex, maxLength);
	return strResult;
}

bool isPalindromeOrNot(string strSentence)
{
	int Left = 0;
	int Right = strSentence.length() - 1;

	while (Left < Right)
	{
		strSentence[Left] = tolower(strSentence[Left]);
		strSentence[Right] = tolower(strSentence[Right]);
		//if (!(strSentence[Left] >= 'a' && strSentence[Left] <= 'z'))
		if (!std::isalnum(static_cast<unsigned char>(strSentence[Left])))
		{
			Left++;
		}
		//else if (!(strSentence[Right] >= 'a' && strSentence[Right] <= 'z'))
		else if (!std::isalnum(static_cast<unsigned char>(strSentence[Right])))
		{
			Right--;
		}
		else if (strSentence[Left] == strSentence[Right])
		{
			Left++;
			Right--;
		}
		else
		{
			return false;
		}
	}

	return true;
}

int reverse(int num)
{
	int result = 0;
	while (num != 0)
	{
		result = (result * 10) + (num % 10);
		num = num / 10;
	}
	return result;
}

bool isPalindromeNum(int n)
{
	// Find the appropriate divisor
	// to extract the leading digit
	int divisor = 1;
	while (n / divisor >= 10)
		divisor *= 10;

	while (n != 0)
	{
		int leading = n / divisor;
		int trailing = n % 10;

		// If first and last digit 
		// not same return false
		if (leading != trailing)
			return false;

		// Removing the leading and trailing
		// digit from number
		n = (n % divisor) / 10;

		// Reducing divisor by a factor 
		// of 2 as 2 digits are dropped
		divisor = divisor / 100;
	}
	return true;
}

bool IsPalindrome(int x) 
{
	// Special cases:
	// As discussed above, when x < 0, x is not a palindrome.
	// Also if the last digit of the number is 0, in order to be a palindrome,
	// the first digit of the number also needs to be 0.
	// Only 0 satisfy this property.
	if (x < 0 || (x % 10 == 0 && x != 0)) 
	{
		return false;
	}

	int revertedNumber = 0;
	while (x > revertedNumber) 
	{
		revertedNumber = revertedNumber * 10 + x % 10;
		x /= 10;
	}

	// When the length is an odd number, we can get rid of the middle digit by revertedNumber/10
	// For example when the input is 12321, at the end of the while loop we get x = 12, revertedNumber = 123,
	// since the middle digit doesn't matter in palidrome(it will always equal to itself), we can simply get rid of it.
	return x == revertedNumber || x == revertedNumber / 10;
}

/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
*/
bool regExprMatch(char strExpr[], char strPattern[], int nExprLength, int nPatternLength)
{
	// empty pattern can only match with
	// empty string
	if (nPatternLength == 0)
	{
		return (nExprLength == 0);
	}

	// lookup table for storing results of
	// subproblems
	//Expr : rows
	//patt: cols
	bool** lookup = new bool*[nExprLength + 1];
	for (int nIndex = 0; nIndex < (nExprLength + 1); ++nIndex)
	{
		lookup[nIndex] = new bool[nPatternLength + 1];
		memset(lookup[nIndex], false, nPatternLength + 1);
	}

	// empty pattern can match with empty string
	lookup[0][0] = true;

	// Only '*' can match with empty string
	for (int nIndex = 1; nIndex <= nPatternLength; nIndex++)
	{
		if (strPattern[nIndex - 1] == '*')
		{
			lookup[0][nIndex] = lookup[0][nIndex - 2];
		}
	}

	// fill the table in bottom-up fashion
	for (int nIndex = 1; nIndex <= nExprLength; nIndex++)
	{
		for (int pIndex = 1; pIndex <= nPatternLength; pIndex++)
		{

			// Current characters are considered as
			// matching in two cases
			// (a) current character of pattern is '?'
			// (b) characters actually match
			if (strPattern[pIndex - 1] == '.' || strExpr[nIndex - 1] == strPattern[pIndex - 1])
			{
				lookup[nIndex][pIndex] = lookup[nIndex - 1][pIndex - 1];
			}
			// Two cases if we see a '*'
			// a) We ignore ‘*’ character and move
			//    to next  character in the pattern,
			//     i.e., ‘*’ indicates an empty sequence.
			// b) '*' character matches with ith
			//     character in input
			else if (strPattern[pIndex - 1] == '*')
			{
				lookup[nIndex][pIndex] = lookup[nIndex][pIndex - 2]; 
				if (strPattern[pIndex - 2] == '.' || strExpr[nIndex - 1] == strPattern[pIndex - 2])
				{
					lookup[nIndex][pIndex] = lookup[nIndex][pIndex] || lookup[nIndex - 1][pIndex];
				}
			}
			// If characters don't match
			else
			{
				lookup[nIndex][pIndex] = false;
			}
		}
	}

	return lookup[nExprLength][nPatternLength];
}

bool isRegularExpMatch(string s, string p) 
{
	// base case
	if (p.length() == 0) 
	{
		return s.length() == 0;
	}

	// special case
	if (p.length() == 1)
	{

		// if the length of s is 0, return false
		if (s.length() < 1) 
		{
			return false;
		}

		//if the first does not match, return false
		else if ((p.at(0) != s.at(0)) && (p.at(0) != '.'))
		{
			return false;
		}

		// otherwise, compare the rest of the string of s and p.
		else 
		{
			return isRegularExpMatch(s.substr(1), p.substr(1));
		}
	}

	// case 1: when the second char of p is not '*'
	if (p.at(1) != '*') 
	{
		if (s.length() < 1)
		{
			return false;
		}
		if ((p.at(0) != s.at(0)) && (p.at(0) != '.')) 
		{
			return false;
		}
		else 
		{
			return isRegularExpMatch(s.substr(1), p.substr(1));
		}
	}

	// case 2: when the second char of p is '*', complex case.
	else 
	{
		//case 2.1: a char & '*' can stand for 0 element
		if (isRegularExpMatch(s, p.substr(2)))
		{
			return true;
		}

		//case 2.2: a char & '*' can stand for 1 or more preceding element, 
		//so try every sub string
		int i = 0;
		while (i<s.length() && (s.at(i) == p.at(0) || p.at(0) == '.'))
		{
			if (isRegularExpMatch(s.substr(i + 1), p.substr(2)))
			{
				return true;
			}
			i++;
		}
		return false;
	}
}


bool matchRegexRecursive(string text, string pattern, int pos1, int pos2)
{
	//if pos2 has reached end of pattern means pos2 should also reach end of text for match
	//to happen
	if (pos2 == pattern.length()) 
	{
		return pos1 == text.length();
	}

	//if next character is not * means either current value at pattern and text should be same
	//or current value at pattern should be . in which case you can skip one character of text
	if (pos2 == pattern.length() - 1 || pattern[pos2 + 1] != '*') 
	{
		return (pos1 < text.length() && (text[pos1] == pattern[pos2] || pattern[pos2] == '.')) && matchRegexRecursive(text, pattern, pos1 + 1, pos2 + 1);
	}

	//if we have case like abc and ad*bc so here we totally skip d*
	if (matchRegexRecursive(text, pattern, pos1, pos2 + 2))
	{
		return true;
	}

	//For case like abbc and ab*c match first b with b* and then next b to c. If that does not work out
	//then try next b with b* and then c with c and so on.
	//if pattern current val is . then skip one character at time from text till we either reach end of text
	//or a match is found
	while (pos1 < text.length() && (text[pos1] == pattern[pos2] || pattern[pos2] == '.'))
	{
		if (matchRegexRecursive(text, pattern, pos1 + 1, pos2 + 2)){
			return true;
		}
		pos1++;
	}
	return false;
}

/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
*/
bool wildCardMatch(char strExpr[], char strPattern[], int nExprLength, int nPatternLength)
{
	// empty pattern can only match with
	// empty string
	if (nPatternLength == 0)
	{
		return (nExprLength == 0);
	}

	int newPatternIndex = 0;
	bool bIsFirst = true;

	for (int nPatIndex = 0; nPatIndex < nPatternLength; ++nPatIndex)
	{
		if (strPattern[nPatIndex] == '*')
		{
			if (bIsFirst)
			{
				strPattern[newPatternIndex++] = strPattern[nPatIndex];
				bIsFirst = false;
			}
		}
		else
		{
			strPattern[newPatternIndex++] = strPattern[nPatIndex];
			bIsFirst = true;
		}
	}

	nPatternLength = newPatternIndex;

	// lookup table for storing results of
	// subproblems
	bool** lookup = new bool*[nExprLength + 1];
	for (int nIndex = 0; nIndex < (nExprLength + 1); ++nIndex)
	{
		lookup[nIndex] = new bool[nPatternLength + 1];
		memset(lookup[nIndex], false, nPatternLength + 1);
	}

	// empty pattern can match with empty string
	lookup[0][0] = true;

	// Only '*' can match with empty string
	if (nPatternLength > 0 && strPattern[0] == '*')
	{
		lookup[0][1] = true;
	}

	// fill the table in bottom-up fashion
	for (int nIndex = 1; nIndex <= nExprLength; nIndex++)
	{
		for (int pIndex = 1; pIndex <= nPatternLength; pIndex++)
		{

			// Current characters are considered as
			// matching in two cases
			// (a) current character of pattern is '?'
			// (b) characters actually match
			if (strPattern[pIndex - 1] == '?' || strExpr[nIndex - 1] == strPattern[pIndex - 1])
			{
				lookup[nIndex][pIndex] = lookup[nIndex - 1][pIndex - 1];
			}
			// Two cases if we see a '*'
			// a) We ignore ‘*’ character and move
			//    to next  character in the pattern,
			//     i.e., ‘*’ indicates an empty sequence.
			// b) '*' character matches with ith
			//     character in input
			else if (strPattern[pIndex - 1] == '*')
			{
				lookup[nIndex][pIndex] = lookup[nIndex][pIndex - 1] || lookup[nIndex - 1][pIndex];
			}
			// If characters don't match
			else
			{
				lookup[nIndex][pIndex] = false;
			}
		}
	}

	return lookup[nExprLength][nPatternLength];
}

vector<string> findMostFrequent(std::string sentence, vector<string> wordsToExclude)
{
	int nFirstIndex = 0;
	int nSecondIndex = 0;
	int nCharIndex = 0;
	vector<string> frequentWords;
	unordered_map<string, int> wordCount;
	string word;
	while (sentence[nCharIndex])
	{
		if (sentence[nCharIndex] == ' ')
		{
			/*if (nFirstIndex == -1)
			{
				nFirstIndex = nCharIndex;
			}
			else*/
			{
				nSecondIndex = nCharIndex;
				if ((nSecondIndex - nFirstIndex) > 1)
				{
					word = sentence.substr(nFirstIndex, nSecondIndex - nFirstIndex);
					if (wordsToExclude.end() == std::find(wordsToExclude.begin(), wordsToExclude.end(), word))
					{
						wordCount[word]++;
					}
					//nFirstIndex = nCharIndex + 1;
				}
				else
				{
					//nFirstIndex = nSecondIndex + 1;
				}
				nFirstIndex = nCharIndex + 1;
			}
		}
		nCharIndex++;
	}

	// To get last word.
	nSecondIndex = nCharIndex;
	if ((nSecondIndex - nFirstIndex) > 1)
	{
		word = sentence.substr(nFirstIndex, nSecondIndex - nFirstIndex);
		if (wordsToExclude.end() == std::find(wordsToExclude.begin(), wordsToExclude.end(), word))
		{
			wordCount[word]++;
		}
		nFirstIndex = -1;
	}

	for (auto word : wordCount)
	{
		if (word.second > 1)
		{
			frequentWords.push_back(word.first);
		}
	}

	return frequentWords;
}

std::vector<string> logProcessor( int nFileSize, vector<string> list)
{
	vector<string> strAlp;
	vector<string> strNum;
	vector<string> AlpNum;

	/*for (string sl : list)
	{

		string slPart;
		size_t pos = sl.find(' ', 2);
		if (string::npos != pos)
		{
			slPart = sl.substr(pos, 2);
		}
		if (isdigit(slPart[1].at(0))){
			strNum.add(sl);
		}
		else {
			strAlp.add(slPart[1].concat(" " + slPart[0]));
		}
	}
	Collections.sort(strAlp);
	for (String sl2 : strAlp){
		String[] part = { sl2.substring(0, sl2.lastIndexOf(" ")), sl2.substring(sl2.lastIndexOf(" ") + 1) };
		AlpNum.add(part[1].concat(" " + part[0]));
	}
	AlpNum.addAll(strNum);*/
	return AlpNum;
}

int findMaxAreaContainsWater(vector<int> height)
{
	int nMaxArea = 0;
	int nLength = height.size();
	int nLeftIndex = 0;
	int nRightIndex = nLength - 1;

	while (nLeftIndex < nRightIndex)
	{
		nMaxArea = max(nMaxArea, ((nRightIndex - nLeftIndex) * min(height[nLeftIndex], height[nRightIndex])));
		if (height[nLeftIndex] < height[nRightIndex])
		{
			++nLeftIndex;
		}
		else
		{
			--nRightIndex;
		}
	}

	return nMaxArea;
}

int findMaxTrappingWater(vector<int> height)
{
	int TotalAmount = 0;
	int nLeftIndex = 0;
	int nRightIndex = height.size() - 1;
	int nLeftMax = 0;
	int nRightMax = 0;

	while (nLeftIndex < nRightIndex){
		if (height[nLeftIndex] < height[nRightIndex]){
			height[nLeftIndex] >= nLeftMax ? nLeftMax = height[nLeftIndex] : TotalAmount += (nLeftMax - height[nLeftIndex]);
			nLeftIndex++;
		}
		else{
			height[nRightIndex] >= nRightMax ? nRightMax = height[nRightIndex] : TotalAmount += (nRightMax - height[nRightIndex]);
			nRightIndex--;
		}
	}

	return TotalAmount;
}

string intToRoman(int num) 
{
	string strRoman;
	if (num > 0 && num < 4000)
	{
		string strThousands[] = { "", "M", "MM", "MMM" };
		string strHundreds[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		string strTens[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		string strOnes[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

		strRoman = strThousands[num / 1000] + strHundreds[(num % 1000) / 100] + strTens[(num % 100) / 10] + strOnes[num % 10];
	}
	return strRoman;
}

int getIntegerValue(char romanChar)
{
	if (romanChar == 'I')
	{
		return 1;
	}
	if (romanChar == 'V')
	{
		return 5;
	}
	if (romanChar == 'X')
	{
		return 10;
	}
	if (romanChar == 'L')
	{
		return 50;
	}
	if (romanChar == 'C')
	{
		return 100;
	}
	if (romanChar == 'D')
	{
		return 500;
	}
	if (romanChar == 'M')
	{
		return 1000;
	}
	return 0;
}

// Returns decimal value of roman numaral
int romanToDecimal(string strRoman)
{
	int nResult = 0;
	int nLength = strRoman.length();
	int nFirstDigit = 0;
	int nSecondDigit = 0;

	for (int nIndex = 0; nIndex < nLength; ++nIndex)
	{
		nFirstDigit = getIntegerValue(strRoman[nIndex]);

		if ((nIndex + 1) < nLength)
		{
			nSecondDigit = getIntegerValue(strRoman[nIndex + 1]);
			if (nFirstDigit >= nSecondDigit)
			{
				nResult = nResult + nFirstDigit;
			}
			else
			{
				nResult = nResult + nSecondDigit - nFirstDigit;
				nIndex++; 
			}
		}
		else
		{
			nResult = nResult + nFirstDigit;
			nIndex++;
		}
	}
	return nResult;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	//CopyConstEx* pObj = NULL;// new CopyConstEx();
	//delete pObj;
	//CopyConstEx obj1(*pObj);
	HMODULE hModule = ::GetModuleHandle(NULL);
	//int re = findMinTriesToBreakEggFromFloor(2, 6);
	//longestSubSequenceOfStrings("abcde", "hgckde");
	//vector<int> OddArr{ 3, 4, 5, 3, 4, 5, 7, 1, 1 };
	//int ans = findOddOccuredElement(OddArr);
	int nRetCode = 0;
	//vector<vector<int>> in{ { 0, 2, 3 }, { 2, 5, 3 } };
	//vector<int> seqArr{ 3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10};
	//longIncreasngSubSeq(seqArr);
	//formatCharStream("ssad fdfgdfgg hhdffdsff tri sdfsdf fg g g s f g h d s c v b n f r e ss f f g");
	//playSongs(PlayList);
	//getSkyline(in);
	//isPalindromeOrNot("dA  9 a D");
	validPath("\\C:\\a\\\\fdfdf\\");
	//countTrailingZerosOfFactorial(1000);
	
	//findPartitionedSubSetsWithEqualSum(in);
	int SortArr[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121 };
	int rss = findMinCombinationsOfCoins(SortArr, sizeof(SortArr) / sizeof(SortArr[0]), 143);
	//maxIndicesDiff(in);
	int c = 0;
	//vector<std::pair<int, int>> List1{ make_pair(1, 3), make_pair(5, 8), make_pair(9, 11) };
	//vector<std::pair<int, int>> List2{ make_pair(2, 3), make_pair(4, 7) };
	//intersectionOfSetOfSortedIntervals(List1, List2);
	//areAnagram("abc", "aa");
	/*long f, s;
	cout << "f" << std::endl;
	cin >> f;
	cout << "s" << std::endl;
	cin >> s;*/


	//AddBinaryNumbers(f, s);
	//calcDivision(9, 3);
	int SortArffr[] = { 5, 7, 7, 8, 8, 10 };
	int n = sizeof(SortArffr) / sizeof(SortArffr[0]);
	//searchRange(SortArr, 0, n - 1, 6);
	//bool bres = isValid("((");
	int a = 10 + 12;
	//printZigZagConcat("GEEKSFORGEEKS", 3);
	
	//romanToDecimal("XII");
	/*vector<int> excludeList;
	excludeList.push_back(-1);
	excludeList.push_back(2);
	excludeList.push_back(1);
	excludeList.push_back(-4);
	excludeList.push_back(-1);
	excludeList.push_back(4);
	threeSumClosest(excludeList, 1);
	findMostFrequent(" jack and  jill  went to the market to buy bread and cheese cheese is jack favorite food ", excludeList);

	//bool bVal = wildCardMatch("aa", "*");
	char strArr[] = "aa";
	char pattern[] = "*";
	bool bres = wildCardMatch(strArr, pattern, sizeof(strArr) - 1, sizeof(pattern) - 1);

	stringToInt("    -42"); 
	int SortArr[] = { 0, 1, 1, 1, 0, 1, 1, 0 };
	int SortArr1[] = { 3, 4 };
	findStates(SortArr, sizeof(SortArr) / sizeof(SortArr[0]), 4);*/

	/*int SortArr[] = { 2,3,6,8,10};
	int SortArr1[] = { 1,4,7,9,12,13 };
	findMedianSortedArraysWithDiffSize(SortArr, SortArr1, sizeof(SortArr) / sizeof(SortArr[0]), sizeof(SortArr1) / sizeof(SortArr1[0])); */

	//checkRectanglesOverlap(RecPoint(2, 1), RecPoint(5, 5), RecPoint(3, 2), RecPoint(5, 7));
	//unsigned int res = numwaysofsteps(4);

	//int n = countOnes(23);

	/*QueueUsingStack Qobj;
	Qobj.insertToQueue(1);
	Qobj.insertToQueue(2);
	Qobj.insertToQueue(3);
	Qobj.insertToQueue(4);
	int reslt = Qobj.recurDequeue();
	reslt = Qobj.recurDequeue();

	int SArr[7] = { 1, 3, 5, -2, 8, 9, 11 };
	checkAlmostIncreasingSequence(SArr, sizeof(SArr) / sizeof(SArr[0]));

	unsigned int A[5][5] = { { 1, 0, 1, 1, 0 }, { 0, 1, 1, 1, 0 }, { 0, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1 } };
	unsigned int B[5][5] = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
	unsigned int res = findMaxSquare(A, B, 5, 5);*/
	/*int num1, num2;
	cout << " Input the 1st binary number: ";
	cin >> num1;
	cout << " Input the 2nd binary number: ";
	cin >> num2;*/
	//AddBinaryStrings("1010", "11");
	/*const std::vector<int> input{ 1,3,6,7,3,3,6 };
	std::unordered_map<int, int> count;
	for (int i : input) 
	{
		++count[i];
	}
	std::vector<std::pair<int, int>> pairs;
	pairs.reserve(count.size());
	std::copy(count.begin(), count.end(), std::back_inserter(pairs));
	int k = 3;
	std::partial_sort(pairs.begin(), pairs.begin() + k, pairs.end(),
		[](const std::pair<int, int> &a, const std::pair<int, int> &b) 
	{
		return a.second > b.second;
	}
	);
	for (int i = 0; i < k; ++i) 
	{
		std::cout << pairs[i].first << ", " << pairs[i].second << '\n';
	}*/



	//interval_map<unsigned int, char> myMap('A');
	////Initialize(myMap, 'A');

	//std::cout << "Initial values : \n";
	//myMap.Print();
	//
	//std::cout << "\n\nTest values  (-3, 3, 'B') : \n";
	//myMap.assign(-3, 3, 'B');
	//
	//std::cout << "\n\nTest values (21, 300000, 'G') : \n";
	//myMap.assign(21, 4294967294, 'G');
	//myMap.Print();
	//myMap.Print();

	/*
	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (21, 30, 'G') : \n";
	myMap.assign(21, 30, 'G');
	myMap.Print();


	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (42, 47, 'S') : \n";
	myMap.assign(42, 47, 'S');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (25, 34, 'F') : \n";
	myMap.assign(25, 34, 'F');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (11, 15, 'D') : \n";
	myMap.assign(11, 15, 'D');
	myMap.Print();


	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (10, 10, 'T') : \n";
	myMap.assign(10, 10, 'T');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (15, 10, 'T') : \n";
	myMap.assign(15, 10, 'T');
	myMap.Print();

	Initialize(myMap, 'A');
	std::cout << "\n\n\n\n\nInitial values : \n";
	myMap.Print();
	std::cout << "\n\nTest values (15, 10, 'T') : \n";
	myMap.assign(25, 35, 'A');
	myMap.Print();


	

	int A[4][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };
	int B[3][5] = { { 13, 14, 15, 3, 4 }, { 4, 7, 8, 9, 1 }, { 15, 4, 7, 8, 5 } };
	int out[5][3];
	Matrix mat;
	mat.matrixTranspose(B, out, 3, 5);
	//mat.matrixMultiplication(A, B, out, 4, 3, 3, 5);*/
		
		
	/*int unArray[] = {-1,-2,1};
	int arrSize = sizeof(unArray) / sizeof(unArray[0]);
	int val = findMissingSmallestInteger(unArray, arrSize);
	int s = 7;*/
	/*Sorting sort;
	sort.printArray(unArray, arrSize);
	sort.HeapSort(unArray, arrSize);
	sort.printArray(unArray, arrSize);
	int k = 3;
	int v = unArray[k-1];
	
	std::string tsr = removeSpaces("     geek hh   jjj k k   ");
	int a = -6;
	//a = 2;
	unsigned int b = 4294967290;


	
	GetSize obj;
	int size = my_sizeof(obj);

	
	int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//findOdd(arr, n);

	stringToFloat("2345.0", 1);
	stringToInt("342098");
	intToStr(56700);
	float fNum = 34.877;
	ftoa(fNum);*/

	/*int cardArray[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8,
						9, 10, 11, 12, 13, 14, 15,
						16, 17, 18, 19, 20, 21, 22,
						23, 24, 25, 26, 27, 28, 29,
						30, 31, 32, 33, 34, 35, 36,
						37, 38, 39, 40, 41, 42, 43,
						44, 45, 46, 47, 48, 49, 50,
						51 };

	shuffle(cardArray, sizeof(cardArray)/sizeof(int));*/

	//int res = power(10, 6);

	/*string strWrd("ABC");
	permutation(strWrd, 0, strWrd.length() - 1);*/

	/*PriorityQueue pQueue;
	pQueue.insertIntoPQueue(10, 5);
	pQueue.insertIntoPQueue(12, 6);
	pQueue.insertIntoPQueue(5, 3);
	pQueue.insertIntoPQueue(8, 4);
	pQueue.insertIntoPQueue(15, 7);
	pQueue.insertIntoPQueue(3, 2);
	pQueue.insertIntoPQueue(2, 1);
	pQueue.displayQueue();*/

	/*Stock ArrayIntersection;
	int arr1[] = { 2,3,4,5,6,7,8,9,16,22,33};
	int arr2[] = { 1,3,4,10,11,13,14,15,16,17,22,25,30,33,35,36};
	
	ArrayIntersection.findArrayIntersection(arr1, arr2, sizeof(arr1) / sizeof(arr1[0]), sizeof(arr2) / sizeof(arr2[0]));*/
	
	BNode *pBRoot = new BNode(25);
	BinaryTree bTree;
	bTree.insertNode(pBRoot, 30);
	bTree.insertNode(pBRoot, 33);
	bTree.insertNode(pBRoot, 20);
	bTree.insertNode(pBRoot, 27);
	bTree.insertNode(pBRoot, 35);
	bTree.insertNode(pBRoot, 34);
	bTree.insertNode(pBRoot, 23);
	bTree.insertNode(pBRoot, 19);
	bTree.insertNode(pBRoot, 17);
	/*bTree.insertNode(pBRoot, 25);
	bTree.insertNode(pBRoot, 28);
	bTree.insertNode(pBRoot, 50);
	bTree.insertNode(pBRoot, 48);
	bTree.insertNode(pBRoot, 55);
	bTree.insertNode(pBRoot, 56);
	bTree.insertNode(pBRoot, 52);*/
	BNode* LinkedList = NULL;
	bTree.isBST(pBRoot);
	bTree.extractLeafNodesAndCreateLinkListFromLeftToRight(pBRoot, &LinkedList);
	//int w = bTree.getMaxWidth(pBRoot);
	
	/*bTree.DeleteNodeInBST(pBRoot, 30);

	bTree.preOrderTraversal(pBRoot);
	printf("\n");
	bTree.inOrderTraversal(pBRoot);
	printf("\n");
	bTree.postOrderTraversal(pBRoot);



	BNode *pTemp = bTree.searchTree(pBRoot, 56);*/
	
	/*stringToFloat("2345.0", 1);
	stringToInt("342098");
	intToStr(56700);
	float fNum = 34.877;
	ftoa(fNum);

	string strWord("Ball");

	std::sort(strWord.begin(), strWord.end());
	do
	{
		cout << strWord << "\n";
	} while (std::next_permutation(strWord.begin(), strWord.end()));


		Trie trie;
		trie.Add("dog");
		trie.Add("eat");
		trie.Add("eats");
		trie.Add("scare");
		trie.Add("care");

		vector<int> memo;
		cout << Count(trie, "dogeatscare", memo) << "\n";*/
			

	/*LinkedList list1;
	LinkedList list2;
	list1.createList(5);
	list2.createList(5);
	LinkedList list3;
	list1.AddTwoNumbers(list1.getHeadNode(), list2.getHeadNode());

	LinkedList list;
	list.createList(2);
	list.createList(1);
	//list.createList(3);
	//list.createList(2);
	//list.createList(5);
	//list.createList(2);
	list.partition(list.getHeadNode(), 2);
	//list.getHeadNode()->m_NextNode->m_NextNode->m_NextNode->m_NextNode->m_NextNode = list.getHeadNode()->m_NextNode;
	//list.displayList(list.removeNthFromEnd(list.getHeadNode(), 1));
	/*list.createList(6);
	list.createList(7);
	list.createList(8);
	list.createList(9);
	list.createList(10);
	list.displayList(list.getHeadNode());
	//list.displayList(list.reverseList(NULL, list.getHeadNode()));
	//list.displayList(list.deleteNodeWithData(list.getHeadNode(), 4));
	list.alternateReverseList(list.getHeadNode());
	//Node* pNode = list.reverseKNodes(list.getHeadNode(), 3);
	Node* pFirst = NULL;
	Node* pSecond = NULL;
	//list.splitList(list.getHeadNode(), pFirst, pSecond);
	list.displayList(list.getHeadNode());
	//list.displayList(pFirst);
	//list.displayList(pSecond);
	//list.deleteNodes(list.getHeadNode());
	//list.ReverseLinkedList();
	//list.deleteFromEnd();
	//list.createList(6);*/

	TrieTreeNode* pRoot = new TrieTreeNode();
	vector<char> wordList;
	pRoot->insertWord("Ball");
	pRoot->insertWord("Apple");
	pRoot->insertWord("App");
	pRoot->insertWord("Apply");
	pRoot->insertWord("Appu");
	pRoot->insertWord("Apetitizer");
	pRoot->insertWord("Apocalypto");
	pRoot->insertWord("app");
	pRoot->insertWord("Ballon");
	pRoot->matchWordsFromPrefix("Ap");

	//pRoot->displayWords(pRoot, wordList);
	cout << "\n";
	bool bDeleteStatus = false;
	bool bRet = pRoot->deleteWord(pRoot, "Ballon", bDeleteStatus);
	bDeleteStatus = false;
	pRoot->deleteWord(pRoot, "Balon", bDeleteStatus);

	//pRoot->displayWords(pRoot, wordList);
	cout << "\n";

	pRoot->searchWord("Ball");
	pRoot->searchWord("Cad");
	pRoot->searchWord("ap");
	pRoot->searchWord("App");
	pRoot->searchWord("Apple");
	delete pRoot;
	pRoot = NULL;

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
