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

#ifndef _GAME_H__
#define _GAME_H__

#include "players.h"

enum GameState
{
	TurnP1,
	TurnP2,
	P1Won,
	P2Won,
	Draw
};

enum BoardField
{
	Empty,
	Player1,
	Player2
};

class Game
{
public:
	static const unsigned int BoardWidth = 7;
	static const unsigned int BoardHeight = 6;
	static const unsigned int ConnectLength = 4;

	Game(Player& _p1, Player& _p2);
	GameState getState();
	bool isRunning();
	BoardField operator()(int x, int y) const;
	void nextTurn();
private:
	BoardField board[BoardWidth][BoardHeight];
	GameState currentState;
	Player* p1;
	Player* p2;
	void clearBoard();
	bool isValidMove(const int moveCol);
	bool boardIsFilled();
	int makeMove(const int moveCol, const BoardField move);
	bool getWinner(GameState& winnerOut, const int lastMoveX, const int lastMoveY);
};

#endif