#pragma once
#include "Scene.h"

class PlayerBase;
class InputState;

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
private:

	PlayerBase* m_player;
	const InputState& input_;
	int animationcount;
	bool charactervector_;		//右：true、左：false

public:
	GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input);


	~GameplayingScene() {}

	void Update(const InputState& input);
	void Draw();
};

