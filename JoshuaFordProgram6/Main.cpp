/*********************************************

Name: Joshua Ford
Course: CS 201R
Program: Program 6 Teddy Bear Counter
Due Date: 24 April 2016
Description: Get number of bears and try to get to 17 within
	counting restrictions
Inputs:	keyboard(console)
Outputs: console
Algorithm:
1. Get number of bears
2. SolveTeddy()
	a. If turns > 20, go back one turn
	b. If bears == 17, record all moves and output success
	c. If bears is even, divide by two and recheck
	d. If bears is a multiple of three, add one third and recheck
	e. Else add 23 and recheck
3. Ask to go again

*********************************************/

#include <iostream>
#include <string>
using namespace std;

bool SolveTeddy(int bears, int turns, string moves[], int& idx);

void main()
{
	char exit = ' ';
	char inBears[5]; // for input checking
	int bears; // the glorious beasts to be counted
	string buffer; // for bad input checking
	string moveList[20]; // for tracking moves of solutions
	int idx;

	while (tolower(exit) != 'n')
	{
		idx = 0; // reset idx before each count

		// get number of bears
		do
		{
			cout << "Number of bears [0 < N <= 10000]: ";
			cin.get(inBears, 5);
			getline(cin, buffer);
			bears = atoi(inBears);
		} while (buffer != "" || bears < 1 || bears > 10000);

		cout << "Traversing the Teddy Bear Abyss..." << endl;

		// report results
		if (!SolveTeddy(bears, 0, moveList, idx))
			cout << "No solution found within 20 turns" << endl;
		else
		{
			// output move set to show user just how awesome 
			// you really are at counting stuffed animals
			for (int i = 0; i < idx; i++)
			{
				cout << moveList[i] << endl;
			}
		}

		// ask for redo
		do 
		{
			cout << "Count more bears? [y/n]";
			cin >> exit;
			getline(cin, buffer);
		} while (tolower(exit) != 'n' && tolower(exit) != 'y');

		// for readability 
		cout << "\n";
	}
	cout << buffer;
}

bool SolveTeddy(int bears, int turns, string moves[], int& idx)
{
	if (turns == 21)
	{
		// no good here, turn back now 
		return false;
	}

	if (bears == 17)
	{
		// we've hit the jackpot, return true all the way up the call stack
		cout << "Solution found in " << turns << " turns" << endl;
		return true;
	}

	// first try to divide by two
	if (bears % 2 == 0 && SolveTeddy(bears / 2, turns + 1, moves, idx))
	{
		moves[turns] = "Turn " + to_string(turns + 1) + ": Reduce " 
			+ to_string(bears) + " by half to get " + to_string(bears / 2);
		idx += 1;
		return true;
	}

	// if bears is divisible by three, and within parameters, choose this path
	if (bears % 3 == 0 && (bears + (bears / 3)) <= 10000 
		&& (bears + (bears / 3)) > 0 && SolveTeddy(bears + (bears / 3), turns + 1, moves, idx))
	{
		moves[turns] = "Turn " + to_string(turns + 1) + ": Add one third to " 
			+ to_string(bears) + " to get " + to_string(bears + (bears / 3));
		idx += 1;
		return true;
	}

	// if can't divide by 2 or 3, add 23
	if (bears + 23 > 0 && bears + 23 <= 10000 
		&& SolveTeddy(bears + 23, turns + 1, moves, idx))
	{
		moves[turns] = "Turn " + to_string(turns + 1) + ": Add 23 to " 
			+ to_string(bears) + " to get " + to_string(bears + 23);
		idx += 1;
		return true;
	}

	// no possible paths here, go back to previous turn
	return false;
}