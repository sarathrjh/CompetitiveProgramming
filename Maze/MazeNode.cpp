#include "MazeNode.h"

Coordinates::Coordinates(int nXPoint, int nYPoint) :
					     m_nXPoint(nXPoint),
					     m_nYPoint(nYPoint)
{
	
}

Coordinates::Coordinates(const Coordinates& nodeCoordinates)
{
	m_nXPoint = nodeCoordinates.m_nXPoint;
	m_nYPoint = nodeCoordinates.m_nYPoint;
}

bool Coordinates::operator== (const Coordinates& nodeCoordinates) const
{
	if (m_nXPoint == nodeCoordinates.m_nXPoint && m_nYPoint == nodeCoordinates.m_nYPoint)
	{
		return true;
	}
	return false;
}


MazeNode::MazeNode(Coordinates nodeCoordinates, int nDistance) :
					m_NodeCoordinates(nodeCoordinates),
					m_nDistanceToNearestExit(nDistance),
					m_LeftNode(NULL),
					m_RightNode(NULL),
					m_UpNode(NULL),
					m_DownNode(NULL)
{

}

MazeNode::~MazeNode()
{
	delete m_LeftNode;
	m_LeftNode = NULL;
	delete m_RightNode;
	m_RightNode = NULL;
	delete m_UpNode;
	m_UpNode = NULL;
	delete m_DownNode;
	m_DownNode = NULL;
}