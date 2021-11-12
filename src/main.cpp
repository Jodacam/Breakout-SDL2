#include <iostream>
#include <string>
#include <sstream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "render/SDLRender.h"
#include "events/EventManager.h"
#include "resourceManager/AssetsManager.h"
#include "game/SceneManager.h"
#include "game/scenes/GameScene.h"
#include <time.h>
#include "consts/logger.h"
#ifdef PSP
#include <pspkernel.h>
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

int CallbackThread(SceSize args, void *argp)
{
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

int SetupCallbacks(void)
{
	int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if (thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}
	return thid;
}
#endif

const int SCREEN_WIDTH = 480;
#ifdef PSP
const int SCREEN_HEIGHT = 320;
#endif
#ifndef PSP
const int SCREEN_HEIGHT = 320;
#endif
bool appIsRunning = true;
int main(int argc, char *argv[])
{
#ifdef PSP
	SetupCallbacks();
#endif
	InitLogger();
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
	GameEngine::SceneManager *manager = GameEngine::SceneManager::Instance();
	manager->AddScene(new GameEngine::GameScene());
	manager->ChangeScene(0);
	float timer = 5;
	float actualTimer = 0;
	int frameCount = 0;
	while (appIsRunning)
	{
		/*

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

		if (eventManager->IsKeyPress(SDL_SCANCODE_C))
			appIsRunning = false;
				 */
		eventManager->ReadKeyBoard();
		if (eventManager->GetController()->GetButton(GameEngine::GameButtonType::START).pressed)
			appIsRunning = false;
		GameEngine::Scene *_scene = manager->GetActualScene();
		render->ClearScreen();
		_scene->Render(render);
		_scene->Update(deltaTime);
		render->DrawScreen();
		auto end = SDL_GetTicks();
		float frameTime = end - start;
		deltaTime = frameTime * 0.001;
		actualTimer += deltaTime;
		frameCount++;
		if (actualTimer > timer)
		{
			float averageDelta = actualTimer / frameCount;
			frameCount = 0;
			actualTimer = 0;
			std::stringstream s;
			s << "La media de delta fue de : " << averageDelta;
			printLog(s.str());
		}

		// std::cout << "Tiempo en ms : " << frameTime << std::endl;
		// std::cout << "Frames por segundo con esta medida  : " << (1.0f / (frameTime)) * 1000 << std::endl;
		start = SDL_GetTicks();
	}

	render->Close();

	return 0;
}
