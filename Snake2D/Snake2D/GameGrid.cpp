#include "GameGrid.h"

GameGrid::GameGrid(int w, int h, int nodeSize) : NodeSize(nodeSize), Width(w), Height(h), GridSize(w*h)
{
	T = {};

	for(int x = 0; x < w; x ++)
		for (int y = 0; y < h; y++)
		{
			Node CusomNode;
			CusomNode.X = x * nodeSize + nodeSize;
			CusomNode.Y = y * nodeSize + NodeSize;
			CusomNode.IsObstacle = false;
			CusomNode.IsBonus = false;
			CusomNode.IsHead = false;
			Nodes.push_back(CusomNode);
		}

}

GameGrid::GameGrid() : NodeSize(0), Width(0), Height(0), GridSize(0)
{

}

/// <summary>
/// Spawns random bonuses on the game grid
/// </summary>
void GameGrid::SpawnRandomBonus()
{
	if (T.ElapsedMils() > SpawnDelay)
	{
		int R = rand() % GridSize;

		while (Nodes[R].IsObstacle || Nodes[R].IsObstacle || Nodes[R].IsBonus)
		{
			R = rand() % GridSize;
		}

		Nodes[R].IsBonus = true;
		T = {};
	}
}

/// <summary>
/// Resets all the nodes, used to reset game
/// </summary>
void GameGrid::ResetNodes()
{
	for (auto& N : Nodes)
	{
		N.IsBonus = false;
		N.IsHead = false;
		N.IsObstacle = false;
	}
}