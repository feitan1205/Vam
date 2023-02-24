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
#include "ItemSelectScene.h"
#include "../game.h"

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
	enemflamecount_(10),
	tmpLv_(0),
	timer(),
	maxenemynum_(10),
	enemylv_(0),
	enemynum_ ()
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

	enemies_.back()->ChangeExp(playerpos_);

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

	frametimer++;

	if (frametimer == 60) {
		timer++;
		frametimer = 0;
		if (timer % 50 == 1) {
			maxenemynum_+=10;
			enemylv_++;
		}
	}

	

	printfDx(L"%d\n", enemylv_);

	//レベルアップ時の選択画面へ移動
	if (player_->GetNowLv() != tmpLv_) {
		ItemSelectScene* pnextscene;
		pnextscene = new ItemSelectScene(manager_);
		pnextscene->SetPlayer(player_);
		manager_.PushScene(pnextscene);
	}
	tmpLv_ = player_->GetNowLv();

	//エネミー生成へのカウントダウン
	enemflamecount_--;

	//シーンの変更
	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}

	//プレイヤーの移動入力/////////////////////
	if (input_.IsPressed(InputType::up)) {
		playervector_.y = -2;
		
	}
	if (input_.IsPressed(InputType::down)) {
		playervector_.y = 2;
		
	}
	if (input_.IsPressed(InputType::right)) {
		playervector_.x = 2;
		charactervector_ = false;
	}
	if (input_.IsPressed(InputType::left)) {
		playervector_.x = -2;
		charactervector_ = true;
	}
	////////////////////////////////////////////
	
	//プレイヤーの斜め移動処理
	playervector_ = (playervector_.normalize()) * player_->GetPlayerSpeed();
	playerpos_ = playerpos_ + playervector_;

	//プレイヤーのヒットボックスをセット
	player_->SetHitBox(playerpos_);

	//エネミーのヒットボックスのセット
	for (auto& enem : enemies_) {
		enem->SetHitBox(playerpos_);
	}

	//enemy_->Update(playerpos_);
	for (auto& enem : enemies_) {
		enem->Update(playerpos_);
	}

	//プレイヤーのアップデート
	player_->Update(playerpos_,charactervector_);

	//マップのアップデート
	map_->Update(playerpos_);

	//エネミーの攻撃処理（プレイヤーとあたっていた場合）
	for (auto& enem : enemies_) {
		if (CheckHit(player_->GetMinHitBox(), player_->GetMaxHitBox(), enem->GetMinHitBox(), enem->GetMaxHitBox())) {
			//printfDx(L"・・・・");
			if (enem->GetCoolDownTime() <= 0) {
				player_->Damage(enem->GetAttackPoint());
				enem->SetCoolDownTime();
			}
		}
	}


	//プレイヤーの攻撃処理（プレイヤーの攻撃種別）
	for (auto& enem : enemies_) {
		if (enem->GetIsExp())continue;
		for (int i = 0; i < player_->GetAttackKindNum(); i++) {
			if (player_->GetAttackingNumber(i) == 0 || player_->GetAttackingNumber(i) == 1) {
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
			else if (player_->GetAttackingNumber(i) == 2) {
				if (player_->GetIsAttack(i)) {
					if (CheckHitCircle(playerpos_, player_->GetAttackHitCircle(i), enem->GetPos(), enem->GetCircle()) && !enem->IsHitAttack(player_->GetAttackingNumber(i))) {
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

	for (auto& enem : enemies_) {
		if (CheckHit(player_->GetMinHitBox(), player_->GetMaxHitBox(), enem->GetMinHitBox(), enem->GetMaxHitBox()) && enem->GetIsExp()) {
			player_->GetExp(enem->GetExpPoint());
			enem->DeleteEnable();
		}
	}

	//死亡かつ経験値でもないエネミーをempty

	auto rmIt = std::remove_if(enemies_.begin(), enemies_.end(),
		[](const std::shared_ptr<EnemyBase>& enemy)
		{
			return !(enemy->GetIsEnabled() || enemy->GetIsExp());
		});

	//emptyエネミーのメモリ削除
	enemies_.erase(rmIt, enemies_.end());

	//printfDx(L"%d\n", enemies_.size());

	for (auto& enem : enemies_) {
		if (enem->GetIsEnabled()) {
			enemynum_++;
		}
	}

	if (enemynum_ <= maxenemynum_) {
		//oキーを押したときとエネミーカウントが0になったときエネミー生成
		if ((CheckHitKey(KEY_INPUT_O) && !tmpishitkey_) || enemflamecount_ < 0) {
			enemies_.push_back(std::make_shared<FlyingEye>());
			enemies_.back()->Init(playerpos_);
			enemies_.back()->EnemyLvUp(enemylv_);
			enemflamecount_ = 10;
		}
	}
	tmpishitkey_ = CheckHitKey(KEY_INPUT_O);

	//プレイヤーのベクトルを初期化

	playervector_ = {0, 0};
	
	enemynum_ = 0;

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


	/*DrawFormatString(300, 300, 0xffffff, L"%f", playerpos_.x, true);
	DrawFormatString(300, 316, 0xffffff, L"%f", playerpos_.y, true);*/

	/*for (auto& enem : enemies_) {
		DrawFormatString(400, 300, 0xffffff, L"%f", enem->GetPos().x, true);
		DrawFormatString(400, 316, 0xffffff, L"%f", enem->GetPos().y, true);
		break;
	}*/

	SetFontSize(32);

	DrawFormatString((Game::kScreenWidth / 2) - 48, 10, 0xffffff, L"%02d：%02d", timer / 60 ,timer % 60, true);

	SetFontSize(16);

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
	float num = circle + enemycircle;
	if (vecdistance <= num) {
		return true;
	}
	
	return false;
}