#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "player/player.h"
#include "render/SDLRender.h"
#include "events/eventManager.h"
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
bool appIsRunning = true;
int main(int argc, char *argv[])
{

	//The surface contained by the window
	GameEngine::Renderer *render = new GameEngine::Renderer();
	GameEngine::EventManager *eventManager = new GameEngine::EventManager();
	GameEngine::Player * player = new GameEngine::Player();   
	player->SetX(100);
	player->SetY(100);
	SDL_Event event;
	if (!render->Init(SCREEN_WIDTH, SCREEN_HEIGHT,"Test"))
	{
		std::cin.get();
		return -1;
	}


	SDL_Texture * background = render->LoadTexture("resources/img/Hexagon_Pattern.png");

	while (appIsRunning)
	{
		
		while (eventManager->PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				appIsRunning = false;
				break;
			}
		}

		
		eventManager->ReadKeyBoard();
		if(eventManager->IsKeyPress(SDL_SCANCODE_C)) appIsRunning = false;

		render->ClearScreen();
		render->DrawImage(background,rand() % 480,rand() % 320,100,100);
		render->DrawScreen();
	}

	render->Close();

	return 0;
}
