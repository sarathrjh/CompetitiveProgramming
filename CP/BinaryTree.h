#include "stdafx.h"
#include <queue>
#include <deque>
#include <vector>
using namespace std;
class BNode
{
public:
	BNode(int nData) : m_nData(nData), m_LeftNode(NULL), m_RightNode(NULL)
	{

	}

	int m_nData;
	BNode* m_LeftNode;
	BNode* m_RightNode;
};


class BinaryTree
{
public:

	BinaryTree()
	{

	}

	void swap(int& First, int& Second)
	{
		int nTemp = First;
		First = Second;
		Second = nTemp;
	}

	void insertNode(BNode *pRootNode, int nValue)
	{
		if (pRootNode)
		{
			if (nValue < pRootNode->m_nData)
			{
				if (pRootNode->m_LeftNode)
				{
					insertNode(pRootNode->m_LeftNode, nValue);
				}
				else
				{
					pRootNode->m_LeftNode = new BNode(nValue);
				}
			}
			else if (nValue > pRootNode->m_nData)
			{
				if (pRootNode->m_RightNode)
				{
					insertNode(pRootNode->m_RightNode, nValue);
				}
				else
				{
					pRootNode->m_RightNode = new BNode(nValue);
				}
			}
		}
	}

	BNode* searchTree(BNode *pRootNode, int nValue)
	{
		if (pRootNode)
		{
			if (pRootNode->m_nData == nValue)
			{
				return pRootNode;
			}
			else if (nValue < pRootNode->m_nData)
			{
				return searchTree(pRootNode->m_LeftNode, nValue);
			}
			else if (nValue > pRootNode->m_nData)
			{
				return searchTree(pRootNode->m_RightNode, nValue);
			}
		}
	}

	BNode* FindMax(BNode* root)
	{
		if (root == NULL)
			return NULL;

		while (root->m_RightNode != NULL)
		{
			root = root->m_RightNode;
		}
		return root;
	}

	int heightOfBtree(BNode* pRoot)
	{
		if (!pRoot)
			return 0;
		int nLeftHeight = heightOfBtree(pRoot->m_LeftNode);
		int nRightHeight = heightOfBtree(pRoot->m_RightNode);
		return 1 + max(nLeftHeight, nRightHeight);
	}

	/*
	Given a binary tree, find its minimum depth.
	The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
	Note: A leaf is a node with no children.

	Example:
	Given binary tree [3,9,20,null,null,15,7],

		3
	   / \
	  9  20
		/  \
	   15   7
	return its minimum depth = 2.
	*/
	int minDepth(BNode *root)
	{
		// Corner case. Should never be hit unless the code is 
		// called on root = NULL
		if (root == NULL)
			return 0;

		// Base case : Leaf Node. This accounts for height = 1.
		if (root->m_LeftNode == NULL && root->m_RightNode == NULL)
			return 1;

		// If left subtree is NULL, recur for right subtree
		if (!root->m_LeftNode)
			return minDepth(root->m_RightNode) + 1;

		// If right subtree is NULL, recur for left subtree
		if (!root->m_RightNode)
			return minDepth(root->m_LeftNode) + 1;

		return min(minDepth(root->m_LeftNode), minDepth(root->m_RightNode)) + 1;
	}

	/* Function to get the maximum width of a binary tree*/
	int getMaxWidth(BNode* pRoot)
	{
		int maxWidth = 0;
		int width;
		int h = heightOfBtree(pRoot);
		int i;

		/* Get width of each level and compare
		the width with maximum width so far */
		for (i = 1; i <= h; i++)
		{
			width = getWidth(pRoot, i);
			if (width > maxWidth)
				maxWidth = width;
		}

		return maxWidth;
	}

	/* Get width of a given level */
	int getWidth(BNode* pRoot, int level)
	{

		if (pRoot == NULL)
			return 0;

		if (level == 1)
			return 1;

		else if (level > 1)
			return getWidth(pRoot->m_LeftNode, level - 1) +
			getWidth(pRoot->m_RightNode, level - 1);
	}

	void ReverseQueue(std::deque<BNode*>& NodeQue)
	{
		int nStart = 0;
		int nEnd = NodeQue.size() - 1;
		while (nStart < nEnd)
		{
			int nTemp = NodeQue[nStart]->m_nData;
			NodeQue[nStart]->m_nData = NodeQue[nEnd]->m_nData;
			NodeQue[nEnd]->m_nData = nTemp;
			nStart++;
			nEnd--;
		}
	}

	void printLevelNodes(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			printf("Empty tree\n");
			return;
		}

		int nCurLevel = 0;
		int nCount = 0;
		std::queue<BNode*> NodeQue;
		NodeQue.push(pRoot);
		while (!NodeQue.empty())
		{
			nCurLevel++;
			nCount = NodeQue.size();
			while (nCount--)
			{
				BNode *temp = NodeQue.front();
				NodeQue.pop();
				printf("%d ", temp->m_nData);

				if (temp->m_LeftNode != NULL)
					NodeQue.push(temp->m_LeftNode);
				if (temp->m_RightNode != NULL)
					NodeQue.push(temp->m_RightNode);
			}
			printf("\n");
		}

	}

	//print btree 's' model
	void printSModel(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			printf("Empty tree\n");
			return;
		}

		int nCurLevel = 0;
		int nCount = 0;
		std::deque<BNode*> NodeQue;
		NodeQue.push_back(pRoot);
		while (!NodeQue.empty())
		{
			nCurLevel++;
			nCount = NodeQue.size();
			while (nCount--)
			{
				BNode *temp = NodeQue.front();
				NodeQue.pop_front();
				printf("%d ", temp->m_nData);

				if (temp->m_LeftNode != NULL)
					NodeQue.push_back(temp->m_LeftNode);
				if (temp->m_RightNode != NULL)
					NodeQue.push_back(temp->m_RightNode);
			}
			printf("\n");
			if ((nCurLevel + 1) % 2 != 0)
			{
				ReverseQueue(NodeQue);
			}
		}
	}

	/*
	Given a Perfect Binary Tree, reverse the alternate level nodes of the binary tree.
	Given tree: 
				   a
				/     \
			   b       c
			 /  \     /  \
			d    e    f    g
		   / \  / \  / \  / \
		   h  i j  k l  m  n  o 

	Modified tree:
				 a
				/     \
			   c       b
			 /  \     /  \
			d    e    f    g
		   / \  / \  / \  / \
		  o  n m  l k  j  i  h 
	*/
	void printSModelPerfectBinaryTree(BNode *root1, BNode* root2, int level)
	{
		// Base cases
		if (root1 == NULL || root2 == NULL)
			return;

		// Swap subtrees if level is even
		if (level % 2 == 0)
			swap(root1->m_nData, root2->m_nData);

		// Recur for left and right subtrees (Note : left of root1
		// is passed and right of root2 in first call and opposite
		// in second call.
		printSModelPerfectBinaryTree(root1->m_LeftNode, root2->m_RightNode, level + 1);
		printSModelPerfectBinaryTree(root1->m_RightNode, root2->m_LeftNode, level + 1);
	}

	void reverseAlternate(BNode *root)
	{
		printSModelPerfectBinaryTree(root->m_LeftNode, root->m_RightNode, 0);
	}


	/*
	Given a binary tree, write a function to get the maximum width of the given tree. 
	The width of a tree is the maximum width among all levels. The binary tree has the 
	same structure as a full binary tree, but some nodes are null.

	The width of one level is defined as the length between the end-nodes 
	(the leftmost and right most non-null nodes in the level, where the null nodes
	between the end-nodes are also counted into the length calculation.

	Example 1:
	Input: 

			   1
			 /   \
			3     2
		   / \     \  
		  5   3     9 

	Output: 4
	Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
	Example 2:
	Input: 

			  1
			 /  
			3    
		   / \       
		  5   3     

	Output: 2
	Explanation: The maximum width existing in the third level with the length 2 (5,3).
	Example 3:
	Input: 

			  1
			 / \
			3   2 
		   /        
		  5      

	Output: 2
	Explanation: The maximum width existing in the second level with the length 2 (3,2).
	Example 4:
	Input: 

			  1
			 / \
			3   2
		   /     \  
		  5       9 
		 /         \
		6           7
	Output: 8
	Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
	*/
	int maxwidthOfComBinaryTree(BNode* root) 
	{
		// Base case
		if (root == NULL)
			return 0;

		// Initialize result
		int result = 0;

		// Do Level order traversal keeping track of number
		// of nodes at every level.
		std::queue<std::pair<BNode*, int>> levelQue;
		levelQue.push(std::make_pair(root, 0));
		int Size = 0;
		int Count = 0;
		int start = 0;
		int end = 0;
		while (!levelQue.empty())
		{
			// Get the size of queue when the level order
			// traversal for one level finishes
			Size = levelQue.size();
			Count = 0;

			// Iterate for all the nodes in the queue currently
			while (Count < Size)
			{
				// Dequeue an node from queue
				auto cur = levelQue.front();
				levelQue.pop();

				if (Count == 0)
				{
					start = cur.second;
				}
				end = cur.second;
				// Enqueue left and right children of
				// dequeued node
				if (cur.first->m_LeftNode != NULL)
					levelQue.push(std::make_pair(cur.first->m_LeftNode, cur.second * 2));
				if (cur.first->m_RightNode != NULL)
					levelQue.push(std::make_pair(cur.first->m_RightNode, cur.second * 2 + 1));
				Count++;
			}

			// Update the maximum node count value
			result = max(result, end - start + 1);
		}

		return result;

	}

	// Function to find the maximum width of the tree
	// using level order traversal
	int maxWidth(BNode* pRoot)
	{
		// Base case
		if (pRoot == NULL)
			return 0;

		// Initialize result
		int result = 0;

		// Do Level order traversal keeping track of number
		// of nodes at every level.
		std::queue<BNode*> q;
		q.push(pRoot);
		while (!q.empty())
		{
			// Get the size of queue when the level order
			// traversal for one level finishes
			int count = q.size();

			// Update the maximum node count value
			result = max(count, result);

			// Iterate for all the nodes in the queue currently
			while (count--)
			{
				// Dequeue an node from queue
				BNode *temp = q.front();
				q.pop();

				// Enqueue left and right children of
				// dequeued node
				if (temp->m_LeftNode != NULL)
					q.push(temp->m_LeftNode);
				if (temp->m_RightNode != NULL)
					q.push(temp->m_RightNode);
			}
		}

		return result;
	}

	/* The function returns true if root is balanced else false
	The second parameter is to store the height of tree.
	Initially, we need to pass a pointer to a location with value
	as 0. We can also write a wrapper over this function */
	bool isBalanced(BNode* pRoot, int& height)
	{
		/* lh --> Height of left subtree
		rh --> Height of right subtree */
		int lh = 0, rh = 0;

		/* l will be true if left subtree is balanced
		and r will be true if right subtree is balanced */
		int l = 0, r = 0;

		if (pRoot == NULL)
		{
			height = 0;
			return 1;
		}

		/* Get the heights of left and right subtrees in lh and rh
		And store the returned values in l and r */
		l = isBalanced(pRoot->m_LeftNode, lh);
		r = isBalanced(pRoot->m_RightNode, rh);

		/* Height of current node is max of heights of left and
		right subtrees plus 1*/
		height = max(lh, rh) + 1;

		/* If difference between heights of left and right
		subtrees is more than 2 then this node is not balanced
		so return 0 */
		if ((lh - rh >= 2) || (rh - lh >= 2))
			return 0;

		/* If this node is balanced and left and right subtrees
		are balanced then return true */
		else return l&&r;
	}

	int getHeight(BNode* root) 
	{
		if (root == NULL)
			return 0;

		int left = getHeight(root->m_LeftNode);
		int right = getHeight(root->m_RightNode);

		if (left == -1 || right == -1)
			return -1;

		if (abs(left - right) > 1) {
			return -1;
		}

		return max(left, right) + 1;
	}

	bool isBalanced(BNode* root) 
	{
		if (root == NULL)
			return true;

		if (getHeight(root) == -1)
			return false;

		return true;
	}

	int diameterOpt(BNode* pRoot, int& height)
	{
		/* lh --> Height of left subtree
		rh --> Height of right subtree */
		int lh = 0, rh = 0;

		/* ldiameter  --> diameter of left subtree
		rdiameter  --> Diameter of right subtree */
		int ldiameter = 0, rdiameter = 0;

		if (pRoot == NULL)
		{
			height = 0;
			return 0; /* diameter is also 0 */
		}

		/* Get the heights of left and right subtrees in lh and rh
		And store the returned values in ldiameter and ldiameter */
		ldiameter = diameterOpt(pRoot->m_LeftNode, lh);
		rdiameter = diameterOpt(pRoot->m_RightNode, rh);

		/* Height of current node is max of heights of left and
		right subtrees plus 1*/
		height = max(lh, rh) + 1;

		return max(lh + rh + 1, max(ldiameter, rdiameter));
	}

	/* This function tests if a binary tree is a full binary tree. */
	bool isFullTree(BNode* pRoot)
	{
		// If empty tree
		if (pRoot == NULL)
			return true;

		// If leaf node
		if (pRoot->m_LeftNode == NULL && pRoot->m_RightNode == NULL)
			return true;

		// If both left and right are not NULL, and left & right subtrees
		// are full
		if ((pRoot->m_LeftNode) && (pRoot->m_RightNode))
			return (isFullTree(pRoot->m_LeftNode) && isFullTree(pRoot->m_RightNode));

		// We reach here when none of the above if conditions work
		return false;
	}

	BNode* DeleteNodeInBST(BNode* root, int data)
	{
		if (root == NULL) return root;
		else if (data < root->m_nData)
			root->m_LeftNode = DeleteNodeInBST(root->m_LeftNode, data);
		else if (data> root->m_nData)
			root->m_RightNode = DeleteNodeInBST(root->m_RightNode, data);
		else
		{
			//No child
			if (root->m_RightNode == NULL && root->m_LeftNode == NULL)
			{
				delete root;
				root = NULL;
			}
			//One child 
			else if (root->m_RightNode == NULL)
			{
				BNode* temp = root;
				root = root->m_LeftNode;
				delete temp;
			}
			else if (root->m_LeftNode == NULL)
			{
				BNode* temp = root;
				root = root->m_RightNode;
				delete temp;
			}
			//two child
			else
			{
				BNode* temp = FindMax(root->m_LeftNode);
				root->m_nData = temp->m_nData;
				//root->m_LeftNode will be assigned with NULL, when the max node is deleted, which is the last node.
				root->m_LeftNode = DeleteNodeInBST(root->m_LeftNode, temp->m_nData);
			}
		}
		return root;
	}


	void preOrderTraversal(BNode* pRoot)
	{
		if (pRoot)
		{
			printf("%d ", pRoot->m_nData);
			preOrderTraversal(pRoot->m_LeftNode);
			preOrderTraversal(pRoot->m_RightNode);
		}
	}

	void inOrderTraversal(BNode* pRoot)
	{
		if (pRoot)
		{
			inOrderTraversal(pRoot->m_LeftNode);
			printf("%d ", pRoot->m_nData);
			inOrderTraversal(pRoot->m_RightNode);
		}
	}


	void postOrderTraversal(BNode* pRoot)
	{
		if (pRoot)
		{
			postOrderTraversal(pRoot->m_LeftNode);
			postOrderTraversal(pRoot->m_RightNode);
			printf("%d ", pRoot->m_nData);
		}
	}

	bool isBST(BNode* pRoot, BNode* pLeft = NULL, BNode* pRight = NULL)
	{
		// Base condition
		if (pRoot == NULL)
		{
			return true;
		}

		// if left node exist then check it has
		// correct data or not i.e. left node's data
		// should be less than root's data
		if (pLeft != NULL && pRoot->m_nData < pLeft->m_nData)
		{
			return false;
		}

		// if right node exist then check it has
		// correct data or not i.e. right node's data
		// should be greater than root's data
		if (pRight != NULL && pRoot->m_nData > pRight->m_nData)
		{
			return false;
		}

		// check recursively for every node.
		return isBST(pRoot->m_LeftNode, pLeft, pRoot) && isBST(pRoot->m_RightNode, pRoot, pRight);
	}

	// function to return sum of all elements larger than
	// and equal to Kth largest element
	int klargestElementSum(BNode* pRoot, int kNums, int& nCount)
	{
		// Base cases
		if (pRoot == NULL)
		{
			return 0;
		}
		if (nCount > kNums)
		{
			return 0;
		}

		// Compute sum of elements in right subtree
		int result = klargestElementSum(pRoot->m_RightNode, kNums, nCount);
		if (nCount >= kNums)
		{
			return result;
		}

		// Add root's data
		result += pRoot->m_nData;

		// Add current Node
		nCount++;
		if (nCount >= kNums)
		{
			return result;
		}

		// If c is less than k, return left subtree Nodes
		return result + klargestElementSum(pRoot->m_LeftNode, kNums, nCount);
	}

	int addNodeData(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}

		return pRoot->m_nData + addNodeData(pRoot->m_LeftNode) + addNodeData(pRoot->m_RightNode);
	}

	int isSumTree(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 1;
		}

		if (pRoot->m_LeftNode == NULL && pRoot->m_RightNode == NULL)
		{
			return 1;
		}

		if (pRoot->m_nData == addNodeData(pRoot->m_LeftNode) + addNodeData(pRoot->m_RightNode))
		{
			if (isSumTree(pRoot->m_LeftNode) && isSumTree(pRoot->m_RightNode))
			{
				return 1;
			}
		}
		return 0;
	}

	int isSumTreeOptimised(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}

		if (pRoot->m_LeftNode == NULL && pRoot->m_RightNode == NULL)
		{
			return pRoot->m_nData;
		}

		if (pRoot->m_nData == isSumTreeOptimised(pRoot->m_LeftNode) + isSumTreeOptimised(pRoot->m_RightNode))
		{
			return 2 * pRoot->m_nData;
		}
		return -1;
	}

	int convertToNewSumTree(BNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}

		int nOldValue = pRoot->m_nData;
		pRoot->m_nData = convertToNewSumTree(pRoot->m_LeftNode) + convertToNewSumTree(pRoot->m_RightNode);

		return nOldValue + pRoot->m_nData;

	}

	bool rootToLeafSum(BNode* pRoot, int nSum, std::vector<int>& ResultPath)
	{
		if (pRoot == NULL)
		{
			return false;
		}

		//Leaf node

		if (pRoot->m_LeftNode == NULL && pRoot->m_RightNode == NULL)
		{
			if (pRoot->m_nData == nSum)
			{
				ResultPath.push_back(pRoot->m_nData);
				return true;
			}
			return false;
		}

		//Left node
		if (rootToLeafSum(pRoot->m_LeftNode, nSum - pRoot->m_nData, ResultPath))
		{
			ResultPath.push_back(pRoot->m_nData);
			return true;
		}

		//Right node
		if (rootToLeafSum(pRoot->m_RightNode, nSum - pRoot->m_nData, ResultPath))
		{
			ResultPath.push_back(pRoot->m_nData);
			return true;
		}

		return false;
	}

	void ReverseAlternateLevelNodesOfPerfectBT(BNode* pFirstNode, BNode* pSecondNode, int nLevel)
	{
		if (pFirstNode == NULL || pSecondNode == NULL)
		{
			return;
		}

		if (nLevel % 2 == 0)
		{
			swap(pFirstNode->m_nData, pSecondNode->m_nData);
		}

		ReverseAlternateLevelNodesOfPerfectBT(pFirstNode->m_LeftNode, pSecondNode->m_RightNode, nLevel + 1);
		ReverseAlternateLevelNodesOfPerfectBT(pFirstNode->m_RightNode, pSecondNode->m_LeftNode, nLevel + 1);
	}

	/*
	Write a function which accepts the root of a tree, and returns a Linked List
	which contains the leaf nodes of the tree from left to right order.*/
	BNode* extractLeafNodesAndCreateLinkListFromLeftToRight(BNode* pRoot, BNode** pHead)
	{
		if (!pRoot)
		{
			return NULL;
		}

		//Leaf node with left and right are null.
		if (pRoot->m_LeftNode == NULL && pRoot->m_RightNode == NULL)
		{
			//since we are traversing from right, the leaf nodes are from right to left
			//Add leaf nodes to head of linked list, so at last left most node will be the head
			//and right most leaft node will be the tail end of Linkedlist.
			pRoot->m_RightNode = *pHead;
			if(*pHead)
				(*pHead)->m_LeftNode = pRoot;
			*pHead = pRoot;
			//delete pRoot;
			return NULL;
		}

		//traverse tree from right.
		pRoot->m_RightNode = extractLeafNodesAndCreateLinkListFromLeftToRight(pRoot->m_RightNode, pHead);
		pRoot->m_LeftNode = extractLeafNodesAndCreateLinkListFromLeftToRight(pRoot->m_LeftNode, pHead);

		return pRoot;
	}

	/*
	Given a binary tree containing n nodes. The problem is to find the sum of all nodes
	on the longest path from root to leaf node. If two or more paths compete for the longest 
	path, then the path having maximum sum of nodes is being considered.

	Examples:

	Input : Binary tree:
			4        
		   / \       
		  2   5      
		 / \ / \     
		7  1 2  3    
		  /
		 6
	Output : 13
	The highlighted nodes (4, 2, 1, 6) above are
	part of the longest root to leaf path having
	sum = (4 + 2 + 1 + 6) = 13
	*/
	void maxSumOfLongestPathFromRootToLeafNode(BNode* pRoot, int sum, int Length, int& maxLength, int& maxSum)
	{
		if (!pRoot)
		{
			if (maxLength < Length)
			{
				maxLength = Length;
				maxSum = sum;
			}
			else if (maxLength == Length)
			{
				maxSum = max(maxSum, sum);
			}
			return;
		}

		maxSumOfLongestPathFromRootToLeafNode(pRoot->m_LeftNode, sum + pRoot->m_nData, Length + 1, maxLength, maxSum);
		maxSumOfLongestPathFromRootToLeafNode(pRoot->m_RightNode, sum + pRoot->m_nData, Length + 1, maxLength, maxSum);
	}

	// utility function to find the sum of nodes on
	// the longest path from root to leaf node
	int sumOfLongRootToLeafPathUtil(BNode* root)
	{
		// if tree is NULL, then sum is 0
		if (!root)
			return 0;

		int maxSum = INT_MIN, maxLen = 0;

		// finding the maximum sum 'maxSum' for the
		// maximum length root to leaf path
		maxSumOfLongestPathFromRootToLeafNode(root, 0, 0, maxLen, maxSum);

		// required maximum sum
		return maxSum;
	}

	/*
	Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
	For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of
	the two subtrees of every node never differ by more than 1.

	Example:
	Given the sorted array: [-10,-3,0,5,9],
	One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

		  0
		 / \
	   -3   9
	   /   /
	 -10  5
	*/
	BNode* convertToBST(vector<int>& nums, int low, int high)
	{
		if (low > high)
		{
			return NULL;
		}

		int mid = (low + high) / 2;
		BNode* root = new BNode(nums[mid]);
		root->m_LeftNode = convertToBST(nums, low, mid - 1);
		root->m_RightNode = convertToBST(nums, mid + 1, high);
		return root;
	}

	BNode* sortedArrayToBST(vector<int>& nums)
	{
		return convertToBST(nums, 0, nums.size() - 1);
	}

	/*
	Given a binary tree, flatten it to a linked list in-place.

	For example, given the following tree:

		1
	   / \
	  2   5
	 / \   \
	3   4   6
	The flattened tree should look like:

	1
	 \
	  2
	   \
		3
		 \
		  4
		   \
			5
			 \
			  6
	*/
	// Function to convert binary tree into
	// linked list by altering the right node
	// and making left node point to NULL
	void flatten(BNode* root)
	{
		// base condition- return if root is NULL
		// or if it is a leaf node
		if (root == NULL || root->m_LeftNode == NULL && root->m_RightNode == NULL)
		{
			return;
		}

		// if root->left exists then we have 
		// to make it root->right
		if (root->m_LeftNode)
		{
			// move left recursively
			flatten(root->m_LeftNode);

			// store the node root->right
			BNode* tmpRight = root->m_RightNode;
			root->m_RightNode = root->m_LeftNode;
			root->m_LeftNode = NULL;

			// find the position to insert
			// the stored value   
			BNode* tmp = root->m_RightNode;
			while (tmp->m_RightNode) 
			{
				tmp = tmp->m_RightNode;
			}

			// insert the stored value
			tmp->m_RightNode = tmpRight;
		}

		// now call the same function
		// for root->right
		flatten(root->m_RightNode);
	}
};