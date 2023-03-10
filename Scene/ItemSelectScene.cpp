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
	pw_width = Game::kScreenWidth / 3;	//ウィンドウ枠の幅
	pw_height = Game::kScreenHeight - 200;	//ウィンドウ枠の高さ
	pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//ウィンドウ枠の左
	pw_start_y = (Game::kScreenHeight - pw_height) / 2;	//ウィンドウ枠上

	itemboxsize_.x = Game::kScreenWidth / 3 - 20;
	itemboxsize_.y = 120;

	if (GetRand(100) > 10) {
		selectnum_ = 3;
	}

}

ItemSelectScene::~ItemSelectScene()
{
}

void ItemSelectScene::Update(const InputState& input)
{
	/*if (input.IsTriggered(InputType::pause))
	{
		manager_.PopScene();
		return;
	}*/

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
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x4c5378, true);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

	//ポーズ中メッセージ
	if (player_->GetNowLv() == 1) {
		DrawString((Game::kScreenWidth / 2) - 45, pw_start_y + 10, L"初期武器選択", 0xffff88);
	}
	else {
		DrawString((Game::kScreenWidth / 2) - 30, pw_start_y + 10, L"LvUP!!!", 0xffff88);
	}

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
	
	for (int i = 0; i < selectnum_; i++) {
		DrawBox(pw_start_x + 20, ((pw_start_y + 15 * (i + 1))+ (itemboxsize_.y * i)) + 50, pw_start_x + itemboxsize_.x, ((pw_start_y + 15 * i) + (itemboxsize_.y * (i + 1))) + 30, 0x8f8f8f, true);

		if (player_->GetWeaponLv(selectkind_[i]) == 0) {
			DrawFormatString(pw_start_x + 400, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffff00, L"new", true);
		}
		else if ((player_->GetWeaponLv(selectkind_[i]) + 1) == player_->GetWeaponMaxLv(selectkind_[i])) {
			DrawFormatString(pw_start_x + 400, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xff0000, L"max", true);
		}
		else {
			DrawFormatString(pw_start_x + 400, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"Lv：%d", player_->GetWeaponLv(selectkind_[i]) + 1, true);
		}

		switch (selectkind_[i])
		{
		case PlayerStatus::ao:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"青", true);
			if (player_->GetWeaponLv(selectkind_[i]) == 0) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"向いている方向に青い斬撃を放つ。", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 1) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"クールタイムが0.4秒減少", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 2) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"基礎攻撃力が10上昇", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 3) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"クールタイムが0.4秒減少", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 4) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"クールタイムが0.4秒減少", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 5) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"基礎攻撃力が20上昇", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 6) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"クールタイムが0.4秒減少", true);
			}
			if (player_->GetWeaponLv(selectkind_[i]) == 7) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"基礎攻撃力が20上昇", true);
			}
			break;
		case PlayerStatus::murasaki:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"紫", true);
			if (player_->GetWeaponLv(selectkind_[i]) == 0) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"一定時間頭上に回転を放つ。", true);
			}
			break;
		case PlayerStatus::aka:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"赤", true);
			if (player_->GetWeaponLv(selectkind_[i]) == 0) {
				DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
					L"自分を中心にダメージエリアを展開する。", true);
			}
			break;
		/*case PlayerStatus::bullet:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"弾", true);
			break;*/
		case PlayerStatus::boots:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"ブーツ", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"移動速度が10%%上昇", true);
			break;
		case PlayerStatus::book:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"本", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"クールタイムが10%%減少", true);
			break;
		case PlayerStatus::candle:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"ろうそく", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"攻撃範囲が20%%上昇", true);
			break;
		case PlayerStatus::spinach:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"ほうれん草", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"攻撃力が20%%上昇", true);
			break;
		case PlayerStatus::crown:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"王冠", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"獲得経験値が20%%上昇", true);
			break;
		case PlayerStatus::orb:
			DrawFormatString(pw_start_x + 50, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 50, 0xffffff, L"オーブ", true);
			DrawFormatString(pw_start_x + 100, ((pw_start_y + 15 * (i + 1)) + (itemboxsize_.y * i) + 5) + 75, 0xffffff,
				L"経験値回収エリアが20%%上昇", true);
			break;
		default:
			break;
		}
	}

	SetFontSize(76);

	DrawFormatString(pw_start_x - 10, ((pw_start_y + 15 * (selectidx_ + 1)) + (itemboxsize_.y * selectidx_) + 17) + 40, 0xff0000, L"▶", true);
	DrawFormatString(pw_start_x + itemboxsize_.x - 10, ((pw_start_y + 15 * (selectidx_ + 1)) + (itemboxsize_.y * selectidx_) + 17) + 40, 0xff0000, L"◀", true);

	SetFontSize(16);

}

void ItemSelectScene::SetPlayer(PlayerBase* player)
{
	player_ = player;

	if (player_->GetNowLv() == 1) {

		selectnum_ = 3;

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

	int sortcount = 1;
	int tmpselectkind = 0;

	while(sortcount != 0) {
		sortcount = 0;
		for (int i = 1; i < selectnum_; i++) {
			if (player_->GetWeaponLv(selectkind_[i]) != 0 && player_->GetWeaponLv(selectkind_[i - 1]) == 0) {
				tmpselectkind = selectkind_[i];
				selectkind_[i] = selectkind_[i - 1];
				selectkind_[i - 1] = tmpselectkind;
				sortcount++;
			}
		}
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