#include <iostream>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "render/SDLRender.h"
#include "events/EventManager.h"
#include "resourceManager/AssetsManager.h"
#include "game/SceneManager.h"
#include "game/scenes/GameScene.h"
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
	GameEngine::EventManager *eventManager = GameEngine::EventManager::Instance();
	float deltaTime = 0.0f;
	auto start = SDL_GetTicks();
	GameEngine::SceneManager* manager = GameEngine::SceneManager::Instance();
	manager->AddScene(new GameEngine::GameScene());
	manager->ChangeScene(0);
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


		GameEngine::Scene* _scene = manager->GetActualScene();
		render->ClearScreen();
		_scene->Render(render);
		_scene->Update(deltaTime);
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
