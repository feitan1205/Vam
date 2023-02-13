#include "ItemSelectScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../Player/PlayerBase.h"
#include "../game.h"

ItemSelectScene::ItemSelectScene(SceneManager& manager):
	Scene(manager),
	finishlvup_or_creat(false)
{
}

ItemSelectScene::~ItemSelectScene()
{
}

void ItemSelectScene::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PopScene();
		return;
	}

	if (finishlvup_or_creat) {
		return;
	}

	/*if (GetRand(9) / 5 == 1) {
		lvup_or_creat = true;
	}
	else */
	{
		lvup_or_creat = false;
	}

	if (player_->GetAttackKindNum() == 3) {
		lvup_or_creat = false;
	}

	/*if (lvup_or_creat) {

	}*/

	if (!lvup_or_creat) {
		levelupweaponnumber_ = GetRand(player_->GetAttackKindNum() - 1);
		player_->SetLv(levelupweaponnumber_);
	}

	finishlvup_or_creat = true;

}

void ItemSelectScene::Draw()
{
	constexpr int pw_width = Game::kScreenWidth / 2;	//ポーズ枠の幅
	constexpr int pw_height = Game::kScreenHeight - 100;	//ポーズ枠の高さ
	constexpr int pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//ポーズ枠の左
	constexpr int pw_start_y = (Game::kScreenHeight - pw_height) / 2;	//ポーズ枠上

	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//ポーズウィンドウセロファン(黒い)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

	//ポーズ中メッセージ
	DrawString((Game::kScreenWidth / 2) + 30, pw_start_y + 10, L"LvUP!!!", 0xffff88);

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);

	/*for (int i = 0; i < player_->GetAttackKindNum(); i++) {

		DrawFormatString(pw_start_x + 50, pw_start_y + 50 * (i + 1), 0xffffff, L"%d", player_->GetAttackingNumber(i), true);

		DrawFormatString(pw_start_x + 120, pw_start_y + 50 * (i + 1), 0xffffff, L"%d", player_->GetWeaponLv(i), true);
	}*/

	DrawFormatString(pw_start_x + 100, pw_start_y + 100, 0xffffff, L"%dが%dレベルに上がりました。", player_->GetAttackingNumber(levelupweaponnumber_),player_->GetWeaponLv(levelupweaponnumber_), true);

	DrawFormatString(pw_start_x + 100, pw_start_y + 700, 0xffffff,L"Pボタンで再開", true);

}
