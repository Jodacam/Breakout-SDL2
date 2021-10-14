#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "player/player.h"
#include "render/SDLRender.h"
#include "events/eventManager.h"
#include "resourceManager/assetsManager.h"
#include <time.h>
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;
bool appIsRunning = true;
int main(int argc, char *argv[])
{

	GameEngine::Renderer *render = new GameEngine::Renderer();
	GameEngine::AssetManager::InitInstance(render);

	SDL_Event event;
	if (!render->Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test"))
	{
		std::cin.get();
		return -1;
	}

	GameEngine::EventManager *eventManager = new GameEngine::EventManager();

	GameEngine::Player *player = new GameEngine::Player();
	player->SetX(220);
	player->SetY(300);

	SDL_Texture *background = GameEngine::AssetManager::getInstance()->AddTexture("resources/img/Hexagon_Pattern.png", "background");

	float deltaTime = 0.0f;
	auto start = SDL_GetTicks();
	while (appIsRunning)
	{

		while (eventManager->PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				appIsRunning = false;
				break;
			case SDL_WINDOWEVENT:
				render->HandleWindowEvent(&event);
				break;
			}
		}

		eventManager->ReadKeyBoard();
		if (eventManager->IsKeyPress(SDL_SCANCODE_C))
			appIsRunning = false;
		if (eventManager->GetController()->GetButton(GameEngine::GameButtonType::START).pressed)
			appIsRunning = false;
		render->ClearScreen();
		render->DrawImage(background, 120, 0, 240, 320);
		player->Render(render);
		player->Update(eventManager, deltaTime);
		render->DrawScreen();
		auto end = SDL_GetTicks();
		float frameTime = end - start;
		deltaTime = frameTime * 0.001;
		// std::cout << "Tiempo en ms : " << frameTime << std::endl;
		// std::cout << "Frames por segundo con esta medida  : " << (1.0f / (frameTime)) * 1000 << std::endl;
		start = SDL_GetTicks();
	}

	render->Close();

	return 0;
}
