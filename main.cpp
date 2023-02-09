#include <DxLib.h>
#include <cassert>
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "InputState.h"
#include "DrawFunctions.h"
#include "game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;

	SceneManager sceneManager;
	sceneManager.ChangeScene(new TitleScene(sceneManager));

	while (ProcessMessage() != -1) 
	{
		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}