#include "PauseScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../game.h"
#include "../DrawFunctions.h"

constexpr int kattackkindnum = 4;

PauseScene::PauseScene(SceneManager& manager) :
	Scene(manager),
	allmoveposition_()
{
	buttonH_ = my::MyLoadGraph(L"Data/img/buttons.png");
	pw_width = Game::kScreenWidth / 3;	//ウィンドウ枠の幅
	pw_height = Game::kScreenHeight - 200;	//ウィンドウ枠の高さ
	pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//ウィンドウ枠の左
	pw_start_y = (Game::kScreenHeight - pw_height) / 2;	//ウィンドウ枠上
	allmoveposition_.x = Game::kScreenWidth;

	itemboxsize_.x = 150;
	itemboxsize_.y = itemboxsize_.x / 3;

}

PauseScene::~PauseScene()
{
}

void PauseScene::SetPlayingScene(GameplayingScene* playingscene)
{
	playingscene_ = playingscene;
}

void PauseScene::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PopScene();
		return;
	}

	if (input.IsTriggered(InputType::prev)) {
		playingscene_->SetFinishFlag();
		manager_.PopScene();
		return;
	}

	if (allmoveposition_.x > 10) {
		allmoveposition_.x -= Game::kScreenWidth / 10;
		return;
	}
	
}

void PauseScene::Draw()
{

	//SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//セレクトウィンドウセロファン
	DrawBox(pw_start_x + allmoveposition_.x, pw_start_y, pw_start_x + pw_width + allmoveposition_.x, pw_start_y + pw_height, 0x4c5378, true);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

	//ポーズ中メッセージ
	DrawString((Game::kScreenWidth / 2) - 45 + allmoveposition_.x, pw_start_y + 10, L"ポーズ", 0xffff88);

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x + allmoveposition_.x, pw_start_y, pw_start_x + pw_width + allmoveposition_.x, pw_start_y + pw_height, 0xffffff, false);

}



bool PauseScene::CheckHit(int posX, int posY, int sizeX, int sizeY)
{

	int mouseX = 0;
	int mouseY = 0;

	GetMousePoint(&mouseX, &mouseY);

	if (mouseX < posX) return false;
	if (mouseX > sizeX) return false;
	if (mouseY < posY) return false;
	if (mouseY > sizeY) return false;

	return true;
}
