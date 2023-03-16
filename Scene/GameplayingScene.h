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

	bool CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2);		//四角の当たり判定
	bool CheckHitCircle(Vec2 playerpos, float circle, Vec2 enemypos, float enemycircle);	//円の当たり判定

private:

	const InputState& input_;	//入力キーの取得
	Map* map_;					//マップ
	PlayerBase* player_;		//プレイヤー
	Vec2 playerpos_;			//プレイヤーの座標
	Vec2 playervector_;			//プレイヤーの移動ベクトル
	bool charactervector_;		//プレイヤーの向いている方向　右：false、左：true
	std::list<std::shared_ptr<EnemyBase>> enemies_;	//エネミー
	int animationcount_;		//アニメーションのためのカウント
	int enemflamecount_;		//エネミー生成のカウント
	int tmpLv_;					//過去レベルの保管
	bool tmpishitkey_;			//過去キーの保管
	int frametimer;
	int timer;
	int maxenemynum_;
	int enemylv_;
	int enemynum_;
	Vec2 enemypos_;
	int hitsoundhandle_;
	int lvupsoundhandle_;
	int catchexpsoundhandle_;
	int gamebgm_;
	bool timeenemycreat_;

	static constexpr int fade_interval = 60;
	int fadeTimer_ = 0;	//フェードタイマー
	int fadeVolume_ = 0;	//黒矩形とのブレンド具合

};

