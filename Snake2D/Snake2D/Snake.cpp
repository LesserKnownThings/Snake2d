#include "Snake.h"

Snake::Snake(int index, int movementDirection):HeadPlacement(), MovementDirection()
{
	MovementDirection = Direction(movementDirection);
	T = {};
}

Snake::Snake(): HeadPlacement(), MovementDirection()
{

}

/// <summary>
/// Function to move the body with a delay
/// </summary>
/// <param name="gridWidth">The grid width</param>
/// <param name="gridHeight">The grid height</param>
/// <param name="nodeSize">The node size in the grid</param>
/// <returns></returns>
bool Snake::Move(int gridWidth, int gridHeight, int nodeSize)
{


	if (T.ElapsedMils() > MovementSpeed)
	{	
		int NewIndex = 0;
		int YIndex = HeadPlacement.CurrentIndex / gridHeight;
		int XIndex = HeadPlacement.CurrentIndex / gridWidth / gridHeight;
		int CurrentX = HeadPlacement.CurrentIndex;

		switch (MovementDirection)
		{
		case Left:			
			HeadPlacement.LastKnownIndex = HeadPlacement.CurrentIndex;

			NewIndex = CurrentX - gridHeight + (CurrentX * XIndex);

			if (!CheckIndex(NewIndex, gridWidth * gridHeight))
				return false;

			HeadPlacement.CurrentIndex = NewIndex;
			break;

		case Right:
			NewIndex = CurrentX + gridHeight + (CurrentX * XIndex);

			if (!CheckIndex(NewIndex, gridWidth * gridHeight))
				return false;

			HeadPlacement.LastKnownIndex = HeadPlacement.CurrentIndex;
			HeadPlacement.CurrentIndex = NewIndex;
			break;

		case Down:
			NewIndex = HeadPlacement.CurrentIndex + 1;

			if (NewIndex > (YIndex * gridWidth + gridHeight -1))
				return false;

			HeadPlacement.LastKnownIndex = HeadPlacement.CurrentIndex;

			HeadPlacement.CurrentIndex++;
			break;

		case Up:
			NewIndex = HeadPlacement.CurrentIndex - 1;

			if (NewIndex < (YIndex * gridWidth))
				return false;

			HeadPlacement.LastKnownIndex = HeadPlacement.CurrentIndex;
			HeadPlacement.CurrentIndex--;
			break;
		}


		//Move body
		for (int i = 0; i < BodyArray.size(); i++)
		{
			if (i == 0)
			{
				BodyArray[i].LastKnownIndex = BodyArray[i].CurrentIndex;
				BodyArray[i].CurrentIndex = HeadPlacement.LastKnownIndex;
				continue;
			}

			BodyArray[i].LastKnownIndex = BodyArray[i].CurrentIndex;
			BodyArray[i].CurrentIndex = BodyArray[i - 1].LastKnownIndex;

		}

		T = {};
	}

	return true;
}

/// <summary>
/// Changes the movement direction of the Snake
/// </summary>
/// <param name="direction">The intended direction</param>
void Snake::SetMovementDirection(int direction)
{
	if (MovementDirection == Right && direction == 0)
		return;

	if (MovementDirection == Left && direction == 2)
		return;

	if (MovementDirection == Up && direction == 3)
		return;

	if (MovementDirection == Down && direction == 1)
		return;

	MovementDirection = Direction(direction);
}

/// <summary>
/// Adds a new portion to the body
/// </summary>
void Snake::AddToBody()
{
	if (BodyArray.size() == 0)
	{
		Coordinates Coord;
		Coord.LastKnownIndex = HeadPlacement.LastKnownIndex;
		Coord.CurrentIndex = HeadPlacement.LastKnownIndex;
		BodyArray.push_back(Coord);
	}
	else
	{
		Coordinates Coord;
		Coord.LastKnownIndex = BodyArray[BodyArray.size()-1].LastKnownIndex;
		Coord.CurrentIndex = BodyArray[BodyArray.size() - 1].LastKnownIndex;
		BodyArray.push_back(Coord);
	}

}

bool Snake::CheckIndex(int index, int gridSize)
{
	return index >= 0 && index < gridSize;
}