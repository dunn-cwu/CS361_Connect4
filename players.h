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

#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include <random>
#include <time.h>   

class Player
{
public:
	virtual int getNextTurn() = 0;
};

class HumanPlayer : public Player
{
public:
	virtual int getNextTurn() override;
};

class AiPlayer : public Player
{
public:
	AiPlayer();
	virtual int getNextTurn() override;
private:
	std::random_device randDevice;
	std::mt19937 randGen;
	std::uniform_int_distribution<> randDist;
};

#endif // !__PLAYERS_H__
