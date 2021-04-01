#include "Engine.h"



Engine::Engine(int screenWidth, int screenHeight, const char* appName) : IsRunning(true), Event(), ScreenHeight(screenHeight), ScreenWidht(screenWidth), FirstFrameCall(), LasFrameCall()
{
	Window = SDL_CreateWindow(appName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	Surface = SDL_GetWindowSurface(Window);	


	int NodeSize = 10;
	int W = (ScreenWidht - 20) / NodeSize;
	int H = (ScreenHeight - 20) / NodeSize;

	Grid = { W,H,NodeSize };	

	int PlayerIndex = 0;
	int StartDirection = 2; // Right Movement
	Player = { PlayerIndex, StartDirection };
	Coordinates C;
}

/// <summary>
/// Function to draw the borders of the game
/// </summary>
void Engine::DrawBorders()
{
	SDL_SetRenderDrawColor(Renderer, Color.Green.r, Color
		.Green.g, Color.Green.b, SDL_ALPHA_OPAQUE);

	SDL_Rect TopRect = {0,0,ScreenWidht, 10};
	SDL_Rect LeftRect = { 0,0,10, ScreenHeight };
	SDL_Rect RightRect = {ScreenWidht - 10, 0, 10, ScreenHeight};
	SDL_Rect BottomRect = {0, ScreenHeight - 10, ScreenWidht, 10};

	SDL_RenderFillRect(Renderer, &TopRect);
	SDL_RenderFillRect(Renderer, &LeftRect);
	SDL_RenderFillRect(Renderer, &RightRect);
	SDL_RenderFillRect(Renderer, &BottomRect);
}

/// <summary>
/// Function to draw the game grid
/// </summary>
void Engine::DrawGrid()
{
	SDL_SetRenderDrawColor(Renderer, Color.DarkBlue.r, Color.DarkBlue.g, Color.DarkBlue.b, SDL_ALPHA_OPAQUE);	

	for( int x = 0; x < Grid.Width; x ++)
		for (int y = 0; y < Grid.Height; y++)
		{
			SDL_Rect r = {x * Grid.NodeSize + Grid.NodeSize, y * Grid.NodeSize + Grid.NodeSize, Grid.NodeSize, Grid.NodeSize };
			SDL_RenderFillRect(Renderer, &r);
		}	
}

/// <summary>
/// Update loop, all actions go here
/// </summary>
void Engine::Update()
{	
	Grid.SpawnRandomBonus();

	int CurrentIndex = Player.HeadPlacement.CurrentIndex;

	std::vector<Coordinates> ChildrenIndexes = Player.BodyArray;

	bool CanMove = Player.Move(Grid.Width, Grid.Height, Grid.NodeSize);

	for (auto Index : ChildrenIndexes)
		Grid.Nodes[Index.CurrentIndex].IsObstacle = false;
	for (auto Index : Player.BodyArray)
		Grid.Nodes[Index.CurrentIndex].IsObstacle = true;

	Grid.Nodes[CurrentIndex].IsHead = false;
	Grid.Nodes[Player.HeadPlacement.CurrentIndex].IsHead = true;

	if (Grid.Nodes[Player.HeadPlacement.CurrentIndex].IsBonus)
	{
		Grid.Nodes[Player.HeadPlacement.CurrentIndex].IsBonus = false;
		Player.AddToBody();

	}

	if (!CanMove || Grid.Nodes[Player.HeadPlacement.CurrentIndex].IsObstacle)
	{
		Grid.ResetNodes();
		Player = { 0,2 };
		Player.BodyArray.clear();
	}

	EventUpdate();
}

/// <summary>
/// Function called to get game events
/// </summary>
void Engine::EventUpdate()
{
	while (SDL_PollEvent(&Event) != 0)
	{
		Keys = SDL_GetKeyboardState(nullptr);

		switch (Event.type)
		{
		case SDL_QUIT:
			IsRunning = false;
			break;

		case SDL_KEYDOWN:
			if (Keys[SDL_SCANCODE_LEFT])
				Player.SetMovementDirection(0);
			else if (Keys[SDL_SCANCODE_UP])
				Player.SetMovementDirection(1);
			else if (Keys[SDL_SCANCODE_RIGHT])
				Player.SetMovementDirection(2);
			else if (Keys[SDL_SCANCODE_DOWN])
				Player.SetMovementDirection(3);
			else if (Keys[SDL_SCANCODE_A])
				Player.AddToBody();
			break;
		}
	
	}
}

/// <summary>
/// Function called to draw the game
/// </summary>
void Engine::Draw()
{
	SDL_SetRenderDrawColor(Renderer, Color.Black.r, Color.Black.g, Color.Black.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Renderer);


	DrawBorders();
	DrawGrid();

	for (auto node : Grid.Nodes)
	{
		if (node.IsHead)
			SDL_SetRenderDrawColor(Renderer, Color.Yellow.r, Color.Yellow.g, Color.Yellow.b, SDL_ALPHA_OPAQUE);
		else if (node.IsObstacle)
			SDL_SetRenderDrawColor(Renderer, Color.Green.r, Color.Green.g, Color.Green.b, SDL_ALPHA_OPAQUE);
		else if (node.IsBonus)
			SDL_SetRenderDrawColor(Renderer, Color.Silver.r, Color.Silver.g, Color.Silver.b, SDL_ALPHA_OPAQUE);
		else 
			SDL_SetRenderDrawColor(Renderer, Color.DarkBlue.r, Color.DarkBlue.g, Color.DarkBlue.b, SDL_ALPHA_OPAQUE);
		

		SDL_Rect CurrentRect = { node.X, node.Y, Grid.NodeSize / 1.5f, Grid.NodeSize / 2 };
		SDL_RenderFillRect(Renderer, &CurrentRect);
	}
	

	SDL_RenderPresent(Renderer);
}

/// <summary>
/// Displays the current FPS in the game window
/// </summary>
void Engine::FPSDisplay()
{
	if (T.ElapsedMils() > FSPDelay)
	{
		float Elapsed = (LasFrameCall - FirstFrameCall) / (float)SDL_GetPerformanceFrequency();

		std::string FPS = "Current FPS: " + std::to_string(static_cast<int>(1.0f / Elapsed));

		SDL_SetWindowTitle(Window, FPS.c_str());
		T = {};
	}
}