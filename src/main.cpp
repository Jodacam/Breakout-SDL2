#include <iostream>
#include <string>
#include <sstream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "engine/render/SDLRender.h"
#include "engine/events/EventManager.h"
#include "engine/resourceManager/AssetsManager.h"
#include "engine/scenes/SceneManager.h"
#include "game/scenes/GameScene.h"
#include "engine/audio/AudioManager.h"
#include "engine/scenes/LuaScene.h"
#include <time.h>
#include "engine/consts/logger.h"
#include "engine/canvas/Canvas.h"
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
const int SCREEN_HEIGHT = 277;
const int AUDIO_WAVE_LENGTH = 22050/2;
#endif
#ifndef PSP
const int AUDIO_WAVE_LENGTH = 22050*2;
const int SCREEN_HEIGHT = 277;
#endif
bool appIsRunning = true;
int main(int argc, char *argv[])
{
#ifdef PSP
	SetupCallbacks();
#endif
	InitLogger();
	//GameEngine::Renderer *render = new GameEngine::Renderer();
	GameEngine::Renderer *render = GameEngine::Renderer::GetInstance();
	GameEngine::AssetManager::InitInstance(render);
	SDL_Event event;
	if (!render->Init(SCREEN_WIDTH, SCREEN_HEIGHT, "Test"))
	{
		std::cin.get();
		return -1;
	}

	GameEngine::AudioManager::Init(AUDIO_WAVE_LENGTH, MIX_DEFAULT_FORMAT, 2, 4096);

	GameEngine::EventManager *eventManager = GameEngine::EventManager::Instance();
	GameEngine::SceneManager *manager = GameEngine::SceneManager::Instance();

	//Load all needed data for the game.
	GameEngine::AssetManager::GetInstance()->AddSong("resources/audio/music/test.ogg", "default");
	GameEngine::AssetManager::GetInstance()->AddSoundEffect("resources/audio/sfx/Collide/bonk-4.wav","bounce");
	GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Racket.png","player");
	GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Hexagon_Pattern.png", "background");
	GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Left.png", "leftborder");
	GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Right.png", "rightborder");
	GameEngine::AssetManager::GetInstance()->AddTexture("resources/img/Border_Top.png", "topborder");


	//Load Game first scene
	manager->AddScene(new GameEngine::LuaScene("resources/scripts/scene1.lua"));
	manager->ChangeScene(0);

	float deltaTime = 0.0f;
	auto start = SDL_GetTicks();
	float timer = 2;
	float actualTimer = 0;
	int frameCount = 0;
	/* GameEngine::Text frameText;
	frameText.SetText("Delta : ms\nFrames:  ", true); */


	GameEngine::Canvas c = GameEngine::Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto frameText = c.CreateElementOfType<GameEngine::UIText>("Delta : ms\nFrames:  ",GameEngine::Vector(0,50));

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
		eventManager->UpdateInput();

		if (eventManager->GetController()->GetButton(GameEngine::GameButtonType::B).pressed)
			appIsRunning = false;

		GameEngine::Scene *scene = manager->GetActualScene();
		render->ClearScreen();
		scene->Update(deltaTime);
		scene->Render(render);
		c.Render(render);
		render->DrawScreen();

		auto end = SDL_GetTicks();
		float frameTime = end - start;
		deltaTime = frameTime * 0.001;
		actualTimer += deltaTime;
		frameCount++;
		start = SDL_GetTicks();
		if (actualTimer > timer)
		{
			float averageDelta = actualTimer / frameCount;
			frameCount = 0;
			actualTimer = 0;
			std::stringstream s;
			s << "Delta: " << int(averageDelta * 1000) << "ms\nFrames: " << int(1 / (averageDelta));
			frameText->SetText(s.str(), true);
		}
	}
	render->Close();

	return 0;
}
