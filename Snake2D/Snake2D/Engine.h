#pragma once
#include "Colors.h"
#include <SDL.h>
#include <string>
#include "GameGrid.h"
#include "Snake.h"

class Engine
{
 
public:
	Engine(int screenWidth, int screenHeight,const char* appName);

private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_Surface* Surface;
	SDL_Event Event;

private:
	int ScreenWidht;
	int ScreenHeight;
	int FSPDelay = 250;
	const Uint8* Keys;
	Timer T;

private:
	GameGrid Grid;
	Snake Player;
	void DrawBorders();
	void DrawGrid();

public:
	bool IsRunning;
	Uint64 FirstFrameCall;
	Uint64 LasFrameCall;

public:
	void Update();
	void EventUpdate();
	void Draw();
	void FPSDisplay();

public:
	int GetWidth(){ return ScreenWidht; }
	int GetHeight() { return ScreenHeight; }
};

