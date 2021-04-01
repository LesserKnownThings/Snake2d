#pragma once
#include <vector>
#include <random>
#include "TimeControl.h"
#include <iostream>

struct Node
{
	int X = 0;
	int Y = 0;
	bool IsObstacle = false;
	bool IsBonus = false;
	bool IsHead = false;
};

class GameGrid
{
public:
	GameGrid(int w, int h, int nodeSize);
	GameGrid();
	void SpawnRandomBonus();
	void ResetNodes();

public:
	std::vector<Node> Nodes;
	int NodeSize;
	int Width, Height;
	
private:
	int GridSize;

private:
	int SpawnDelay = 800;
	Timer T;
};

