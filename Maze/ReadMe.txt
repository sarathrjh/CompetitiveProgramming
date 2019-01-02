Problem: Given an N x M complete 2D maze, implement the following:


• Render the maze on screen, drawing all the walls

• Allow the user to click anywhere within the graph

• Display the shortest path from the user-chosen point to the nearest exit

• An exit is a gap in the walls around the perimeter

File format:

All elements in the file are positive integers, commas, spaces and newlines. The maze is considered to be an N x M matrix, with (0,0) as the upper left and (N-1, M-1) as the lower right. The first line of the file is:

N, M\n

Where N = number of columns and M = number of rows, followed by a newline character. Following the maze dimensions are the wall coordinates. Each wall has the following format:

X1, Y1, X2, Y2\n 

where 0 <= X1, X2 < N and 0 <= Y1, Y2 < M. Each wall line is terminated with a newline character.


Walls have the following properties:


• Each wall is  either vertical or horizontal, so one (and only one) of the two following conditions is true: X1 == X2 or Y1 == Y2.

• The maze is guaranteed to be complete, such that for each (i, j) where 0 <= i < N and 0 <= j < M, (I,j) is a member of at least one wall and a member of at most four walls.

• No walls intersect, but walls may share endpoints.




========================================================================
    CONSOLE APPLICATION : Maze Project Overview
========================================================================

AppWizard has created this Maze application for you.

This file contains a summary of what you will find in each of the files that
make up your Maze application.


Maze.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Maze.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Maze.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
