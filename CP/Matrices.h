#include "stdafx.h"
#include <iostream>
#include <string>
#include <ostream>

class Matrix
{
public:
	Matrix(){}

	void matrixTranspose(int Matrix1[][5], int outputmatrix[][3], int row1, int col1)
	{
		for (int nRowIndex = 0; nRowIndex < row1; nRowIndex++)
		{
			for (int nColIndex = 0; nColIndex < col1; nColIndex++)
			{
				outputmatrix[nColIndex][nRowIndex] = Matrix1[nRowIndex][nColIndex];
			}
		}
	}

	void matrixMultiplication(int Matrix1[][3], int Matrix2[][5], int outputmatrix[][3], int row1, int col1, int row2, int col2)
	{
		for (int nrow = 0; nrow < row2; ++nrow)
		{
			for (int ncol = 0; ncol < col1; ++ncol)
			{
				outputmatrix[nrow][ncol] = 0;
			}
		}

		if (col1 != row2)
			return;
		for (int nRowIndex = 0; nRowIndex < row1; nRowIndex++)
		{
			for (int nColIndex = 0; nColIndex < col2; nColIndex++)
			{
				for (int nOutIndex = 0; nOutIndex < col1; nOutIndex++)
				{
					outputmatrix[nRowIndex][nColIndex] += Matrix1[nRowIndex][nOutIndex] * Matrix2[nOutIndex][nColIndex];
				}
			}
		}
	}

	Convert to Cartesian :

	cartesianx = screenx - screenwidth / 2;
	cartesiany = -screeny + screenheight / 2;
	Convert to Screen :

	screenx = cartesianx + screenwidth / 2;
	screeny = -cartesiany + screenheight / 2;

	void mirrorLeftRight()
	{
		for (int x = 0; x < width / 2; x++) {
			for (int y = 0; y < height; y++) {
				int temp = pixelData[x][y];
				pixelData[x][y] = pixelData[width - x][y]
					pixelData[width - x][y] = temp;
			}
		}
	}

	void mirrorUpDown()
	{
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height / 2; y++) {
				int temp = pixelData[x][y];
				pixelData[x][y] = pixelData[x][height - y]
					pixelData[x][height - y] = temp;
			}
		}
	}

	With mirror I would guess that you need to change

		int temp = pixelData[x][y];
	pixelData[x][y] = pixelData[width - x][y]
		pixelData[width - x][y] = temp;
	to something like this only

	pixelData[x][y] = pixelData[width - x][y]
	You need to use width - 1 - x instead of width - x, and height - 1 - y instead of height - y.
	Otherwise for x == 0 you'll try to index [width], which is outside the array.

	// Function that return
	// dot product of two vector array.
	int dotProduct(int vect_A[], int vect_B[])
	{

		int product = 0;

		// Loop for calculate cot product
		for (int i = 0; i < n; i++)

			product = product + vect_A[i] * vect_B[i];
		return product;
	}

	// Function to find
	// cross product of two vector array.
	void crossProduct(int vect_A[], int vect_B[], int cross_P[])

	{

		cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
		cross_P[1] = vect_A[0] * vect_B[2] - vect_A[2] * vect_B[0];
		cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
	}



	void CGraphics2DView::Rotate(MATRIX3X3& m, int degrees)
	{
		MATRIX3X3 m1, m2;

		if (degrees == 0) return;

		double radians = 6.283185308 / (360.0 / degrees);
		double c = cos(radians);
		double s = sin(radians);

		m1[0][0] = c; m1[0][1] = s; m1[0][2] = 0;
		m1[1][0] = -s; m1[1][1] = c; m1[1][2] = 0;
		m1[2][0] = 0; m1[2][1] = 0; m1[2][2] = 1;

		MultMatrix(m2, m1, m);
		CopyMatrix(m, m2);
	}

	First Cycle(Involves Red Elements)
		1  2  3 4
		5  6  7  8
		9 10 11 12
		13 14 15 16


		Moving first group of four elements(First
		elements of 1st row, last row, 1st column
		and last column) of first cycle in counter
		clockwise.
		4  2  3 16
		5  6  7 8
		9 10 11 12
		1 14  15 13

		Moving next group of four elements of
		first cycle in counter clockwise
		4  8  3 16
		5  6  7  15
		2  10 11 12
		1  14  9 13

		Moving final group of four elements of
		first cycle in counter clockwise
		4  8 12 16
		3  6  7 15
		2 10 11 14
		1  5  9 13


		Second Cycle(Involves Blue Elements)
		4  8 12 16
		3  6 7  15
		2  10 11 14
		1  5  9 13

		Fixing second cycle
		4  8 12 16
		3  7 11 15
		2  6 10 14
		1  5  9 13
	// An Inplace function to rotate a N x N matrix
	// by 90 degrees in anti-clockwise direction
	void rotateMatrix(int mat[][N])
	{
		// Consider all squares one by one
		for (int x = 0; x < N / 2; x++)
		{
			// Consider elements in group of 4 in 
			// current square
			for (int y = x; y < N - x - 1; y++)
			{
				// store current cell in temp variable
				int temp = mat[x][y];

				// move values from right to top
				mat[x][y] = mat[y][N - 1 - x];

				// move values from bottom to right
				mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

				// move values from left to bottom
				mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

				// assign temp to left
				mat[N - 1 - y][x] = temp;
			}
		}
	}

	public static void reverseElementsRowWise(int[][] matrix) {
		int n = matrix.length;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n / 2; ++j) {
				int temp = matrix[i][n - j - 1];
				matrix[i][n - j - 1] = matrix[i][j];
				matrix[i][j] = temp;
			}
		}
	}

	public static void transpose(int[][] matrix) {
		int n = matrix.length;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[j][i];
				matrix[j][i] = temp;
			}
		}
	}

	// Using macros to convert degree to radian
	// and call sin() and cos() as these functions
	// take input in radians
#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)  

	// To rotate an object
	void rotate(float a[][2], int n, int x_pivot,
		int y_pivot, int angle)
	{
		int i = 0;
		while (i < n)
		{
			// Shifting the pivot point to the origin
			// and the given points accordingly
			int x_shifted = a[i][0] - x_pivot;
			int y_shifted = a[i][1] - y_pivot;

			// Calculating the rotated point co-ordinates
			// and shifting it back
			a[i][0] = x_pivot + (x_shifted*COS(angle)
				- y_shifted*SIN(angle));
			a[i][1] = y_pivot + (x_shifted*SIN(angle)
				+ y_shifted*COS(angle));
			printf("(%f, %f) ", a[i][0], a[i][1]);
			i++;
		}
	}

	// Driver Code
	int main()
	{
		// 1st Example
		// The following figure is to be 
		// rotated about (0, 0) by 90 degrees
		int size1 = 4;//No. of vertices

		// Vertex co-ordinates must be in order
		float points_list1[][2] = { { 100, 100 }, { 150, 200 },
		{ 200, 200 }, { 200, 150 } };
		rotate(points_list1, size1, 0, 0, 90);

		// 2nd Example
		// The following figure is to be 
		// rotated about (50, -50) by -45 degrees
		/*int size2 = 3;//No. of vertices
		float points_list2[][2] = {{100, 100}, {100, 200},
		{200, 200}};
		rotate(points_list2, size2, 50, -50, -45);*/
		return 0;
	}

	/* A function that constructs Balanced Binary Search Tree from a sorted array */
	struct TNode* sortedArrayToBST(int arr[], int start, int end)
	{
		/* Base Case */
		if (start > end)
			return NULL;

		/* Get the middle element and make it root */
		int mid = (start + end) / 2;
		struct TNode *root = newNode(arr[mid]);

		/* Recursively construct the left subtree and make it
		left child of root */
		root->left = sortedArrayToBST(arr, start, mid - 1);

		/* Recursively construct the right subtree and make it
		right child of root */
		root->right = sortedArrayToBST(arr, mid + 1, end);

		return root;
	}

};

/*
write a class that takes a string in the constructor and then uses the operator <<
to output the number of occurrences of 3 letter words in the string
Ex: "The fox jumped over one dog." -> 4

ThreeLetterWords c("The  ,   fox jumped over one dog.");
cout << c;
*/

class MyString
{
public:

	MyString(std::string strData);

	int GetCount() const
	{
		return m_nCount;
	}

private:

	std::string m_strData;
	int m_nCount;
};

MyString::MyString(std::string strData)
{
	m_nCount = 0;
	int nFirstIndex = 0;
	int nSecondIndex = 0;
	int nCharIndex = 0;

	while (strData[nCharIndex])
	{
		if (strData[nCharIndex] == ' ' || strData[nCharIndex] == '.' || strData[nCharIndex] == ',')
		{
			nSecondIndex = nCharIndex;
			if (nSecondIndex - nFirstIndex == 3)
			{
				m_nCount++;
			}

			nFirstIndex = nCharIndex + 1;
		}
		nCharIndex++;
	}

	nSecondIndex = nCharIndex;
	if (nSecondIndex - nFirstIndex == 3)
	{
		m_nCount++;
	}
}


std::ostream& operator<<(std::ostream& out, const MyString& strInput)
{
	out << strInput.GetCount();
	return out;
}
