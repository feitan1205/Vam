#include "ItemSelectScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../Player/PlayerBase.h"
#include "../game.h"

constexpr int kattackkindnum = 4;

ItemSelectScene::ItemSelectScene(SceneManager& manager) :
	Scene(manager),
	finishlvup(false),
	selectidx_(0),
	selectnum_(4),
	selectok_(false)
{
	pw_width = Game::kScreenWidth / 2;	//ウィンドウ枠の幅
	pw_height = Game::kScreenHeight - 100;	//ウィンドウ枠の高さ
	pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//ウィンドウ枠の左
	pw_start_y = (Game::kScreenHeight - pw_height) / 2;	//ウィンドウ枠上

	itemboxsize_.x = Game::kScreenWidth / 2 - 60;
	itemboxsize_.y = 100;

	if (GetRand(100) > 10) {
		selectnum_ = 3;
	}

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

	if (finishlvup) {
		manager_.PopScene();
		return;
	}

	if (input.IsTriggered(InputType::down))
	{
		selectidx_++;

		if (selectidx_ >= selectnum_) {
			selectidx_ = selectnum_ - 1;
		}
	}
	if (input.IsTriggered(InputType::up))
	{
		selectidx_--;

		if (selectidx_< 0) {
			selectidx_ = 0;
		}
	}

	

	if (input.IsTriggered(InputType::prev)) {
		player_->SetLv(selectkind_[selectidx_]);
		finishlvup = true;
		return;
	}

	if (input.IsTriggered(InputType::next)) {
		for (int i = 0; i < selectnum_; i++) {
			if (CheckHit(pw_start_x + 50, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i), pw_start_x + itemboxsize_.x, (pw_start_y + 30 * i) + (itemboxsize_.y * (i + 1)))) {
				player_->SetLv(selectkind_[i]);
				finishlvup = true;
				break;
			}
		}
	}

}

void ItemSelectScene::Draw()
{
	
	if (finishlvup) {
		return;
	}

	//SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//ポーズウィンドウセロファン(黒い)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x8f8f8f, true);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

	//ポーズ中メッセージ
	DrawString((Game::kScreenWidth / 2) - 30, pw_start_y + 10, L"LvUP!!!", 0xffff88);

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
	
	for (int i = 0; i < selectnum_; i++) {
		DrawBox(pw_start_x + 50, ((pw_start_y + 30 * (i + 1))+ (itemboxsize_.y * i)) + 20, pw_start_x + itemboxsize_.x, ((pw_start_y + 30 * i) + (itemboxsize_.y * (i + 1))) + 20, 0xffffff, true);
		DrawFormatString(pw_start_x + 50 + 500, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"Lv：%d", player_->GetWeaponLv(selectkind_[i]) + 1,true);
		switch (selectkind_[i])
		{
		case PlayerStatus::ao:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"青：", true);
			break;
		case PlayerStatus::murasaki:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"紫：", true);
			break;
		case PlayerStatus::aka:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"赤：", true);
			break;
		case PlayerStatus::bullet:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"弾：", true);
			break;
		case PlayerStatus::boots:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"ブーツ：", true);
			DrawFormatString(pw_start_x + 50 + 125, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 45, 0x000000, 
				L"移動速度が10%%上昇", true);
			break;
		case PlayerStatus::book:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"本：", true);
			break;
		case PlayerStatus::candle:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"ろうそく：", true);
			break;
		case PlayerStatus::spinach:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"ほうれん草：", true);
			DrawFormatString(pw_start_x + 50 + 125, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 45, 0x000000,
				L"攻撃力が20%%上昇", true);
			break;
		case PlayerStatus::crown:
			DrawFormatString(pw_start_x + 50 + 50, ((pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5) + 20, 0x000000, L"王冠：", true);
			break;
		default:
			break;
		}
	}

	SetFontSize(32);

	DrawFormatString(pw_start_x + 40, ((pw_start_y + 30 * (selectidx_ + 1)) + (itemboxsize_.y * selectidx_) + 17) + 20, 0xff0000, L"▶", true);

	SetFontSize(16);

}

void ItemSelectScene::SetPlayer(PlayerBase* player)
{
	player_ = player;

	if (player_->GetNowLv() == 1) {

		selectnum_ = 4;

		for (int i = 0; i < selectnum_; i++) {
			selectkind_[i] = i;
		}

		//selectkind_[0] = PlayerStatus::boots;
		//selectkind_[1] = PlayerStatus::spinach;
		return;
	}

	for (int i = 0; i < selectnum_; i++) {
		while (!selectok_) {
			selectkind_[i] = GetRand(PlayerStatus::kindmax - 1);

			selectok_ = true;

			if (player_->GetWeaponLv(selectkind_[i]) == player_->GetWeaponMaxLv(selectkind_[i])) {
				selectok_ = false;
			}

			for (int j = i - 1; j >= 0; j--) {
				if (selectkind_[i] == selectkind_[j]) {
					selectok_ = false;
				}
			}
		

		}
		selectok_ = false;
	}

}

bool ItemSelectScene::CheckHit(int posX, int posY, int sizeX, int sizeY)
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