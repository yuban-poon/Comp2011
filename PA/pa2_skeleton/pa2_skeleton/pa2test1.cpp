/*

	The following program solves the L-shape blocks problem

	 Given
		A 2^N x 2^N array (In this assignment, we restrict the value N as 1, 2 and 3 )
		 The location of the empty cell (x,y)
			The legal (x,y) coordinates of the empty cell:

				For a 2 x 2 block, the legal range is 0-1
				For a 4 x 4 block, the legal range is 0-3
				For a 8 x 8 block, the legal range is 0-7
		 You can assume all the input values are correct

	Output:

		The empty cell (x,y) remains empty
		All other cells are filled by non-overlapping L-shape blocks

	Output mode:
		(0) Console output without normalization
		(1) Console output with normalization

		 Author: Peter, Brian, Tommy
*/

#include <iostream>
using namespace std;

// Constants in global scope
const int MAX_WIDTH = 8;
const int LOCATEQUADRANT_NOT_IMPLEMENTED = 0;

// TODO:
// function locateQuadrant:
// @param x:  x coordinate of the empty cell
// @param y:  y coordinate of the empty cell
//
// If x < half width, y < half width, then return 1
// If x >= half width, y < half width, then return 2
// If x >= half width, y >= half width, then return 3
// If x < half width, y >= half width, then return 4
//
// @return: int
// The function returns after getting valid values for width, emptyXPos and emptyYPos
int locateQuadrant(int width, int x, int y)
{
	if (x < 0.5 * width && y < 0.5 * width)
		return 1;
	if (x >= 0.5 * width && y < 0.5 * width)
		return 2;
	if (x >= 0.5 * width && y >= 0.5 * width)
		return 3;
	if (x < 0.5 * width && y >= 0.5 * width)
		return 4;
	return 0;
}

/**
	Given the puzzleMap (2D array from the recursive function),
	Generate the console output
 */
void visualizePuzzleByText(int width, char puzzleMap[][MAX_WIDTH])
{

	cout << "  ";
	for (int x = 0; x < width; x++)
		cout << x << " ";
	cout << endl;

	for (int y = 0; y < width; y++)
	{
		cout << y << ":";
		for (int x = 0; x < width; x++)
			cout << puzzleMap[x][y] << " ";
		cout << endl;
	}
}

/**
 * Initialize the whole puzzleMap using by a space character: ' '
 */
void initializePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
			puzzleMap[x][y] = ' ';
}

// TODO:
// Normalize the whole puzzleMap. The space character ' ' will not be changed.
//
void normalizePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	char uniqueLetters[22] = {'\0'}; // 21 unique letters + '\0'
	int count = 0;

	// Find all unique elements in the puzzleMap
	// Mapping sequence: uniqueletter = CDHIBGEKJFARSMNQTPLO (skip ' ')
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			char element = puzzleMap[j][i];
			bool found = false;
			if (element == ' ')
			{
				continue;
			}

			for (int k = 0; k < count; ++k)
			{
				if (uniqueLetters[k] == element)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				uniqueLetters[count++] = element;
			}
		}
	}

	// Map the unique elements to the first 21 letters
	// Normalize the puzzleMap
	// Map ABCDEFGHIJKLMNOPQRSTU -> CDHIBGEKJFARSMNQUTPLO
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			char element = puzzleMap[j][i];
			if (element == ' ')
			{
				continue;
			}
			for (int k = 0; k < count; ++k)
			{
				if (uniqueLetters[k] == element)
				{
					puzzleMap[j][i] = 'A' + k;
					break;
				}
			}
		}
	}
	return;
}

// TODO:
// [The most important function in this program]
// The recursive function to fill up the character array: puzzleMap
// You need to figure out the parameters of the fillPuzzleRecursive function by yourself
//
void fillPuzzleRecursive(int width, char puzzleMap[][MAX_WIDTH], int tx,
												 int ty, int x, int y, char &nextChar)
{
	int quad = 0;
	// tx: top Left X coordinate
	// ty: top Left Y coordinate
	// x:  x coordinate of the empty cell
	// y:  y coordinate of the empty cell
	if (width == 2)
	{
		quad = locateQuadrant(width, x % 2, y % 2);
		if (quad != 1)
			puzzleMap[tx][ty] = nextChar; // quad 1
		if (quad != 2)
			puzzleMap[tx + 1][ty] = nextChar; // quad 2
		if (quad != 3)
			puzzleMap[tx + 1][ty + 1] = nextChar; // quad 3
		if (quad != 4)
			puzzleMap[tx][ty + 1] = nextChar; // quad 4
		nextChar++;
		return;
	}

	// The general case
	//
	// Key idea:
	//  Because qual must be equal to either 1, 2, 3 or 4
	// As a result:
	//    A L-shape MUST be created at the center of the bigger rectangle
	//    Each Quad MUST have exactly 1 empty space

	// find the quadrant of the big square
	quad = locateQuadrant(width, x, y);

	// find the quadrant of the small square
	switch (quad)
	{
	case 1:
		quad = locateQuadrant(width, x, y);
		break;
	case 2:
		quad = locateQuadrant(width, x - tx, y);
		break;
	case 3:
		quad = locateQuadrant(width, x - tx, y - ty);
		break;
	case 4:
		quad = locateQuadrant(width, x, y - ty);
		break;
	}

	// fill the empty space
	if (quad != 1)
		puzzleMap[tx + width / 2 - 1][ty + width / 2 - 1] = nextChar; // quad 1
	if (quad != 2)
		puzzleMap[tx + width / 2][ty + width / 2 - 1] = nextChar; // quad 2
	if (quad != 3)
		puzzleMap[tx + width / 2][ty + width / 2] = nextChar; // quad 3
	if (quad != 4)
		puzzleMap[tx + width / 2 - 1][ty + width / 2] = nextChar; // quad 4
	nextChar++;

	// fill the squares by recursion
	fillPuzzleRecursive(width / 2, puzzleMap, tx, ty, (quad == 1 ? x : width / 2 - 1), (quad == 1 ? y : width / 2 - 1), nextChar);								 // quad 1
	fillPuzzleRecursive(width / 2, puzzleMap, tx + width / 2, ty, (quad == 2 ? x : width / 2), (quad == 2 ? y : width / 2 - 1), nextChar);				 // quad 2
	fillPuzzleRecursive(width / 2, puzzleMap, tx + width / 2, ty + width / 2, (quad == 3 ? x : width / 2), (quad == 3 ? y : width / 2), nextChar); // quad 3
	fillPuzzleRecursive(width / 2, puzzleMap, tx, ty + width / 2, (quad == 4 ? x : width / 2 - 1), (quad == 4 ? y : width / 2), nextChar);				 // quad 4
	return;
}

// TODO:
// function checkInput:
//
// @param width: the width of the square. Valid values: 2, 4, 8
// You can assume inputs are always integers.
// @param emptyXPos: the x-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
// @param emptyYPos: the y-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
//
//  Note: The pass-by-reference variables will be used in the main function.
// @return: void
// The function returns after getting valid values for width, emptyXPos and emptyYPos
void checkInput(int &width, int &emptyXPos, int &emptyYPos)
{
	while (true)
	{
		// Some helper lines for you to use:
		cout << "Enter the width/height of the puzzle (2, 4, 8): ";
		cin >> width;
		cout << endl;
		if (width != 2 && width != 4 && width != 8)
		{
			continue;
		}
		break;
	}

	while (true)
	{
		cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyXPos;
		cout << endl;
		if (emptyXPos < 0 || emptyXPos > width - 1)
		{
			continue;
		}
		break;
	}

	while (true)
	{
		cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyYPos;
		cout << endl;
		if (emptyYPos < 0 || emptyYPos > width - 1)
		{
			continue;
		}
		break;
	}
	return;
}

// You are NOT ALLOWED to modify the main function
int main()
{

	int width = 8;
	int emptyXPos = 0;
	int emptyYPos = 0;

	// checkInput(width, emptyXPos, emptyYPos);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			emptyXPos = i;
			emptyYPos = j;

			// initialized with empty spaces..
			char puzzleMap[MAX_WIDTH][MAX_WIDTH];

			// initialize
			initializePuzzleMap(width, puzzleMap);

			int modeOfOperation = 3;
			do
			{
				cout
						<< "0: Exit directly (for testing checkInput function), 1: Output Quadrant of the empty cell,"
						<< endl
						<< "2: Output without normalization (for student's debug only), 3: Output with normalization"
						<< endl;
				cout << "Enter the output mode: ";
				// cin >> modeOfOperation;
				cout << endl;
			} while (modeOfOperation < 0 || modeOfOperation > 3);

			if (modeOfOperation == 0)
			{
				return 0;
			}
			if (modeOfOperation == 1)
			{
				int quad = locateQuadrant(width, emptyXPos, emptyYPos);
				cout << "Quadrant for the empty cell: " << quad << endl;
				return 0;
			}
			char nextChar = 'A';

			// invoke the recursive call here...
			// Result: puzzleMap will be filled by characters
			fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);

			int quad = locateQuadrant(width, emptyXPos, emptyYPos);
			cout << "Quadrant for the empty cell: " << quad << endl;
			if (modeOfOperation == 2)
			{
				visualizePuzzleByText(width, puzzleMap);
			}
			else
			{
				normalizePuzzleMap(width, puzzleMap);
				visualizePuzzleByText(width, puzzleMap);
			}
		}
	}
	return 0;
}
