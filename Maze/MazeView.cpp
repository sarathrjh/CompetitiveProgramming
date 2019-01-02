#include "MazeView.h"
#include <fstream>

const int WALL_COLOR = 72;
const int PATH_COLOR = 2;
const int EXIT_CODE = 27; //Escape key
const char WALL = '#';
const char FREE = ' ';
const char PATH = '*';

/**
 * @brief Constructor
 *
 * @param[in] : Nil
 *  
 */
MazeView::MazeView() :
			m_outHandle(NULL),
			m_inHandle(NULL),
			m_events(0),
			m_ExitKey(0),
			m_mouseXPoint(0),
			m_mouseYPoint(0),
			m_buttonState(0),
			m_nRowCount(0),
			m_nColCount(0),
			m_MazeArray(NULL)
{
	m_ExitCoordinates.clear();
	m_mazeNodeMap.clear();
}

/**
 * @brief Destructor
 *
 * @param[in] : Nil
 *
 */
MazeView::~MazeView()
{
	for (int nRowIndex = 0; nRowIndex < m_nRowCount; nRowIndex++)
	{
		delete [] m_MazeArray[nRowIndex];
	}
	delete [] m_MazeArray;
	m_ExitCoordinates.clear();
	for (auto& mazeNode : m_mazeNodeMap)
	{
		delete mazeNode.second;
	}
	m_mazeNodeMap.clear();
}

/**
 * @brief : displayMaze()
 *
 * This function displays the maze matrix in console, print both Wall('#') and path(' ').
 * Also fill the exit coordinates into a vector from the matrix.
 * @Note: Exit coordinates filling is added in this method as part of optimization
 * to avoid multiple matrix iterations. This display method is being called once
 * during the launch of application.
 *
 * @param - Nil
 *
 * @return - Nil
 */
void MazeView::displayMaze()
{
	clearView();

	for (int nRowIndex = 0; nRowIndex < m_nRowCount; nRowIndex++)
	{
		for (int nColIndex = 0; nColIndex < m_nColCount; nColIndex++)
		{
			//Fill the exit coordinates.
			if (((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nRowIndex == 0)) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nColIndex == 0)) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nRowIndex == (m_nRowCount - 1))) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nColIndex == (m_nColCount - 1))))
			{
				m_ExitCoordinates.push_back(Coordinates(nRowIndex, nColIndex));
			}

			//print walls
			SetConsoleTextAttribute(m_outHandle, WALL_COLOR);
			printf("%c", m_MazeArray[nRowIndex][nColIndex]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 * @brief : displayPath()
 *
 * This function displays or highlight the shortest path in maze.
 *
 * @param pathToHighlight - This vector contains the coordinates of shortest path to exit of maze.
 *
 * @param bClearPath - true, then clear the last highlighted path with ' '.
 *                     false, then display or highlight the path with '*'.
 * @return - Nil
 */
void MazeView::displayPath(const std::vector<Coordinates>& pathToHighlight, bool bClearPath)
{
	COORD coordinate;
	if (bClearPath)
	{
		//Clear the previous path drawn.
		for (auto& mazeCoordinate : pathToHighlight)
		{
			coordinate.Y = mazeCoordinate.m_nXPoint;
			coordinate.X = mazeCoordinate.m_nYPoint;
			SetConsoleTextAttribute(m_outHandle, WALL_COLOR);
			SetConsoleCursorPosition(m_outHandle, coordinate);
			printf("%c", FREE);
		}
	}
	else
	{
		//Draw the path to nearest exit
		for (auto& mazeCoordinate : pathToHighlight)
		{
			coordinate.Y = mazeCoordinate.m_nXPoint;
			coordinate.X = mazeCoordinate.m_nYPoint;
			SetConsoleTextAttribute(m_outHandle, PATH_COLOR);
			SetConsoleCursorPosition(m_outHandle, coordinate);
			printf("%c", PATH);
		}

	}
	//Set the console cursor to last position.
	coordinate.X = 0;
	coordinate.Y = m_nRowCount + 1;
	SetConsoleCursorPosition(m_outHandle, coordinate);
}

/**
 * @brief : readAndParseMazeFile()
 *
 * This function read the input maze file,create and update the maze matrix with WALL and PATH values.
 *
 * @param strMazeFilePath - input maze file path.
 *
 * @return bool- true on successful read.
 *				 false on any failure.
 */
bool MazeView::readAndParseMazeFile(const string& strMazeFilePath)
{
	size_t nLineEnd = 0;
	std::ifstream fileBuffer(strMazeFilePath.c_str());//read
	std::string strFileContents((std::istreambuf_iterator<char>(fileBuffer)), std::istreambuf_iterator<char>());//copy to string
	size_t nCommaPos = strFileContents.find(',');//find ,
	if (nCommaPos == std::string::npos)
	{
		return false;
	}
	m_nColCount = atoi(strFileContents.substr(0, nCommaPos).c_str());//value to the left of , is col count
	size_t nNewLine = strFileContents.find('\n');
	m_nRowCount = atoi(strFileContents.substr(nCommaPos + 1, nNewLine).c_str());//the value between , and \n is row count

	if ((m_nRowCount <= 1) || (m_nColCount <= 1))
	{
		return false;
	}

	m_MazeArray = new char*[m_nRowCount + 1];//row
	for (int nRowIndex = 0; nRowIndex < m_nRowCount; ++nRowIndex)
	{
		m_MazeArray[nRowIndex] = new char[m_nColCount + 1];//column
		memset(m_MazeArray[nRowIndex], 0, m_nColCount + 1);
		nLineEnd = strFileContents.find('\n', nNewLine + 1);

		if (nLineEnd != std::string::npos)
		{
			strcpy(m_MazeArray[nRowIndex], strFileContents.substr(nNewLine + 1, (nLineEnd - nNewLine)).c_str());
			nNewLine = nLineEnd;
		}
		else
		{
			//this is needed in case if the last line does not have a new line to terminate
			strncpy(m_MazeArray[nRowIndex], strFileContents.substr(nNewLine + 1).c_str(), m_nColCount);
		}
	}
	return true;
}

/**
 * @brief : initializeView()
 *
 * This function initialize input and output console handles.
 *
 * @param - Nil
 *
 * @return bool - true on successful initialization.
 *                false on failure.
 */
bool MazeView::initializeView()
{
	bool bReturn = true;
	//This do while loop is to just break on any failure.
	//otherwise need to write return in all if conditions.
	//This function has return in one place.
	do
	{
		m_outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (INVALID_HANDLE_VALUE == m_outHandle)
		{
			bReturn = false;
			break;
		}

		m_inHandle = GetStdHandle(STD_INPUT_HANDLE);
		if (INVALID_HANDLE_VALUE == m_inHandle)
		{
			bReturn = false;
			break;
		}

		if (!SetConsoleMode(m_inHandle, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS))
		{
			bReturn = false;
			break;
		}
	} while (false);

	return bReturn;
}

/**
 * @brief : getSourceCoordinate()
 *
 * This function read the source coordinate or point that the user clicked on the maze.
 * When user click on any wall node('#'), this function will find the Path node(' ') among
 * its four nieghbours(left, right, up, down) with shortest path to nearest exit.
 * If there is no nieghbour node to that clicked Wall node, then take that wall node 
 * as source coordinates and won't display any path, since there is not path.
 *
 * @param sourceCordinates - Output parameter to hold coordinates of the maze that is clicked by user.
 *
 * @return bool - true on any mouse click event, otherwise return false.
 */
bool MazeView::getSourceCoordinate(Coordinates& sourceCordinates)
{
	bool bReturn = false;
	if (getMouseCoordinates(sourceCordinates))
	{
		//Check whether the clicked point is inside maze matrix.
		//if not, then return false;
		if ((sourceCordinates.m_nXPoint < 0) || (sourceCordinates.m_nYPoint < 0) ||
			(sourceCordinates.m_nXPoint >= m_nRowCount) || (sourceCordinates.m_nYPoint >= m_nColCount))
		{
			return bReturn;
		}
		//If the mouse click is on wall ie.'#', then find the nieghbour path node(' ') among 
		//four(left, right, up, down) nodes of that point,which has shortest distance to nearest exit.
		if (m_MazeArray[sourceCordinates.m_nXPoint][sourceCordinates.m_nYPoint] == WALL)
		{
			string LeftKey(std::to_string(sourceCordinates.m_nXPoint) + "," + std::to_string(sourceCordinates.m_nYPoint - 1));
			string RightKey(std::to_string(sourceCordinates.m_nXPoint) + "," + std::to_string(sourceCordinates.m_nYPoint + 1));
			string UpKey(std::to_string(sourceCordinates.m_nXPoint - 1) + "," + std::to_string(sourceCordinates.m_nYPoint));
			string DownKey(std::to_string(sourceCordinates.m_nXPoint + 1) + "," + std::to_string(sourceCordinates.m_nYPoint));

			int nShortestDistanceAmongNieghbours = -1;
			MazeNode* pMazeNodeWithShortDistance = NULL;
			//Find left node and check its distance is shortest or not.
			MazeNode* pMazeNode = findMazeNode(LeftKey);
			if (pMazeNode)
			{
				compareAndGetShortDistance(pMazeNode, nShortestDistanceAmongNieghbours);
				if (pMazeNode->m_nDistanceToNearestExit == nShortestDistanceAmongNieghbours)
				{
					pMazeNodeWithShortDistance = pMazeNode;
				}
			}

			//Find Right node and check its distance is shortest or not.
			pMazeNode = findMazeNode(RightKey);
			if (pMazeNode)
			{
				compareAndGetShortDistance(pMazeNode, nShortestDistanceAmongNieghbours);
				if (pMazeNode->m_nDistanceToNearestExit == nShortestDistanceAmongNieghbours)
				{
					pMazeNodeWithShortDistance = pMazeNode;
				}
			}

			//Find Up node and check its distance is shortest or not.
			pMazeNode = findMazeNode(UpKey);
			if (pMazeNode)
			{
				compareAndGetShortDistance(pMazeNode, nShortestDistanceAmongNieghbours);
				if (pMazeNode->m_nDistanceToNearestExit == nShortestDistanceAmongNieghbours)
				{
					pMazeNodeWithShortDistance = pMazeNode;
				}
			}

			//Find Right node and check its distance is shortest or not.
			pMazeNode = findMazeNode(DownKey);
			if (pMazeNode)
			{
				compareAndGetShortDistance(pMazeNode, nShortestDistanceAmongNieghbours);
				if (pMazeNode->m_nDistanceToNearestExit == nShortestDistanceAmongNieghbours)
				{
					pMazeNodeWithShortDistance = pMazeNode;
				}
			}

			//If there is atleat one path node(' ') among its nieghbours or find the path node 
			//with shortest distance and return its coordinates as source.
			if (nShortestDistanceAmongNieghbours >= 0)
			{
				sourceCordinates.m_nXPoint = pMazeNodeWithShortDistance->m_NodeCoordinates.m_nXPoint;
				sourceCordinates.m_nYPoint = pMazeNodeWithShortDistance->m_NodeCoordinates.m_nYPoint;
			}
		}
		bReturn = true;
	}
	return bReturn;
}

/**
 * @brief : isExit()
 *
 * This function decides the exit of the application.
 * Function checks whether user press escape key or not.
 *
 * @param - Nil
 *
 * @return bool - true if escape key is pressed, otherwise return false.
 */
bool MazeView::isExit()
{
	if (m_ExitKey == EXIT_CODE)
	{
		return true;
	}
	return false;
}

/**
 * @brief : getExitCoordinates()
 *
 * This function returns the copy of Exit Coordinates vector.
 *
 * @param - Nil
 *
 * @return vector<Coordinates> - Copy of Exit Coordinates vector.
 */
vector<Coordinates> MazeView::getExitCoordinates()
{
	return m_ExitCoordinates;
}

/**
 * @brief : buildGraph()
 *
 * This function takes a coordinate point and its distance to create a node
 * in graph and iterates all its neighbours(left, right, up, right) and reccursively
 * call this function with its distance + 1. Each node will be processed until it
 * reaches a Wall or an Exit.
 * This reccursive function will return,
 *		when the 'nodeCoordinates' are below '0' or above maze size.
 *		when the coordinate value in maze is a Wall('#')
 *
 * @Note : In our application, this function is called with all the exit coordinates 
 * as start point and reccursively iterates all the nodes that has path from that exit.
 * On every iteration, it will update the distance in that node, if it is less than the
 * current distcane to exit. Newly created node is added to map to avoid reduntant node
 * creation while iterating neighbours(ie. may be that node has been already visited, then 
 * check it has shortest distance to nearest exit or not).
 * A path node(' ') in maze matrix that is surrounded by Wall node('#') as four nieghbours,
 * then there is no path from that path node to exit, so this function never creates that node
 * in graph. This function will create nodes and connects it in graph that has path to exit.
 *
 * @param nodeCoordinates - Coordinates of the maze.
 *
 * @param nDistance - Distance of that node to exit.
 *
 * @return MazeNode* - Returns the created Node.
 */
MazeNode* MazeView::buildGraph(Coordinates nodeCoordinates, int nDistance)
{
	//if any point below '0' or above 'maze size' or that point is wall, then ignore it.
	if ((nodeCoordinates.m_nXPoint < 0) || (nodeCoordinates.m_nXPoint > (m_nRowCount - 1)) ||
		(nodeCoordinates.m_nYPoint < 0) || (nodeCoordinates.m_nYPoint > (m_nColCount - 1)) ||
		(m_MazeArray[nodeCoordinates.m_nXPoint][nodeCoordinates.m_nYPoint] == '#'))
	{
		return NULL;
	}

	string MapKey(std::to_string(nodeCoordinates.m_nXPoint) + "," + std::to_string(nodeCoordinates.m_nYPoint));
	auto mapIterator = m_mazeNodeMap.find(MapKey);
	MazeNode* NewMazeNode = NULL;
	if (mapIterator != m_mazeNodeMap.end())
	{
		//Node with this coordinate is already created, so check whether it has shortest distance.
		NewMazeNode = m_mazeNodeMap[MapKey];
		//if the distance of the current node is less than 'nDistance', then return.
		//bcoz all the nodes under that node already have shortest distance.
		if (NewMazeNode->m_nDistanceToNearestExit > nDistance)
		{
			NewMazeNode->m_nDistanceToNearestExit = nDistance;
		}
		else
		{
			return m_mazeNodeMap[MapKey];
		}
	}

	if (NewMazeNode == NULL)
	{
		NewMazeNode = new MazeNode(nodeCoordinates, nDistance);
		m_mazeNodeMap[MapKey] = NewMazeNode;
	}

	//Build graph for all the four nieghbour nodes.
	NewMazeNode->m_LeftNode = buildGraph(Coordinates(nodeCoordinates.m_nXPoint, (nodeCoordinates.m_nYPoint - 1)), nDistance + 1);
	NewMazeNode->m_RightNode = buildGraph(Coordinates(nodeCoordinates.m_nXPoint, (nodeCoordinates.m_nYPoint + 1)), nDistance + 1);
	NewMazeNode->m_UpNode = buildGraph(Coordinates((nodeCoordinates.m_nXPoint - 1), nodeCoordinates.m_nYPoint), nDistance + 1);
	NewMazeNode->m_DownNode = buildGraph(Coordinates((nodeCoordinates.m_nXPoint + 1), nodeCoordinates.m_nYPoint), nDistance + 1);

	return NewMazeNode;
}

/**
 * @brief : findSmallestDistanceAmongNieghbours()
 *
 * This function finds the shortest distance among the four
 * neighbours(left, right, up, down) of the inputted node.
 *
 * @param pMazeNode- Input node
 *
 * @return int - (-1) if all the nieghbour nodes are walls.
				 otherwise returns the smallest distance among them.	
 */
int MazeView::findSmallestDistanceAmongNieghbours(MazeNode* pMazeNode)
{
	int nSmallDistance = -1;
	if (pMazeNode)
	{
		nSmallDistance = pMazeNode->m_nDistanceToNearestExit;
		if (pMazeNode->m_LeftNode && pMazeNode->m_LeftNode->m_nDistanceToNearestExit < nSmallDistance)
			nSmallDistance = pMazeNode->m_LeftNode->m_nDistanceToNearestExit;

		if (pMazeNode->m_RightNode && pMazeNode->m_RightNode->m_nDistanceToNearestExit < nSmallDistance)
			nSmallDistance = pMazeNode->m_RightNode->m_nDistanceToNearestExit;

		if (pMazeNode->m_UpNode && pMazeNode->m_UpNode->m_nDistanceToNearestExit < nSmallDistance)
			nSmallDistance = pMazeNode->m_UpNode->m_nDistanceToNearestExit;

		if (pMazeNode->m_DownNode && pMazeNode->m_DownNode->m_nDistanceToNearestExit < nSmallDistance)
			nSmallDistance = pMazeNode->m_DownNode->m_nDistanceToNearestExit;
	}
	return nSmallDistance;
}

/**
 * @brief : findNearestExit()
 *
 * This function takes a coordinate point and find its shortest distance to nearest 
 * exit with all the path nodes. This function is reccursively called until it reaches 
 * exit coordinate.
 * This reccursive function will return,
 *		when the 'srcCordinate' is an exit.
 *
 * @param srcCordinate - Source coordinates of the maze clicked by the user.
 *
 * @param pathToExit - Vector that holds all the coordinates of the shortst path to nearest exit from 'srcCordinate'.
 *
 * @return  - Nil.
 */
void MazeView::findNearestExit(Coordinates srcCordinate, std::vector<Coordinates>& pathToExit)
{
	string MapKey(std::to_string(srcCordinate.m_nXPoint) + "," + std::to_string(srcCordinate.m_nYPoint));
	auto mapIterator = m_mazeNodeMap.find(MapKey);
	MazeNode* NewMazeNode = NULL;
	if (mapIterator != m_mazeNodeMap.end())
	{
		NewMazeNode = m_mazeNodeMap[MapKey];
		if (NewMazeNode)
		{
			//If the srcCordinate is the exit point, then push to path vector and return. 
			if (std::find(m_ExitCoordinates.begin(), m_ExitCoordinates.end(), srcCordinate) != m_ExitCoordinates.end())
			{
				pathToExit.push_back(srcCordinate);
			}
			else
			{
				int nDistanceToExit = findSmallestDistanceAmongNieghbours(NewMazeNode);
				if (nDistanceToExit != -1)
				{
					if (NewMazeNode->m_LeftNode && NewMazeNode->m_LeftNode->m_nDistanceToNearestExit == nDistanceToExit)
					{
						pathToExit.push_back(srcCordinate);
						if (!(std::find(m_ExitCoordinates.begin(), m_ExitCoordinates.end(), srcCordinate) != m_ExitCoordinates.end()))
						{
							findNearestExit(NewMazeNode->m_LeftNode->m_NodeCoordinates, pathToExit);
						}
					}
					else if (NewMazeNode->m_RightNode && NewMazeNode->m_RightNode->m_nDistanceToNearestExit == nDistanceToExit)
					{
						pathToExit.push_back(srcCordinate);
						if (!(std::find(m_ExitCoordinates.begin(), m_ExitCoordinates.end(), srcCordinate) != m_ExitCoordinates.end()))
						{
							findNearestExit(NewMazeNode->m_RightNode->m_NodeCoordinates, pathToExit);
						}
					}
					else if (NewMazeNode->m_UpNode && NewMazeNode->m_UpNode->m_nDistanceToNearestExit == nDistanceToExit)
					{
						pathToExit.push_back(srcCordinate);
						if (!(std::find(m_ExitCoordinates.begin(), m_ExitCoordinates.end(), srcCordinate) != m_ExitCoordinates.end()))
						{
							findNearestExit(NewMazeNode->m_UpNode->m_NodeCoordinates, pathToExit);
						}
					}
					else if (NewMazeNode->m_DownNode && NewMazeNode->m_DownNode->m_nDistanceToNearestExit == nDistanceToExit)
					{
						pathToExit.push_back(srcCordinate);
						if (!(std::find(m_ExitCoordinates.begin(), m_ExitCoordinates.end(), srcCordinate) != m_ExitCoordinates.end()))
						{
							findNearestExit(NewMazeNode->m_DownNode->m_NodeCoordinates, pathToExit);
						}
					}
				}
			}
		}
	}
}

/**
 * @brief : clearView()
 *
 * This private function clear the console view.
 *
 * @param - Nil
 *
 * @return - Nil.
 */
void MazeView::clearView()
{
	COORD screenCoordinate = { 0, 0 };
	DWORD dwCharsWritten = 0;
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBuffer;
	DWORD dwConSize = 0;

	GetConsoleScreenBufferInfo(m_outHandle, &consoleScreenBuffer);
	dwConSize = consoleScreenBuffer.dwSize.X * consoleScreenBuffer.dwSize.Y;
	FillConsoleOutputCharacter(m_outHandle, TEXT(' '), dwConSize, screenCoordinate, &dwCharsWritten);
	GetConsoleScreenBufferInfo(m_outHandle, &consoleScreenBuffer);
	FillConsoleOutputAttribute(m_outHandle, consoleScreenBuffer.wAttributes, dwConSize, screenCoordinate, &dwCharsWritten);
	SetConsoleCursorPosition(m_outHandle, screenCoordinate);
}

/**
 * @brief : getMouseCoordinates()
 *
 * This private function returns Coordinates in maze UI clicked by user.
 *
 * @param sourceCordinates - Output parameter to hold coordinates.
 *
 * @return bool - true if it is mouse left button click.
 *				  otherwise return false.
 */
bool MazeView::getMouseCoordinates(Coordinates& sourceCordinates)
{
	bool bReturn = false;
	if (0 == ReadConsoleInput(m_inHandle, m_inputRecords, MAX_RECORDS, &m_events))
	{
		m_events = 0;
	}
	for (int nIndex = 0; nIndex < m_events; nIndex++)
	{
		m_ExitKey = m_inputRecords[nIndex].Event.KeyEvent.wVirtualKeyCode;
		m_buttonState = m_inputRecords[nIndex].Event.MouseEvent.dwButtonState;
		if (m_inputRecords[nIndex].EventType == MOUSE_EVENT)
		{
			if (m_buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				m_mouseXPoint = m_inputRecords[nIndex].Event.MouseEvent.dwMousePosition.X;
				m_mouseYPoint = m_inputRecords[nIndex].Event.MouseEvent.dwMousePosition.Y;
				sourceCordinates.m_nXPoint = m_mouseYPoint;
				sourceCordinates.m_nYPoint = m_mouseXPoint;
				bReturn = true;
				m_buttonState = 0;
				break;
			}
		}
	}

	return bReturn;
}

/**
 * @brief : fillExitCoordinates()
 *
 * This private function fill exit Coordinates in 'm_ExitCoordinates' vector.
 *
 * @param - Nil.
 *
 * @return - Nil.
 */
void MazeView::fillExitCoordinates()
{
	for (int nRowIndex = 0; nRowIndex < m_nRowCount; nRowIndex++)
	{
		for (int nColIndex = 0; nColIndex < m_nColCount; nColIndex++)
		{
			if (((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nRowIndex == 0)) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nColIndex == 0)) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nRowIndex == (m_nRowCount - 1))) ||
				((m_MazeArray[nRowIndex][nColIndex] == ' ') && (nColIndex == (m_nColCount - 1))))
			{
				m_ExitCoordinates.push_back(Coordinates(nRowIndex, nColIndex));
			}
		}
	}
}

/**
 * @brief : findMazeNode()
 *
 * This private function returns the maze node, if it is present in 'm_mazeNodeMap' map.
 *
 * @param CoordinateKey - Coordinate point.
 *
 * @return MazeNode* - Node if present, otherwise return NULL.
 */
MazeNode* MazeView::findMazeNode(string CoordinateKey)
{
	MazeNode* pMazeNode = NULL;
	auto mapIterator = m_mazeNodeMap.find(CoordinateKey);
	if (mapIterator != m_mazeNodeMap.end())
	{
		pMazeNode = m_mazeNodeMap[CoordinateKey];
	}
	return pMazeNode;
}

/**
 * @brief : compareAndGetShortDistance()
 *
 * This private function compares the distance passed to this function with the
 * distance present in pMazeNode and returns the shortest distance.
 *
 * @param pMazeNode - Maze node that represents a coordinate.
 *
 * @param nShortDistance - I/O parameter that holds the shortest distance.
 *
 * @return - Nil.
 */
void MazeView::compareAndGetShortDistance(MazeNode* pMazeNode, int& nShortDistance)
{
	if (pMazeNode)
	{
		//If node is available, then check its distance to exit is smaller than the cuurent one.
		//Since 'nShortDistance' is initialized with '-1', check whether distance 
		//from atleast one neighbour node is read, if not then assign its distance to 'nShortDistance'.
		if (nShortDistance >= 0)
		{
			if (pMazeNode->m_nDistanceToNearestExit < nShortDistance)
			{
				nShortDistance = pMazeNode->m_nDistanceToNearestExit;
			}
		}
		else
		{
			nShortDistance = pMazeNode->m_nDistanceToNearestExit;
		}
	}
}