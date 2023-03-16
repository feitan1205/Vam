#pragma once
#include "Scene.h"
#include "../Vector2.h"

class InputState;

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{

	//描画変数
private:
	static constexpr int fade_interval = 60;
	int m_background = -1;	//タイトル画像
	int gradH_ = -1;
	int fadeTimer_ = fade_interval;	//フェードタイマー
	int fadeValue_ = 255;	//黒矩形とのブレンド具合

	//フェードインの時のUpdate関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	//Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(const InputState& input);

	//各種ボタン変数
private:

	int m_startbuttonH = -1;
	Vec2 m_startbutton;
	Vec2 m_buttonsize;
	int m_optionbuttonH = -1;
	int m_optionbuttonX;
	int m_optionbuttonY;
	int m_optionbuttonsizeX;
	int m_optionbuttonsizeY;
	bool isnextscene_;
	int titleBGM_;
	int selectsound_;

public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(int posX, int posY, int sizeX, int sizeY);

};