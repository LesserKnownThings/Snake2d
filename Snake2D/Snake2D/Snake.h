#pragma once
#include <vector>
#include <iostream>
#include <SDL.h>
#include "TimeControl.h"

struct Coordinates
{
	int CurrentIndex = 0;
	int LastKnownIndex = 0;
};

class Snake
{
private:
	enum Direction
	{
		Left = 0,
		Up = 1,
		Right = 2,
		Down = 3
	};

	

public:
	Snake(int index, int movementDirection);
	Snake();
	
private:	
	Direction MovementDirection;	
	Timer T;
	int MovementSpeed = 150;

	
public:
	Coordinates HeadPlacement;
	std::vector<Coordinates> BodyArray;

public:
	bool Move(int gridWidth, int gridHeight, int nodeSize);
	void SetMovementDirection(int direction);
	void AddToBody();

private:
	bool CheckIndex(int index, int gridSize);
};

