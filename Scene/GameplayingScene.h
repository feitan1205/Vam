#pragma once
#include "Scene.h"

class PlayerBase;
class InputState;

/// <summary>
/// ƒQ[ƒ€’†ƒV[ƒ“
/// </summary>
class GameplayingScene : public Scene
{
private:

	PlayerBase* m_player;
	const InputState& input_;
	int animationcount;

public:
	GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input);


	~GameplayingScene() {}

	void Update(const InputState& input);
	void Draw();
};

