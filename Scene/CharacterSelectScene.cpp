#include "CharacterSelectScene.h"
#include "GameplayingScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include <DxLib.h>
#include "../Player/Blue.h"
#include "../Player/Red.h"
#include "../game.h"

void CharacterSelectScene::NormalUpdate(const InputState& input)
{
	//次へのボタンが押されたら次のシーンへ行く
	for (int i = 0; i < static_cast<int>(Character::charactermax); i++) {
		if (CheckHit(characterbord_.x + 116 * i, characterbord_.y + 3, 110 * (i + 1), 110 * (i + 1))) {
			if (input.IsTriggered(InputType::next) && i == static_cast<int>(Character::blue))
			{
				selectcharacter_ = static_cast<int>(Character::blue);
				selectflag_ = true;
			}
			if (input.IsTriggered(InputType::next) && i == static_cast<int>(Character::red))
			{
				selectcharacter_ = static_cast<int>(Character::red);
				selectflag_ = true;
			}
		}
	}

	if (selectflag_ && CheckHit(startbutton_.x, startbutton_.y, startbutton_.x + startbuttonsizeX_, startbutton_.y + startbuttonsizeX_)) {
		if (input.IsTriggered(InputType::next))
		{
			updateFunc_ = &CharacterSelectScene::FadeOutUpdate;
		}
	}
}

void CharacterSelectScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255.0f * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval)
	{
		manager_.ChangeScene(new GameplayingScene(manager_, selectcharacter_, input));
		return;
	}
}

CharacterSelectScene::CharacterSelectScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&CharacterSelectScene::NormalUpdate),
	selectflag_(false),
	selectcharacter_(-1)
{

	blue_ = new Blue(Vec2(0, 0));
	red_ = new Red(Vec2(0, 0));

	m_background = my::MyLoadGraph(L"Data/background/red.jpg");
	characterbordH_ = my::MyLoadGraph(L"Data/img/Characterbord.png");
	startbuttonH_ = my::MyLoadGraph(L"Data/img/startbutton.png");

	characterbord_.x = ((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2);
	characterbord_.y = 45;

	selectcharacterbord_.x = characterbord_.x + 15;
	selectcharacterbord_.y = Game::kScreenHeight + 5;

	startbutton_.x = ((Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 8) * 2);
	startbutton_.y = Game::kScreenHeight;

	GetGraphSize(characterbordH_, &characterbordsizeX_, &characterbordsizeY_);
	GetGraphSize(startbuttonH_, &startbuttonsizeX_, &startbuttonsizeY_);
}

CharacterSelectScene::~CharacterSelectScene()
{
	DeleteGraph(m_background);
	DeleteGraph(bulletinbordH_);
	DeleteGraph(characterbordH_);
	DeleteGraph(startbuttonH_);
}

void CharacterSelectScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void CharacterSelectScene::Draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_background, true);

	//キャラクター選択ボードの描画
	DrawBox((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2, 40, (Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2, Game::kScreenHeight, 0x734e30, true);
	DrawBox((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2, 40, (Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2, Game::kScreenHeight, 0x000000, false);

	DrawBox(((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2) - 10, 35, ((Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2) + 10, 43, 0x734e30, true);
	DrawBox(((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2) - 10, 35, ((Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2) + 10, 43, 0x000000, false);

	//キャラクターボックスの描画
	for (int i = 0; i < static_cast<int>(Character::charactermax); i++) {

		DrawExtendGraph(characterbord_.x + 120 * i + 10, characterbord_.y, characterbord_.x + 120 * (i + 1) - 10, 150, characterbordH_, true);

		if (i == static_cast<int>(Character::blue)) {
			DrawExtendGraph(characterbord_.x + 120 * i + 10, characterbord_.y + 10, characterbord_.x + 120 * (i + 1) - 10, 150 - 10, blue_->GetHandle(), true);
		}
		if (i == static_cast<int>(Character::red)) {
			DrawExtendGraph(characterbord_.x + 120 * i + 10, characterbord_.y + 10, characterbord_.x + 120 * (i + 1) - 10, 150 - 10, red_->GetHandle(), true);
		}
	}

	//選択したキャラクター表示の描画
	DrawBox((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2 + 10, 610, (Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2 - 10, 610 + 80, 0x845f41, true);
	DrawBox((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2 + 10, 610, (Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2 + 80 + 10, 610 + 80, 0x000000, false);
	DrawBox((Game::kScreenWidth / 2) - ((Game::kScreenWidth / 2) / 4) * 2 + 10, 610, (Game::kScreenWidth / 2) + ((Game::kScreenWidth / 2) / 4) * 2 - 10, 610 + 80, 0x000000, false);

	DrawExtendGraph(selectcharacterbord_.x, selectcharacterbord_.y, selectcharacterbord_.x + 70, selectcharacterbord_.y + 70, characterbordH_, true);

	if (selectflag_) {
		if (selectcharacter_ == static_cast<int>(Character::blue)) {
			DrawExtendGraph(selectcharacterbord_.x, selectcharacterbord_.y, selectcharacterbord_.x + 70, selectcharacterbord_.y + 70, blue_->GetHandle(), true);
		}
		if (selectcharacter_ == static_cast<int>(Character::red)) {
			DrawExtendGraph(selectcharacterbord_.x, selectcharacterbord_.y, selectcharacterbord_.x + 70, selectcharacterbord_.y + 70, red_->GetHandle(), true);
		}
		DrawGraph(startbutton_.x, startbutton_.y, startbuttonH_, false);
	}

	int mouseX = 0;
	int mouseY = 0;

	GetMousePoint(&mouseX, &mouseY);
	DrawFormatString(0, 0, 0xffffff, L"%d", mouseX, true);
	DrawFormatString(0, 16, 0xffffff, L"%d", characterbord_.x, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	/*SetDrawBlendMode(DX_BLENDMODE_MULA, fadeValue_);
	//画面全体をテクスチャで塗りつぶす
	DrawGraph(0, 0, gradH_, true);*/

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool CharacterSelectScene::CheckHit(int posX, int posY, int sizeX, int sizeY)
{
	int mouseX = 0;
	int mouseY = 0;

	GetMousePoint(&mouseX, &mouseY);


	if (mouseX < posX) return false;
	if (mouseX > posX + sizeX) return false;
	if (mouseY < posY) return false;
	if (mouseY > posY + sizeY) return false;

	return true;
}
