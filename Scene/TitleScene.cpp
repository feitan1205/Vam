#include "TitleScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "CharacterSelectScene.h"
#include "OptionScene.h"
#include "GameplayingScene.h"
#include <DxLib.h>
#include "../DrawFunctions.h"
#include "../game.h"

void TitleScene::FadeInUpdate(const InputState& input)
{
	//真っ黒から徐々に表示する場合場合
	fadeValue_ = (int)(255.0f * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval)));
	//グラデーションを使って徐々に表示する場合
	/*fadeTimer_;*/
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		fadeValue_ = 0;
	}

}

void TitleScene::NormalUpdate(const InputState& input)
{
	//次へのボタンが押されたら次のシーンへ行く
	if (CheckHit(m_startbutton.x, m_startbutton.y, m_startbuttonsizeX, m_startbuttonsizeY)) {
		if (input.IsTriggered(InputType::next))
		{
			//updateFunc_ = &TitleScene::FadeOutUpdate;
			manager_.ChangeScene(new CharacterSelectScene(manager_));
			return;
		}
	}
	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new OptionScene(manager_));
		return;
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		manager_.ChangeScene(new GameplayingScene(manager_,0,input));
		return;
	}

}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255.0f * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval)
	{
		manager_.ChangeScene(new CharacterSelectScene(manager_));
		return;
	}
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&TitleScene::FadeInUpdate),
	m_startbutton(),
	m_startbuttonsizeX(),
	m_startbuttonsizeY(),
	m_optionbuttonX(),
	m_optionbuttonY(),
	m_optionbuttonsizeX(),
	m_optionbuttonsizeY()
{

	m_background = my::MyLoadGraph(L"Data/background/red.jpg");
	m_startbuttonH = my::MyLoadGraph(L"Data/img/startbutton.png");
	gradH_ = my::MyLoadGraph(L"Data/img/gradetion.jpg");

	GetGraphSize(m_startbuttonH, &m_startbuttonsizeX, &m_startbuttonsizeY);
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_background);
}

void TitleScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	//普通の描画
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_background, true);

	DrawString(Game::kScreenWidth / 2 - (16 * 11) / 2, 200, L"ヴァンパイアサバイバー", 0xffffff, true);

	m_startbutton.x = Game::kScreenWidth / 2 - m_startbuttonsizeX / 2;
	m_startbutton.y = Game::kScreenHeight / 2;

	DrawGraph(m_startbutton.x, m_startbutton.y, m_startbuttonH, false);

	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

bool TitleScene::CheckHit(int posX, int posY, int sizeX, int sizeY)
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
