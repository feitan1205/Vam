#include "CharacterSelectScene.h"
#include "GameplayingScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include <DxLib.h>
#include "../Player/Blue.h"
#include "../Player/Red.h"


void CharacterSelectScene::NormalUpdate(const InputState& input)
{
	//次へのボタンが押されたら次のシーンへ行く
	for (int i = 0; i < static_cast<int>(Character::charactermax); i++) {
		if (CheckHit(characterbord.x + 116 * i, characterbord.y + 3, 110 * (i + 1), 110 * (i + 1))) {
			if (input.IsTriggered(InputType::next) && i == static_cast<int>(Character::blue))
			{
				m_selectcharacter = static_cast<int>(Character::blue);
				m_selectflag = true;
			}
			if (input.IsTriggered(InputType::next) && i == static_cast<int>(Character::red))
			{
				m_selectcharacter = static_cast<int>(Character::red);
				m_selectflag = true;
			}
		}
	}

	if (m_selectflag && CheckHit(m_startbutton.x, m_startbutton.y, m_startbutton.x + m_startbuttonsizeX, m_startbutton.y + m_startbuttonsizeX)) {
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
		manager_.ChangeScene(new GameplayingScene(manager_, m_selectcharacter, input));
		return;
	}
}

CharacterSelectScene::CharacterSelectScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&CharacterSelectScene::NormalUpdate),
	m_selectflag(false),
	m_selectcharacter(-1)
{
	m_background = my::MyLoadGraph(L"Data/background/red.jpg");
	m_characterbordH = my::MyLoadGraph(L"Data/img/Characterbord.png");
	m_startbuttonH = my::MyLoadGraph(L"Data/img/startbutton.png");

	characterbord.x = ((1280 / 2) - ((1280 / 2) / 4) * 2);
	characterbord.y = 45;

	selectcharacterbord.x = characterbord.x + 15;
	selectcharacterbord.y = 610 + 5;

	m_startbutton.x = ((1280 / 2) + ((1280 / 2) / 8) * 2);
	m_startbutton.y = 630;

	GetGraphSize(m_characterbordH, &characterbordsizeX, &characterbordsizeY);
	GetGraphSize(m_startbuttonH, &m_startbuttonsizeX, &m_startbuttonsizeY);
}

CharacterSelectScene::~CharacterSelectScene()
{
	DeleteGraph(m_background);
	DeleteGraph(m_bulletinbordH);
	DeleteGraph(m_characterbordH);
	DeleteGraph(m_startbuttonH);
}

void CharacterSelectScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void CharacterSelectScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, m_background, true);

	//キャラクター選択ボードの描画
	DrawBox((1280 / 2) - ((1280 / 2) / 4) * 2, 40, (1280 / 2) + ((1280 / 2) / 4) * 2, 700, 0x734e30, true);
	DrawBox((1280 / 2) - ((1280 / 2) / 4) * 2, 40, (1280 / 2) + ((1280 / 2) / 4) * 2, 700, 0x000000, false);

	DrawBox(((1280 / 2) - ((1280 / 2) / 4) * 2) - 10, 35, ((1280 / 2) + ((1280 / 2) / 4) * 2) + 10, 43, 0x734e30, true);
	DrawBox(((1280 / 2) - ((1280 / 2) / 4) * 2) - 10, 35, ((1280 / 2) + ((1280 / 2) / 4) * 2) + 10, 43, 0x000000, false);

	//キャラクターボックスの描画
	for (int i = 0; i < static_cast<int>(Character::charactermax); i++) {

		DrawExtendGraph(characterbord.x + 120 * i + 10, characterbord.y, characterbord.x + 120 * (i + 1) - 10, 150, m_characterbordH, true);

		if (i == static_cast<int>(Character::blue)) {
			DrawExtendGraph(characterbord.x + 120 * i + 10, characterbord.y + 10, characterbord.x + 120 * (i + 1) - 10, 150 - 10, blue.GetHandle(), true);
		}
		if (i == static_cast<int>(Character::red)) {
			DrawExtendGraph(characterbord.x + 120 * i + 10, characterbord.y + 10, characterbord.x + 120 * (i + 1) - 10, 150 - 10, red.GetHandle(), true);
		}
	}

	//選択したキャラクター表示の描画
	DrawBox((1280 / 2) - ((1280 / 2) / 4) * 2 + 10, 610, (1280 / 2) + ((1280 / 2) / 4) * 2 - 10, 610 + 80, 0x845f41, true);
	DrawBox((1280 / 2) - ((1280 / 2) / 4) * 2 + 10, 610, (1280 / 2) - ((1280 / 2) / 4) * 2 + 80 + 10, 610 + 80, 0x000000, false);
	DrawBox((1280 / 2) - ((1280 / 2) / 4) * 2 + 10, 610, (1280 / 2) + ((1280 / 2) / 4) * 2 - 10, 610 + 80, 0x000000, false);

	DrawExtendGraph(selectcharacterbord.x, selectcharacterbord.y, selectcharacterbord.x + 70, selectcharacterbord.y + 70, m_characterbordH, true);

	if (m_selectflag) {
		if (m_selectcharacter == static_cast<int>(Character::blue)) {
			DrawExtendGraph(selectcharacterbord.x, selectcharacterbord.y, selectcharacterbord.x + 70, selectcharacterbord.y + 70, blue.GetHandle(), true);
		}
		if (m_selectcharacter == static_cast<int>(Character::red)) {
			DrawExtendGraph(selectcharacterbord.x, selectcharacterbord.y, selectcharacterbord.x + 70, selectcharacterbord.y + 70, red.GetHandle(), true);
		}
		DrawGraph(m_startbutton.x, m_startbutton.y, m_startbuttonH, false);
	}

	int mouseX = 0;
	int mouseY = 0;

	GetMousePoint(&mouseX, &mouseY);
	DrawFormatString(0, 0, 0xffffff, L"%d", mouseX, true);
	DrawFormatString(0, 16, 0xffffff, L"%d", characterbord.x, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 1280, 740, 0x000000, true);

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
