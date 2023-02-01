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
	player_(nullptr),
	enemy_(nullptr),
	input_(input),
	animationcount_(40),
	charactervector_(false),
	map_(nullptr),
	playerpos_(0,0),
	flyingeyeH_()
{
	if (selectcharacter == static_cast<int>(Character::blue)) {
		player_ = new Blue(playerpos_);
	}
	else if (selectcharacter == static_cast<int>(Character::red)) {
		player_ = new Red(playerpos_);
	}
	enemy_ = new FlyingEye();
	enemy_->Init(playerpos_);
	map_ = new Map();
	map_->Init();

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
		playervector_.y = -1;
		
	}
	if (input_.IsPressed(InputType::down)) {
		playervector_.y = 1;
		
	}
	if (input_.IsPressed(InputType::right)) {
		playervector_.x = 1;
		charactervector_ = false;
	}
	if (input_.IsPressed(InputType::left)) {
		playervector_.x = -1;
		charactervector_ = true;
	}

	player_->SetHitBox(playerpos_);
	enemy_->SetHitBox(playerpos_);

	if (CheckHit(player_->GetMinHitBox(), player_->GetMaxHitBox(), enemy_->GetMinHitBox(), enemy_->GetMaxHitBox())) {
		//printfDx(L"・・・・");
		if (enemy_->GetCoolDownTime() <= 0) {
			player_->Damage(enemy_->GetAttackPoint());
			enemy_->SetCoolDownTime();
		}
	}

	if (CheckHitKey(KEY_INPUT_O)) {
		enemy_->Init(playerpos_);
	}

	playervector_ = playervector_.normalize();

	playerpos_ = playerpos_ + playervector_;

	enemy_->Update(playerpos_);

	player_->Update(playerpos_,charactervector_);

	map_->Update(playerpos_);


	playervector_ = {0, 0};
}

void GameplayingScene::Draw()
{

	map_->Draw();

	if (input_.IsPressed(InputType::up)) {
		player_->MoveAnimation(charactervector_);
	}
	else if (input_.IsPressed(InputType::down)) {
		player_->MoveAnimation(charactervector_);
	}
	else if (input_.IsPressed(InputType::right)) {
		player_->MoveAnimation(charactervector_);		
	}
	else if (input_.IsPressed(InputType::left)) {
		player_->MoveAnimation(charactervector_);
	}
	else {
		player_->IdleAnimation(charactervector_);
	}	

	enemy_->Draw(true,playerpos_);

}

bool GameplayingScene::CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2)
{

	if (minhitbox1.y > maxhitbox2.y)		return false;
	if (maxhitbox1.y < minhitbox2.y)		return false;
	if (minhitbox1.x > maxhitbox2.x)		return false;
	if (maxhitbox1.x < minhitbox2.x)		return false;

	return true;
}
