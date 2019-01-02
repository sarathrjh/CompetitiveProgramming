#include "stdafx.h"
#include <windows.h>
#include <string>
#include <vector>
#include <map>

#include "MazeNode.h"

using namespace std;

const int MAX_RECORDS = 128;

/**
 * This class represents maze view and graph builder.
 * 
 */
class MazeView
{
public:
	MazeView();
	~MazeView();
	void displayMaze();
	void displayPath(const std::vector<Coordinates>& pathToHighlight, bool bClearPath = false);
	bool readAndParseMazeFile(const string& strMazeFilePath);
	bool initializeView();
	bool getSourceCoordinate(Coordinates& sourceCordinates);
	bool isExit();
	vector<Coordinates> getExitCoordinates();
	MazeNode* buildGraph(Coordinates nodeCoordinates, int nDistance);
	int findSmallestDistanceAmongNieghbours(MazeNode* pMazeNode);
	void findNearestExit(Coordinates srcCordinate, std::vector<Coordinates>& pathToExit);

private:

	void clearView();
	bool getMouseCoordinates(Coordinates& sourceCordinates);
	void fillExitCoordinates();
	MazeNode* findMazeNode(string CoordinateKey);
	void compareAndGetShortDistance(MazeNode* pMazeNode, int& nShortDistance);

	//Member variables
	HANDLE m_outHandle; // Handle to the "screen"
	HANDLE m_inHandle; // Handle to the "keyboard"/"mouse"
	INPUT_RECORD m_inputRecords[MAX_RECORDS];
	vector<Coordinates> m_ExitCoordinates;
	map<string, MazeNode*> m_mazeNodeMap;
	DWORD m_events;
	WORD m_ExitKey;
	char **m_MazeArray;
	int m_mouseXPoint;
	int m_mouseYPoint;
	int m_buttonState;
	int m_nRowCount;
	int m_nColCount;
};