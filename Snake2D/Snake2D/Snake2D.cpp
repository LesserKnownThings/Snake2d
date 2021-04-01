// Snake2D is a classic Snake game that I made using the SDL library
// Author: Marius Ursu (LesserKnownThings)
//

#include "Engine.h"

int main(int argc, char** args)
{
	std::string AppName = "Snake 2d";
	Engine E { 300,300, AppName.c_str()};
	

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		while (E.IsRunning)
		{
			E.FirstFrameCall = SDL_GetPerformanceCounter();

			E.Draw();
			E.Update();						

			E.LasFrameCall = SDL_GetPerformanceCounter();


			E.FPSDisplay();
		}
	}
	

	return 0;
}

