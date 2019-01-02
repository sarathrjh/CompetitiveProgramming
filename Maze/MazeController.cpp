#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "MazeView.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc <= 1)
	{
		printf("Please enter the input file path as command line argument. \n");
		printf("Input Format ******<Maze.exe> <Full path of Maze.txt>******* \n");
		printf("Press Enter to exit \n");
		cin.get();
		return 0;
	}
	else if(argc != 2)
	{
		printf("Unexpected input in command line \n");
		printf("Input Format ******<Maze.exe> <Full path of Maze.txt>******* \n");
		printf("Press Enter to exit \n");
		cin.get();
		return 0;
	}		

	MazeView mazeCanvas;
	if (!mazeCanvas.initializeView())
	{
		printf("View initialization failed....Press enter to exit \n");
		cin.get();
		return 0;
	}

	if (!mazeCanvas.readAndParseMazeFile(argv[1]))
	{
		printf("Maze input file read failed....Press enter to exit \n");
		cin.get();
		return 0;
	}

	std::vector<Coordinates> pathToNearestExit;
	mazeCanvas.displayMaze();

	//Iterate all the exit points and build graph with all the nodes that has path to atleast one exit.
	//After this loop, graph is created with nodes having shortest distance to exit.
	for (auto coordinate : mazeCanvas.getExitCoordinates())
	{
		mazeCanvas.buildGraph(coordinate, 0);
	}

	//Every 50ms check for mouse click event or exit event.
	while (true)
	{
		if (mazeCanvas.isExit())
		{
			break;
		}
		Coordinates mouseClickPoints;
		if (mazeCanvas.getSourceCoordinate(mouseClickPoints))
		{
			mazeCanvas.displayPath(pathToNearestExit, true);
			pathToNearestExit.clear();
			mazeCanvas.findNearestExit(mouseClickPoints, pathToNearestExit);
			mazeCanvas.displayPath(pathToNearestExit);
		}
		//Put a sleep of 50ms to reduce CPU cycles, since in a loop.
		Sleep(50);
	}
	exit(0);
    return 0;
}

