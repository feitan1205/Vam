#include <DxLib.h>
#include <cassert>
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "InputState.h"
#include "DrawFunctions.h"
#include "game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	SetWindowText(L"DINO SURVIVOR");

	SetMouseDispFlag(true);

	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 16);
	ChangeWindowMode(false);
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetMouseDispFlag(TRUE);

	InputState input;

	SceneManager sceneManager;
	sceneManager.ChangeScene(new TitleScene(sceneManager));

	while (ProcessMessage() != -1) 
	{
		LONGLONG time = GetNowHiPerformanceCount();

		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		ScreenFlip();

		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();

	return 0;
}