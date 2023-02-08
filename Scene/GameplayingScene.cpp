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
#include <cmath>
#include "../Attack/AttackBase.h"

constexpr float kplayerspeed = 1.0;



GameplayingScene::GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input) :
	Scene(manager),
	player_(nullptr),
	//enemy_(nullptr),
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

	player_->Init();
	
	enemies_.push_back(std::make_shared<FlyingEye>());

	for (auto& enem : enemies_) {
		enem->Init(playerpos_);
	}
	map_ = new Map();
	map_->Init();

}

GameplayingScene::~GameplayingScene()
{

	delete player_;
	delete map_;

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
	//enemy_->SetHitBox(playerpos_);

	for (auto& enem : enemies_) {
		enem->SetHitBox(playerpos_);
	}

	playervector_ = playervector_.normalize();
	playerpos_ = playerpos_ + playervector_;

	//enemy_->Update(playerpos_);
	for (auto& enem : enemies_) {
		enem->Update(playerpos_);
	}

	player_->Update(playerpos_,charactervector_);

	map_->Update(playerpos_);

	for (auto& enem : enemies_) {
		if (CheckHit(player_->GetMinHitBox(), player_->GetMaxHitBox(), enem->GetMinHitBox(), enem->GetMaxHitBox())) {
			//printfDx(L"・・・・");
			if (enem->GetCoolDownTime() <= 0) {
				player_->Damage(enem->GetAttackPoint());
				enem->SetCoolDownTime();
			}
		}
	}

	for (auto& enem : enemies_) {
		for (int i = 0; i < player_->GetAttackKindNum(); i++) {
			if (player_->GetAttackingNumber(i) == 1 || player_->GetAttackingNumber(i) == 2) {
				if (player_->GetIsAttack(i)) {
					if (CheckHit(player_->GetAttackMinHitBox(i), player_->GetAttackMaxHitBox(i), enem->GetMinHitBox(), enem->GetMaxHitBox()) && !enem->IsHitAttack(player_->GetAttackingNumber(i))) {
						enem->Damage(player_->GetAttackPoint(i), player_->GetAttackingNumber(i));
						enem->AttackHit(true,player_->GetAttackingNumber(i));
						if (enem->GetNowHP() <= 0) {
							enem->Death();
						}
					}
				}
				else {
					enem->AttackHit(false, player_->GetAttackingNumber(i));
				}
			}
			else if (player_->GetAttackingNumber(i) == 3) {
				if (player_->GetIsAttack(i)) {
					if (CheckHitCircle(playerpos_, player_->GetAttackHitCircle(i), enem->GetMinHitBox(), enem->GetCircle()) && !enem->IsHitAttack(player_->GetAttackingNumber(i))) {
						enem->Damage(player_->GetAttackPoint(i), player_->GetAttackingNumber(i));
						enem->AttackHit(true, player_->GetAttackingNumber(i));
						if (enem->GetNowHP() <= 0) {
							enem->Death();
						}
					}
				}
				else {
					enem->AttackHit(false, player_->GetAttackingNumber(i));
				}
			}
		}
	}	

	auto rmIt = std::remove_if(enemies_.begin(), enemies_.end(),
		[](const std::shared_ptr<EnemyBase>& enemy)
		{
			return !enemy->GetIsEnabled();
		});


	enemies_.erase(rmIt, enemies_.end());


	if (CheckHitKey(KEY_INPUT_O) && !tmpishitkey_) {
		enemies_.push_back(std::make_shared<FlyingEye>());
		enemies_.back()->Init(playerpos_);
	}

	tmpishitkey_ = CheckHitKey(KEY_INPUT_O);

	playervector_ = {0, 0};

}

void GameplayingScene::Draw()
{

	map_->Draw();

	for (auto& enem : enemies_) {
		enem->Draw(true, playerpos_);
	}

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

}

bool GameplayingScene::CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2)
{

	if (minhitbox1.y > maxhitbox2.y)		return false;
	if (maxhitbox1.y < minhitbox2.y)		return false;
	if (minhitbox1.x > maxhitbox2.x)		return false;
	if (maxhitbox1.x < minhitbox2.x)		return false;

	return true;
}

bool GameplayingScene::CheckHitCircle(Vec2 playerpos,float circle,Vec2 enemypos,float enemycircle)
{
	Vec2 distance = playerpos - enemypos;

	float vecdistance = std::hypotf(distance.x , distance.y);

	if (vecdistance < circle + enemycircle) {
		return true;
	}
	
	return false;
}