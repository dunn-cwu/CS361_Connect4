// ---------------------------------
// Course: CS 361 Principles of Programming Languages 1
// Section: 10:00 AM
// Instructor: Arne Leitert
// Quarter: Fall 2018
// Date: 11/08/2018
//
// Assignment: Lab 7
// Student: Andrew Dunn
// ---------------------------------

#include <iostream>
#include "game.h"
#include "players.h"

using namespace std;

// Asks player for their next move in the form of a column number
int HumanPlayer::getNextTurn()
{
	int col = -1;

	while (col < 0)
	{
		cout << "Enter column: ";
		cin >> col;
	}

	return col;
}

// Sets up the C++11 random number generator for the current AI player
// The benefit of using the newer random library is that you can have
// multiple random number generators with different seeds. In this case,
// each AiPlayer has a different seed.
AiPlayer::AiPlayer() : randDevice()
{
	// Initialize random number generator with a random seed from randDevice
	randGen = std::mt19937(randDevice());

	// Define a value distribution range for the random numner generator from 1 to Game::BoardWidth
	randDist = uniform_int_distribution<>(1, Game::BoardWidth);
}

int AiPlayer::getNextTurn()
{
	// Return a random column number for the move
	return randDist(randGen);
}