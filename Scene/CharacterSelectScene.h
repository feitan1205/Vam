#pragma once
#include "Scene.h"
#include "../Player/Blue.h"
#include "../Player/Red.h"
#include "../Vector2.h"

enum class Character {

	blue,
	red,
	charactermax

};

class InputState;

class CharacterSelectScene :
	public Scene {

private:

	static constexpr int fade_interval = 60;
	int m_background = -1;	//タイトル画像
	int gradH_ = -1;
	int fadeTimer_ = 0;	//フェードタイマー
	int fadeValue_ = 0;	//黒矩形とのブレンド具合

	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	void (CharacterSelectScene::* updateFunc_)(const InputState& input);

private:

	int bulletinbordH_;
	int characterbordH_;
	int startbuttonH_;
	Vec2 characterbord_;
	Vec2 selectcharacterbord_;
	int characterbordsizeX_;
	int characterbordsizeY_;
	Vec2 startbutton_;
	int startbuttonsizeX_;
	int startbuttonsizeY_;

	bool selectflag_;
	int selectcharacter_;

	Blue* blue_;
	Red* red_;

public:

	CharacterSelectScene(SceneManager& manager);

	~CharacterSelectScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(int posX, int posY, int sizeX, int sizeY);

};
