#include <DxLib.h>
#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include "PauseScene.h"
#include "../Player/Blue.h"
#include "../Player/Red.h"
#include "CharacterSelectScene.h"
#include "../Map/Map.h"
#include "../Enemy/EnemyBase.h"
#include "../Enemy/FlyingEye.h"

constexpr float kplayerspeed = 1.0;

GameplayingScene::GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input) :
	Scene(manager),
	m_player(nullptr),
	m_enemy(nullptr),
	input_(input),
	animationcount(40),
	charactervector_(false),
	map(nullptr),
	playerpos(1280/2,740/2),
	flyingeyeH_()
{
	if (selectcharacter == static_cast<int>(Character::blue)) {
		m_player = new Blue();
	}
	else if (selectcharacter == static_cast<int>(Character::red)) {
		m_player = new Red();
	}
	m_enemy = new FlyingEye();
	map = new Map();
	map->Init();

}

void GameplayingScene::Update(const InputState& input)
{

	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}

	if (input_.IsPressed(InputType::up)) {
		playerpos.y += kplayerspeed;
		m_enemy->PlayerMove(Vec2(0, kplayerspeed));
	}
	if (input_.IsPressed(InputType::down)) {
		playerpos.y -= kplayerspeed;
		m_enemy->PlayerMove(Vec2(0, kplayerspeed));
	}
	if (input_.IsPressed(InputType::right)) {
		playerpos.x -= kplayerspeed;
		charactervector_ = false;
		m_enemy->PlayerMove(Vec2(kplayerspeed, 0));
	}
	if (input_.IsPressed(InputType::left)) {
		playerpos.x += kplayerspeed;
		charactervector_ = true;
		m_enemy->PlayerMove(Vec2(kplayerspeed, 0));
	}

	if (CheckHitKey(KEY_INPUT_O)) {
		m_enemy->Init(playerpos);
	}

	m_enemy->Update(playerpos);

	m_player->Update();

	map->Update(playerpos);

}

void GameplayingScene::Draw()
{

	map->Draw();

	if (input_.IsPressed(InputType::up)) {
		m_player->MoveAnimation(charactervector_);
	}
	else if (input_.IsPressed(InputType::down)) {
		m_player->MoveAnimation(charactervector_);
	}
	else if (input_.IsPressed(InputType::right)) {
		m_player->MoveAnimation(charactervector_);		
	}
	else if (input_.IsPressed(InputType::left)) {
		m_player->MoveAnimation(charactervector_);
	}
	else {
		m_player->IdleAnimation(charactervector_);
	}

	DrawFormatString(0, 16, 0xffffff, L"%f", playerpos.x, true);

	m_enemy->Draw(true);

}