#pragma once
#include "../Vector2.h"
#include "Scene.h"

class PlayerBase;
class EnemyBase;
class InputState;
class Map;

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
private:

	PlayerBase* m_player;
	const InputState& input_;
	int animationcount;
	bool charactervector_;		//右：false、左：true

	Vec2 playerpos;

	Map* map;

	EnemyBase* m_enemy;
	int flyingeyeH_[8];

public:
	GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input);


	~GameplayingScene() {}

	void Update(const InputState& input);
	void Draw();
};

