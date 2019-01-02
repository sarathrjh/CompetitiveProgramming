#include "stdafx.h"
#include <queue>
#include <deque>
#include <vector>
using namespace std;

class AvlNode
{

public:
	int m_Data;
	int m_Height;
	AvlNode* mLeftNode;
	AvlNode* mRightNode;

	AvlNode(int data) : m_Data(data), m_Height(1), mLeftNode(NULL), mRightNode(NULL)
	{

	}
};

class AvlTree
{

	AvlNode* mRootNode;
public:
	AvlTree() : mRootNode(NULL)
	{

	}

	int getHeight(const AvlNode* pAvlNode)
	{
		if (pAvlNode == NULL)
		{
			return 0;
		}
		return pAvlNode->m_Height;
	}

	int getBalanceFactor(const AvlNode* pAvlNode)
	{
		if (pAvlNode == NULL)
		{
			return 0;
		}

		return getHeight(pAvlNode->mLeftNode) - getHeight(pAvlNode->mRightNode);
	}

	/*
	T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
	*/
	AvlNode* rotateRight(AvlNode* pAvlNode)
	{
		/*
		pAvlNode		  -> z
		pCurrLeft		  -> y
		pRightOfCurrLeft  -> T3
		*/
		if (pAvlNode == NULL)
		{
			return pAvlNode;
		}

		//new root
		AvlNode* pCurrLeft = pAvlNode->mLeftNode;
		AvlNode* pRightOfCurrLeft = pCurrLeft->mRightNode;

		//Perform right rotation
		pCurrLeft->mRightNode = pAvlNode;
		pAvlNode->mLeftNode = pRightOfCurrLeft;

		pCurrLeft->m_Height = 1 + max(getHeight(pCurrLeft->mLeftNode), getHeight(pCurrLeft->mRightNode));
		pAvlNode->m_Height = 1 + max(getHeight(pAvlNode->mLeftNode), getHeight(pAvlNode->mRightNode));

		return pCurrLeft;
	}

	/*
	  z                                y
	 /  \                            /   \ 
	T1   y     Left Rotate(z)       z      x
		/  \   - - - - - - - ->    / \    / \
	   T2   x                     T1  T2 T3  T4
		   / \
		 T3  T4
	*/
	AvlNode* rotateLeft(AvlNode* pAvlNode)
	{
		/*
		pAvlNode		  -> z
		pCurrRight		  -> y
		pRightOfCurrLeft  -> T3
		*/
		if (pAvlNode == NULL)
		{
			return pAvlNode;
		}

		AvlNode* pCurrRight = pAvlNode->mRightNode;
		AvlNode* pLeftOfCurrRight = pCurrRight->mLeftNode;

		//Perform left rotation
		pCurrRight->mLeftNode = pAvlNode;
		pAvlNode->mRightNode = pLeftOfCurrRight;

		pCurrRight->m_Height = 1 + max(getHeight(pCurrRight->mLeftNode), getHeight(pCurrRight->mRightNode));
		pAvlNode->m_Height = 1 + max(getHeight(pAvlNode->mLeftNode), getHeight(pAvlNode->mRightNode));

		return pCurrRight;
	}

	AvlNode* insert(AvlNode* pAvlNode, int data)
	{
		/* 1.  Perform the normal BST insertion */
		if (pAvlNode == NULL)
		{
			pAvlNode = new AvlNode(data);
			return pAvlNode;
		}

		if (data > pAvlNode->m_Data)
		{
			insert(pAvlNode->mRightNode, data);
		}
		else if (data < pAvlNode->m_Data)
		{
			insert(pAvlNode->mLeftNode, data);
		}
		else
		{
			//Equal data are not allowed in BST 
			return pAvlNode;
		}

		/* 2. Update height of this parent node  
			  since this is a reccursive function height will be calculated from leaf to the root in that path
			  for all ancestors*/
		pAvlNode->m_Height = 1 + max(getHeight(pAvlNode->mLeftNode), getHeight(pAvlNode->mRightNode));

		/* 3. Get the balance factor of this ancestor node to check whether this node became
		unbalanced. since this is a reccursive getBalanceFactor will be calculated from leaf to the root 
		in that path for all ancestors*/
		int balance = getBalanceFactor(pAvlNode);

		// If this node becomes unbalanced, then 
		// there are 4 cases 

		//Left Left case
		if (balance > 1 && data < pAvlNode->mLeftNode->m_Data)
		{
			/*
				7						6
			/	     ----->			/		\
			6						4		7
		/
		4
			*/
			//Rotate right
			return rotateRight(pAvlNode);
		}

		//Right Right case
		if (balance < -1 && data > pAvlNode->mRightNode->m_Data)
		{
			/*
			7								9
				\	     ----->			/		\
				9						7		11
					\
					11
			*/
			//Rotate left
			return rotateLeft(pAvlNode);
		}

		//Left Right case
		if (balance > 1 && data > pAvlNode->mLeftNode->m_Data)
		{
			/*
				7					7							6
			/	     ----->				\		  ----->	/		\
			4							6					4		7
				\							\
				6							4
			*/

			//Rotate left
			pAvlNode->mLeftNode = rotateLeft(pAvlNode->mLeftNode);

			//Rotate right
			return rotateRight(pAvlNode);
		}

		//Right Left case
		if (balance < -1 && data < pAvlNode->mLeftNode->m_Data)
		{
			/*
			7						7					9
				\	     ----->			\		  ----->	/		\
				10						9					7		10
			/								\
			9								10
			*/

			//Rotate right
			pAvlNode->mRightNode = rotateRight(pAvlNode->mRightNode);

			//Rotate left
			return rotateLeft(pAvlNode);
		}

		return pAvlNode;
	}

	AvlNode* FindMax(AvlNode* root)
	{
		if (root == NULL)
		{
			return NULL;
		}

		while (root->mRightNode != NULL)
		{
			root = root->mRightNode;
		}
		return root;
	}

	AvlNode* deleteNode(AvlNode* pAvlNode, int data)
	{
		// STEP 1: PERFORM STANDARD BST DELETE 

		if (pAvlNode = NULL)
		{
			return pAvlNode;
		}
		else if (data < pAvlNode->m_Data)
		{
			deleteNode(pAvlNode->mLeftNode, data);
		}
		else if (data > pAvlNode->m_Data)
		{
			deleteNode(pAvlNode->mRightNode, data);
		}
		else
		{
			//No child
			if (pAvlNode->mLeftNode == NULL && pAvlNode->mRightNode == NULL)
			{

				delete pAvlNode;
				pAvlNode = NULL;
			}
			//only left child
			else if (pAvlNode->mLeftNode != NULL && pAvlNode->mRightNode == NULL)
			{
				AvlNode* pTemp = pAvlNode;
				pAvlNode = pAvlNode->mLeftNode;
				delete pTemp;
			}
			//only right child
			else if (pAvlNode->mLeftNode == NULL && pAvlNode->mRightNode != NULL)
			{
				AvlNode* pTemp = pAvlNode;
				pAvlNode = pAvlNode->mRightNode;
				delete pTemp;
			}
			//has two childs
			else
			{
				AvlNode* pTemp = FindMax(pAvlNode->mLeftNode);
				pAvlNode->m_Data = pTemp->m_Data;
				//pAvlNode->mLeftNode will be assigned with NULL, when the max node is deleted, which is the last node.
				pAvlNode->mLeftNode = deleteNode(pAvlNode->mLeftNode, pTemp->m_Data);
			}
		}

		// If the tree had only one node then return 
		if (pAvlNode == NULL)
		{
			return pAvlNode;
		}

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
		pAvlNode->m_Height = 1 + max(getHeight(pAvlNode->mLeftNode), getHeight(pAvlNode->mRightNode));

		/* 3. Get the balance factor of this ancestor node to check whether this node became
		unbalanced. since this is a reccursive getBalanceFactor will be calculated from leaf to the root
		in that path for all ancestors*/
		int balance = getBalanceFactor(pAvlNode);

		// If this node becomes unbalanced, then there are 4 cases 

		// Left Left Case 
		if (balance > 1 && getBalanceFactor(pAvlNode->mLeftNode) >= 0)
		{
			return rotateRight(pAvlNode);
		}

		// Left Right Case 
		if (balance > 1 && getBalanceFactor(pAvlNode->mLeftNode) < 0)
		{
			pAvlNode->mLeftNode = rotateLeft(pAvlNode->mLeftNode);
			return rotateRight(pAvlNode);
		}

		// Right Right Case 
		if (balance < -1 && getBalanceFactor(pAvlNode->mRightNode) <= 0)
		{
			return rotateLeft(pAvlNode);
		}

		// Right Left Case 
		if (balance < -1 && getBalanceFactor(pAvlNode->mRightNode) > 0)
		{
			pAvlNode->mRightNode = rotateRight(pAvlNode->mRightNode);
			return rotateLeft(pAvlNode);
		}

		return pAvlNode;
	}

};