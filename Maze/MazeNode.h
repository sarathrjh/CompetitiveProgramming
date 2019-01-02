#include "stdafx.h"


/**
 * This class represents (x,y) coordinates.
 */
class Coordinates
{
public:
	int m_nXPoint;
	int m_nYPoint;

	//Constructor
	Coordinates(int nXPoint = 0, int nYPoint = 0);

	//Copy Constructor
	Coordinates(const Coordinates& nodeCoordinates);

	// "==" Operator overloading
	bool operator== (const Coordinates& nodeCoordinates) const;
	
};


/**
 * This class represents each node or vertex of maze.
 * Each node contains its coordinates, distance to its
 * nearest exit and its four nieghbours(left, right, up and down).
 */
class MazeNode
{
public:
	MazeNode(Coordinates nodeCoordinate, int nDistance);
	~MazeNode();

	Coordinates m_NodeCoordinates;
	int m_nDistanceToNearestExit;
	MazeNode* m_LeftNode;
	MazeNode* m_RightNode;
	MazeNode* m_UpNode;
	MazeNode* m_DownNode;
};