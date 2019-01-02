
#include "stdafx.h"
#include <iostream>
#include <unordered_set>
#include <vector>

class Node
{
public:
	Node(int nData) : m_nData(nData), m_NextNode(NULL)
	{

	}

	int m_nData;
	Node* m_NextNode;
};

class LinkedList
{
public:
	LinkedList() :m_pRootNode(NULL)
	{}
	void createList(int nData);
	void deleteFromEnd();
	void deleteNodes(Node* pHead);
	Node* deleteDuplicates(Node* pHead);
	Node* deleteNodeWithData(Node* pHead, int nData);
	void ReverseLinkedList();
	Node* reverseList(Node* prevNode, Node* currNode);
	Node* reverseListUsingTemp(Node* pRootNode);
	void alternateReverseList(Node* pRootNode);
	Node* reverseKNodes(Node* pRootNode, int nNodesCount);
	void displayList(Node* pRootNode);
	void splitList(Node* pRootNode, Node*& pFirstHalf, Node*& pSecondHalf);
	Node* findCycleNode(Node* pHead);
	Node* mergeKSortedLists(std::vector<Node*> KLists);
	Node* mergeAndSortLinkedLists(Node* pFirstList, Node* pSecondList);
	Node* AddTwoNumbers(Node* pFirstList, Node* pSecondList);
	void removeDuplicates(Node* pHead);
	void removeDuplicatesUnSorted(Node* pHead);
	Node* removeNthFromEnd(Node* pHead, int nPosition);
	Node* rotateRight(Node* head, int k);
	Node* partition(Node* head, int value);
	Node* getHeadNode()
	{
		return m_pRootNode;
	}

private:
	Node* m_pRootNode;
};

void LinkedList::createList(int nData)
{
	if (!m_pRootNode)
	{
		m_pRootNode = new Node(nData);
		return;
	}

	Node* temp = m_pRootNode;
	while (temp)
	{
		if (temp->m_NextNode == NULL)
		{
			temp->m_NextNode = new Node(nData);
			return;
		}
		temp = temp->m_NextNode;
	}
}

void LinkedList::deleteFromEnd()
{
	deleteNodes(m_pRootNode);
	m_pRootNode = NULL;
}

void LinkedList::deleteNodes(Node* pHead)
{
	if (pHead && pHead->m_NextNode != NULL)
		deleteNodes(pHead->m_NextNode);
	delete pHead;
	pHead = NULL;
}

/*
Given a sorted linked list, delete all nodes that have duplicate numbers, 
leaving only distinct numbers from the original list.

Example 1:
Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:
Input: 1->1->1->2->3
Output: 2->3
*/
Node* LinkedList::deleteDuplicates(Node* pHead)
{
	//head is 1->1->1->2->3
	Node* prev = new Node(0);
	prev->m_NextNode = pHead;
	//0->1->1->1->2->3
	Node* curr = prev;
	Node* tmp = NULL;
	int dupVal = 0;

	while (curr->m_NextNode && curr->m_NextNode->m_NextNode)
	{
		if (curr->m_NextNode->m_nData == curr->m_NextNode->m_NextNode->m_nData)
		{
			dupVal = curr->m_NextNode->m_nData;
			while (curr->m_NextNode && curr->m_NextNode->m_nData == dupVal)
			{
				tmp = curr->m_NextNode;
				curr->m_NextNode = curr->m_NextNode->m_NextNode;
				delete tmp;
			}
		}
		else
		{
			curr = curr->m_NextNode;
		}
	}
	return prev->m_NextNode;
}

Node* LinkedList::deleteNodeWithData(Node* pHead, int nData)
{
	Node* pPrev = pHead;
	Node* pCurr = pHead;

	while (pCurr != NULL)
	{
		if (pCurr->m_nData == nData)
		{
			//delete head data
			if (pCurr == pHead)
			{
				pHead = pCurr->m_NextNode;
				pPrev = pHead;
				delete pCurr;
				pCurr = pPrev;
			}
			else
			{
				pPrev->m_NextNode = pCurr->m_NextNode;
				delete pCurr;
				pCurr = pPrev->m_NextNode;
			}
		}
		else
		{
			pPrev = pCurr;
			pCurr = pCurr->m_NextNode;
		}
	}
	return pHead;
}

Node* LinkedList::reverseList(Node* prevNode, Node* currNode)
{
	Node* pHeadNode = NULL;
	if (currNode->m_NextNode != NULL)
		pHeadNode = reverseList(currNode, currNode->m_NextNode);
	else
		pHeadNode = currNode;
	currNode->m_NextNode = prevNode;
	return pHeadNode;
}

Node* LinkedList::reverseListUsingTemp(Node* pRootNode)
{
	if (pRootNode == NULL)
	{
		return NULL;
	}

	Node* pPrev = NULL;
	Node* pCurr = pRootNode;
	Node* pNext = NULL;

	while (pCurr)
	{
		pNext = pCurr->m_NextNode;
		pCurr->m_NextNode = pPrev;
		pPrev = pCurr;
		pCurr = pNext;
	}

	return pPrev;
}


void LinkedList::ReverseLinkedList()
{
	Node* temp = m_pRootNode;
	//m_pRootNode = NULL;
	Node* pNode = reverseList(NULL, m_pRootNode);
}

/*
Input List:  1->2->3->4->5->6
Output List: 1->3->5->6->4->2
*/
void LinkedList::alternateReverseList(Node* pRootNode)
{
	if (!pRootNode)
	{
		return;
	}
	Node* pEvenList = NULL;
	while (pRootNode->m_NextNode)
	{
		//Take even nodes.
		Node* pTemp = pRootNode->m_NextNode;
		if (pRootNode->m_NextNode->m_NextNode)
		{
			//Point to next odd node.
			pRootNode->m_NextNode = pRootNode->m_NextNode->m_NextNode;
			pTemp->m_NextNode = pEvenList;
			pEvenList = pTemp;
		}
		else
		{
			//last even node.
			pTemp->m_NextNode = pEvenList;
			pEvenList = pTemp;
			break;
		}
		pRootNode = pRootNode->m_NextNode;
	}
	pRootNode->m_NextNode = pEvenList;
}

Node* LinkedList::reverseKNodes(Node* pRootNode, int nNodesCount)
{
	Node* current = pRootNode;
	Node* next = NULL;
	Node* prev = NULL;
	int count = 0;

	/*reverse first k nodes of the linked list */
	while (current != NULL && count < nNodesCount)
	{
		next = current->m_NextNode;
		current->m_NextNode = prev;
		prev = current;
		current = next;
		count++;
	}

	/* next is now a pointer to (k+1)th node
	Recursively call for the list starting from current.
	And make rest of the list as next of first node */
	if (next != NULL)
		pRootNode->m_NextNode = reverseKNodes(next, nNodesCount);

	/* prev is new head of the input list */
	return prev;
}

/* Function to remove duplicates from a
unsorted linked list */
void removeDuplicatesUnSorted(Node* pHead)
{
	// Hash to store seen values
	std::unordered_set<int> seen;

	/* Pick elements one by one */
	Node *pCurrent = pHead;
	Node *pPrev = NULL;
	while (pCurrent != NULL)
	{
		// If current value is seen before
		if (seen.find(pCurrent->m_nData) != seen.end())
		{
			pPrev->m_NextNode = pCurrent->m_NextNode;
			delete pCurrent;
		}
		else
		{
			seen.insert(pCurrent->m_nData);
			pPrev = pCurrent;
		}
		pCurrent = pPrev->m_NextNode;
	}
}

void LinkedList::removeDuplicates(Node* pHead)
{
	/* Pointer to traverse the linked list */
	Node* pCurrent = pHead;

	/* Pointer to store the next pointer of a node to be deleted*/
	Node* pTemp;

	/* do nothing if the list is empty */
	if (pCurrent == NULL)
	{ 
		return;
	}
	/* Traverse the list till last node */
	while (pCurrent->m_NextNode != NULL)
	{
		/* Compare current node with next node */
		if (pCurrent->m_nData == pCurrent->m_NextNode->m_nData)
		{
			pTemp = pCurrent->m_NextNode->m_NextNode;
			delete pCurrent->m_NextNode;
			pCurrent->m_NextNode= pTemp;
		}
		else 
		{
			pCurrent = pCurrent->m_NextNode;
		}
	}
}


Node* LinkedList::findCycleNode(Node* pHead)
{
	if (pHead == NULL)
	{
		return pHead;
	}

	Node* pSlow = pHead;
	Node* pFast = pHead;

	while (pSlow && pFast && pFast->m_NextNode)
	{
		pSlow = pSlow->m_NextNode;
		pFast = pFast->m_NextNode->m_NextNode;

		if (pSlow == pFast)
		{
			break;
		}
	}

	if (pSlow == NULL || pFast == NULL || pSlow != pFast)
	{
		return NULL;
	}

	pSlow = pHead;

	while (pSlow != pFast) 
	{
		pSlow = pSlow->m_NextNode;
		pFast = pFast->m_NextNode;
	}
	return pSlow;
}

void LinkedList::splitList(Node* pRootNode, Node*& pFirstHalf, Node*& pSecondHalf)
{
	if (pRootNode == NULL)
	{
		return;
	}

	Node* pFirst = pRootNode;
	Node* pSecond = pRootNode;

	while (pFirst->m_NextNode != NULL && pFirst->m_NextNode->m_NextNode != NULL)
	{
		pFirst = pFirst->m_NextNode->m_NextNode;
		pSecond = pSecond->m_NextNode;
	}

	if (pFirst->m_NextNode && pFirst->m_NextNode->m_NextNode == NULL)
	{
		pFirst = pFirst->m_NextNode;
	}

	pFirstHalf = pRootNode;
	if (pRootNode->m_NextNode != NULL)
	{
		pSecondHalf = pSecond->m_NextNode;
		pSecond->m_NextNode = NULL;
	}
}

Node* LinkedList::mergeKSortedLists(std::vector<Node*> KLists)
{
	int nLength = KLists.size();
	if (nLength > 0)
	{
		nLength -= 1;
	}
	else
	{
		return NULL;
	}
	int nLeft = 0;
	int nRight = nLength;
	while (nLength > 0)
	{
		nLeft = 0;
		nRight = nLength;

		while (nLeft < nRight)
		{
			KLists[nLeft] = mergeAndSortLinkedLists(KLists[nLeft++], KLists[nRight--]);

			if (nLeft >= nRight)
			{
				nLength = nRight;
			}
		}
	}
	return KLists[0];
}

Node* LinkedList::mergeAndSortLinkedLists(Node* pFirstList, Node* pSecondList)
{
	Node* pResultList = NULL;
	if (pFirstList == NULL)
	{
		return pSecondList;
	}

	if (pSecondList == NULL)
	{
		return pFirstList;
	}

	if (pFirstList->m_nData <= pSecondList->m_nData)
	{
		pResultList = pFirstList;
		pResultList->m_NextNode = mergeAndSortLinkedLists(pFirstList->m_NextNode, pSecondList);
	}
	else
	{
		pResultList = pSecondList;
		pResultList->m_NextNode = mergeAndSortLinkedLists(pFirstList, pSecondList->m_NextNode);
	}

	return pResultList;
}

Node* LinkedList::AddTwoNumbers(Node* pFirstList, Node* pSecondList)
{
	Node* pResultList = NULL;
	Node* pPrev = NULL;
	Node* pTemp = NULL;
	int nCarry = 0;
	int nSum = 0;

	while (pFirstList || pSecondList)
	{
		nSum = nCarry + (pFirstList ? pFirstList->m_nData : 0) + (pSecondList ? pSecondList->m_nData : 0);
		nCarry = (nSum >= 10) ? 1 : 0;
		nSum = nSum % 10;

		pTemp = new Node(nSum);
		if (pResultList == NULL)
		{
			pResultList = pTemp;
		}
		else
		{
			pPrev->m_NextNode = pTemp;
		}

		pPrev = pTemp;

		if (pFirstList)
		{
			pFirstList = pFirstList->m_NextNode;
		}

		if (pSecondList)
		{
			pSecondList = pSecondList->m_NextNode;
		}
	}

	if (nCarry > 0)
	{
		pTemp->m_NextNode = new Node(nCarry);
	}

	return pResultList;
}

Node* LinkedList::removeNthFromEnd(Node* pHead, int nPosition)
{
	if (!pHead)
	{
		return pHead;
	}
	Node* pFirst = pHead;
	Node* pSecond = pHead;
	Node* pTemp = NULL;
	for (int nIndex = 0; nIndex < nPosition; ++nIndex)
	{
		pFirst = pFirst->m_NextNode;
	}

	if (pFirst == NULL)
	{
		pTemp = pHead;
		pHead = pHead->m_NextNode;
		delete pTemp;
	}
	else
	{
		while (pFirst->m_NextNode)
		{
			pFirst = pFirst->m_NextNode;
			pSecond = pSecond->m_NextNode;
		}
		pTemp = pSecond->m_NextNode;
		pSecond->m_NextNode = pTemp->m_NextNode;
		delete pTemp;
	}
	return pHead;
}

/*
Given a linked list, rotate the list to the right by k places, where k is non-negative.
Example 1:
Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:
Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/
Node* rotateRight(Node* pHead, int rotTimes)
{
	if (rotTimes <= 0 || !pHead || !pHead->m_NextNode)
	{
		return pHead;
	}

	Node* curr = pHead;
	int Length = 0;
	while (curr)
	{
		Length++;
		curr = curr->m_NextNode;
	}

	(rotTimes > Length) ? rotTimes = rotTimes % Length : rotTimes;
	Node* tmp = NULL;
	while (rotTimes > 0)
	{
		curr = pHead;
		while (curr && curr->m_NextNode)
		{
			if (curr->m_NextNode->m_NextNode == NULL)
			{
				tmp = curr->m_NextNode;
				curr->m_NextNode = curr->m_NextNode->m_NextNode;
				tmp->m_NextNode = pHead;
				pHead = tmp;
			}
			curr = curr->m_NextNode;
		}
		rotTimes--;
	}
	return pHead;
}

/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
*/
Node* LinkedList::partition(Node* head, int value)
{
	if (!head)
	{
		return head;
	}
	Node* newHead = NULL;
	Node* prev = NULL;
	Node* after = NULL;
	Node* tmp = NULL;

	while (head)
	{
		if (head->m_nData < value)
		{
			if (!newHead)
			{
				newHead = head;
			}
			prev = head;
			head = head->m_NextNode;
		}
		else
		{
			if (!after)
			{
				after = head;
				tmp = after;
				head = head->m_NextNode;
				tmp->m_NextNode = NULL;
			}
			else
			{
				tmp->m_NextNode = head;
				head = head->m_NextNode;
				tmp = tmp->m_NextNode;
				tmp->m_NextNode = NULL;
			}
			if (prev)
			{
				prev->m_NextNode = head;
			}
		}
	}
	(prev) ? (prev->m_NextNode ? prev->m_NextNode->m_NextNode = after : prev->m_NextNode = after) : newHead = after;
	return newHead;
}

void LinkedList::displayList(Node* pRootNode)
{
	if (!pRootNode)
	{
		return;
	}
	Node* pTemp = pRootNode;
	while (pTemp)
	{
		std::cout << pTemp->m_nData << "->";
		pTemp = pTemp->m_NextNode;
	}
	std::cout << "\n";
}