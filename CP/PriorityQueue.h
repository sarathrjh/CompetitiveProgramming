#include <iostream>
#include "stdafx.h"

struct PQNode
{
	int m_nValue;
	int m_nPriority;
	PQNode* m_pNextNode;

	PQNode(int nValue, int nPriority) : m_nValue(nValue), m_nPriority(nPriority), m_pNextNode(NULL)
	{

	}
};

class PriorityQueue
{
public:
	PriorityQueue() : m_pRoot(NULL)
	{}

	void insertIntoPQueue(int nValue, int nPriority)
	{
		if (m_pRoot == NULL)
		{
			m_pRoot = new PQNode(nValue, nPriority);
		}
		else
		{
			PQNode* pTempNode = new PQNode(nValue, nPriority);
			if (nPriority > m_pRoot->m_nPriority)
			{
				pTempNode->m_pNextNode = m_pRoot;
				m_pRoot = pTempNode;
			}
			else
			{
				PQNode* pTempQueue = m_pRoot;
				while (pTempQueue->m_pNextNode != NULL)
				{
					if (nPriority > pTempQueue->m_pNextNode->m_nPriority)
					{
						break;
					}
					pTempQueue = pTempQueue->m_pNextNode;
				}
				pTempNode->m_pNextNode = pTempQueue->m_pNextNode;
				pTempQueue->m_pNextNode = pTempNode;
			}
		}
	}

	void displayQueue()
	{
		PQNode* pTemp = m_pRoot;
		while (pTemp != NULL)
		{
			std::cout << pTemp->m_nValue << "->";
			pTemp = pTemp->m_pNextNode;
		}
	}

private:
	PQNode* m_pRoot;
};