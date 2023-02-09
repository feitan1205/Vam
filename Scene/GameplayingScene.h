#pragma once
#include <memory>
#include <map>
#include <list>
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
public:
	GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input);


	~GameplayingScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2);
	bool CheckHitCircle(Vec2 playerpos, float circle, Vec2 enemypos, float enemycircle);

private:

	PlayerBase* player_;
	const InputState& input_;
	int animationcount_;
	bool charactervector_;		//右：false、左：true
	bool tmpishitkey_;
	int enemflamecount_;
	Vec2 playerpos_;
	Vec2 playervector_;

	Map* map_;

	std::list<std::shared_ptr<EnemyBase>> enemies_;

	//EnemyBase* enemy_;
	int flyingeyeH_[8];

};

