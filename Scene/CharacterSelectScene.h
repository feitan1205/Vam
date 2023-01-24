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

	int m_bulletinbordH;
	int m_characterbordH;
	int m_startbuttonH;
	Vec2 characterbord;
	Vec2 selectcharacterbord;
	int characterbordsizeX;
	int characterbordsizeY;
	Vec2 m_startbutton;
	int m_startbuttonsizeX;
	int m_startbuttonsizeY;

	bool m_selectflag;
	int m_selectcharacter;

	Blue blue;
	Red red;

public:

	CharacterSelectScene(SceneManager& manager);

	~CharacterSelectScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(int posX, int posY, int sizeX, int sizeY);

};
