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

using namespace std;

Game::Game(Player& _p1, Player& _p2)
{
	// Set up initial game state and players
	p1 = &_p1;
	p2 = &_p2;
	currentState = GameState::TurnP1;
	clearBoard();
}

// Returns the current state of the game as a
// GameState enum
GameState Game::getState()
{
	return currentState;
}

// Returns true if a game is currently in session
bool Game::isRunning()
{
	return currentState == GameState::TurnP1 || currentState == GameState::TurnP2;
}

// Returns the token type at the specified position in the board.
// Types: Empty, Player1, Player2
BoardField Game::operator()(int x, int y) const
{
	return board[x][y];
}

// Executes the next player turn if the game is running
void Game::nextTurn()
{
	if (!isRunning()) return;

	// Get token type and player class pointer for
	// who has the next turn
	BoardField playerToken = BoardField::Player1;
	Player* nextPlayer = p1;

	if (currentState == GameState::TurnP2)
	{
		playerToken = BoardField::Player2;
		nextPlayer = p2;
	}

	// Get their move's row and column from the player
	int moveCol = -1;
	int moveRow = -1;

	while (moveRow == -1)
	{
		moveCol = nextPlayer->getNextTurn() - 1;
		moveRow = makeMove(moveCol, playerToken);
	}
	
	// Determine if the game has a winner
	GameState winner;
	bool hasWinner = getWinner(winner, moveCol, moveRow);

	if (hasWinner)
	{
		// A player won or the game ended in a draw
		currentState = winner;
	}
	else
	{
		// Advance turn to next player
		if (currentState == GameState::TurnP1)
			currentState = GameState::TurnP2;
		else
			currentState = GameState::TurnP1;
	}
}

// Clears the entire game board with the BoardField::Empty flag
void Game::clearBoard()
{
	for (int y = 0; y < BoardHeight; y++)
	{
		for (int x = 0; x < BoardWidth; x++)
		{
			board[x][y] = BoardField::Empty;
		}
	}
}

// Checks if the given column number is within the
// game board, and checks if there is available space
// for a token
bool Game::isValidMove(const int moveCol)
{
	if (moveCol < 0 || moveCol >= BoardWidth)
		return false;

	if (board[moveCol][0] != BoardField::Empty)
		return false;

	return true;
}

// Returns true if the entire board has been filled with
// player tokens
bool Game::boardIsFilled()
{
	for (int x = 0; x < BoardWidth; x++)
	{
		if (board[x][0] == BoardField::Empty) return false;
	}

	return true;
}

// Attempt to place a player token in the specified board column
// Returns the y position of placed token if successful
// Returns -1 if the move is invalid
int Game::makeMove(const int moveCol, const BoardField move)
{
	// Make sure move is valid
	if (!isValidMove(moveCol)) return -1;

	int yPos = 0;

	// Locate resting place for token in column
	for (; yPos < BoardHeight; yPos++)
	{
		if (board[moveCol][yPos] != BoardField::Empty)
			break;
	}

	// Place token at correct position
	yPos--;
	board[moveCol][yPos] = move;

	return yPos;
}

// Returns true if the specified token was a game winning or game ending move.
// This method works by checking tokens in all 8 directions from the given token,
// looking for a sequence of 'ConnectLength' number of tokens.
// Returns false if no 'ConnectLength' sequences are found radiating from given token.
bool Game::getWinner(GameState& stateOut, const int lastMoveX, const int lastMoveY)
{
	// Check for a draw
	if (boardIsFilled())
	{
		stateOut = GameState::Draw;
		return true;
	}

	// Construct arrays for all valid moves in 8 directions
	const int dirX[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
	const int dirY[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };

	// Get the token type at the given board position
	// We need to find a sequence of 'ConnectLength' tokens
	// of this type.
	const BoardField moveType = board[lastMoveX][lastMoveY];

	// Loop through all 8 directions
	for (int dir = 0; dir < 8; dir++)
	{
		// Get x and y direction moves
		const int moveDirX = dirX[dir];
		const int moveDirY = dirY[dir];

		// Counts the number of identical tokens in the current direction
		int sequenceCounter = 0;

		// Check 'ConnectLength' of tokens in the current direction
		for (int dist = 0; dist < ConnectLength; dist++)
		{
			// Get position of next token in current direction
			int x = lastMoveX + (moveDirX * dist);
			int y = lastMoveY + (moveDirY * dist);

			// Check if position is on the board, and if the
			// token at that position is the same type
			if (x < 0 || y < 0) break;
			if (x >= BoardWidth || y >= BoardHeight) break;
			if (board[x][y] != moveType) break;

			// Increment token sequence counter
			sequenceCounter++;
		}

		// If we have a sequence that is 'ConnectLength' long,
		// we found a winning token sequence. Return the winner.
		if (sequenceCounter >= ConnectLength)
		{
			if (moveType == BoardField::Player1)
				stateOut = GameState::P1Won;
			else 
				stateOut = GameState::P2Won;

			return true;
		}
	}

	// No winning sequences were found around the specified token
	return false;
}
