
// Write your code here

#include<iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class TrieTreeNode
{
public:
	TrieTreeNode();
	~TrieTreeNode();
	void insertWord(TrieTreeNode* pRoot, char* pWord, int nWeight);
	int searchWord(TrieTreeNode* pRoot, char* pWord);
	void findMatchWord(TrieTreeNode* pRoot, vector<char> LetterList, int& nWeight);

private:

	std::map<char, TrieTreeNode*> m_ChildList;
	int m_nWeight;
};

TrieTreeNode::TrieTreeNode()
{
	m_nWeight = -1;
}

TrieTreeNode::~TrieTreeNode()
{
	for (const auto& TreeNode : m_ChildList)
	{
		delete TreeNode.second;
	}
}

void TrieTreeNode::insertWord(TrieTreeNode* pRoot, char* pWord, int nWeight)
{
	TrieTreeNode* pTempRootNode = pRoot;
	while (*pWord != '\0')
	{
		if (pTempRootNode->m_ChildList.end() == pTempRootNode->m_ChildList.find(*pWord))
		{
			pTempRootNode->m_ChildList[*pWord] = new TrieTreeNode();
		}
		pTempRootNode = pTempRootNode->m_ChildList[*pWord];
		++pWord;
	}
	if (nWeight > pTempRootNode->m_nWeight)
		pTempRootNode->m_nWeight = nWeight;
}

void TrieTreeNode::findMatchWord(TrieTreeNode* pRoot, vector<char> LetterList, int& nWeight)
{
	if ((pRoot) && (pRoot->m_nWeight > nWeight))
	{
		nWeight = pRoot->m_nWeight;
	}

	for (const auto& TreeNode : pRoot->m_ChildList)
	{
		LetterList.push_back(TreeNode.first);
		findMatchWord(TreeNode.second, LetterList, nWeight);
		LetterList.pop_back();
	}
}

int TrieTreeNode::searchWord(TrieTreeNode* pRoot, char* pWord)
{
	//printf("%s---\n", pWord);
	string strWord(pWord);
	vector<char> Word;
	TrieTreeNode* pTempRootNode = pRoot;
	while (*pWord != '\0')
	{
		if (pTempRootNode->m_ChildList.end() != pTempRootNode->m_ChildList.find(*pWord))
		{
			pTempRootNode = pTempRootNode->m_ChildList[*pWord];
			Word.push_back(*pWord);
			pWord++;
		}
		else
		{
			return -1;
		}
	}

	int nWeight = pTempRootNode->m_nWeight;
	findMatchWord(pTempRootNode, Word, nWeight);
	return nWeight;
}


int main()
{
	int i, j, n, q, k;
	scanf("%d%d", &n, &q);
	string s;
	std::map<string, int> m_StringList;
	TrieTreeNode* pRoot = new TrieTreeNode();
	int nStringLength = 0;
	int nQueryLength = 0;
	int weight = -1;
	if (n >= 1 && n <= 1000000 && q >= 1 && q <= 100000)
	{
		for (i = 1; i <= n; i++)
		{
			cin >> s >> k;
			nStringLength += s.length();
			if (nStringLength >= 1 && nStringLength <= 1000000 && k >= 1 && k <= 1000000)
				pRoot->insertWord(pRoot, const_cast<char*>(s.c_str()), k);
		}
		while (q--)
		{
			cin >> s;
			nQueryLength += s.length();
			weight = -1;
			if (m_StringList.end() == m_StringList.find(s))
			{
				if (nQueryLength >= 1 && nQueryLength <= 1000000)
				{
					weight = pRoot->searchWord(pRoot, const_cast<char*>(s.c_str()));
					m_StringList[s] = weight;
				}
			}
			else
			{
				weight = m_StringList[s];
			}
			printf("%d\n", weight);
		}
	}
	return 0;
}