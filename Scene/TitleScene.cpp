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

	ChangeVolumeSoundMem((255 - fadeValue_), titleBGM_);
}

void TitleScene::NormalUpdate(const InputState& input)
{
	//次へのボタンが押されたら次のシーンへ行く
	if (CheckHit(m_startbutton.x, m_startbutton.y, m_buttonsize.x, m_buttonsize.y)) {
		if (input.IsTriggered(InputType::next))
		{
			StopSoundMem(titleBGM_);
			PlaySoundMem(selectsound_, DX_PLAYTYPE_BACK);
			//updateFunc_ = &TitleScene::FadeOutUpdate;
			isnextscene_ = true;
		}
	}

	if (!CheckSoundMem(selectsound_) && isnextscene_) {
		manager_.ChangeScene(new GameplayingScene(manager_, 0, input));
		return;
	}

	/*if ()
	{
		manager_.ChangeScene(new OptionScene(manager_));
		return;
	}*/

	if (CheckHitKey(KEY_INPUT_P) || input.IsTriggered(InputType::prev)) {
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
	m_buttonsize(),
	m_optionbuttonX(),
	m_optionbuttonY(),
	m_optionbuttonsizeX(),
	m_optionbuttonsizeY(),
	isnextscene_(false)
{

	m_background = my::MyLoadGraph(L"Data/background/titlebackground.png");
	m_startbuttonH = my::MyLoadGraph(L"Data/img/buttons.png");
	gradH_ = my::MyLoadGraph(L"Data/img/gradetion.jpg");
	titleBGM_ = LoadSoundMem(L"Data/Sound/TitleBGM.wav");
	selectsound_ = LoadSoundMem(L"Data/Sound/select.wav");

	m_buttonsize.x = 150;
	m_buttonsize.y = m_buttonsize.x / 3;

	PlaySoundMem(titleBGM_, DX_PLAYTYPE_LOOP);

}

TitleScene::~TitleScene()
{
	DeleteGraph(m_background);
	DeleteSoundMem(titleBGM_);
	DeleteSoundMem(selectsound_);
}

void TitleScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	//普通の描画
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_background, true);

	m_startbutton.x = Game::kScreenWidth / 2 - m_buttonsize.x / 2;
	m_startbutton.y = (Game::kScreenHeight / 3) * 2;

	DrawExtendGraph(m_startbutton.x, m_startbutton.y, m_startbutton.x + m_buttonsize.x, m_startbutton.y + m_buttonsize.y, m_startbuttonH, true);

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
