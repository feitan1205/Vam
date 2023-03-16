#include "DxLib.h"
#include "FlyingEye.h"
#include "../DrawFunctions.h"
#include "../game.h"
#include <cmath>

constexpr int standardcooldowntime = 30;


FlyingEye::FlyingEye() :
	flamecount_(),
	attackpoint_(2),
	cooldowntime_(),
	tmprand_(),
	level_(),
	nowhp_(3),
	temphp_(),
	damagepoint_(),
	damagedrawframe_(),
	isEnabled_(true),
	expH1_(),
	expH2_(),
	isEnabledexp_(false),
	explv_(),
	exppoint_(),
	speed_(1.0),
	expmove_(false),
	expspeed_(0.6)
{
	expH1_ = my::MyLoadGraph(L"Data/exp/orb6.png");
	expH2_ = my::MyLoadGraph(L"Data/exp/orb4.png");
	for (int i = 0; i < 3; i++) {
		attackhit_[i] = false;
		damagedrawframe_ [i] = -1;
	}
}

FlyingEye::~FlyingEye()
{
}

void FlyingEye::Init(Vec2 playerpos)
{

	ChangeVolumeSoundMem(100, hitsound_);

	isEnabled_ = true;

	playerpos_ = playerpos;

	//nowhp_ = 5;
	
	bool iscreate = true;

	while (iscreate) {
		pos_.x = GetRand(Game::kScreenWidth);
		pos_.y = GetRand(Game::kScreenHeight);
		iscreate = CheckHit(pos_, pos_, Vec2{ 50,50 }, Vec2{ Game::kScreenWidth - 50,Game::kScreenHeight - 50 });
	}

	pos_ += playerpos;

	pos_.x -= Game::kScreenWidth / 2;
	pos_.y -= Game::kScreenHeight / 2;

}

void FlyingEye::End()
{
}

void FlyingEye::Update(Vec2 playerpos)
{

	playerpos_ = playerpos;

	if (expmove_) {
		ExpMove();
	}

	for (int i = 0; i < 3; i++) {
		damagedrawframe_[i]--;
	}

	if (isEnabledexp_) {
		return;
	}

	cooldowntime_--;

	vector_ = playerpos - pos_;

	vector_ = vector_.normalize();

	pos_ += (vector_ * speed_);

	
	if (vector_.x < 0) {
		left_or_right = true;
	}
	else if (vector_.x > 0) {
		left_or_right = false;
	}

	if (pos_.x + (Game::kScreenWidth / 2) - playerpos.x < -100 ||
		pos_.x + (Game::kScreenWidth / 2) - playerpos.x > Game::kScreenWidth + 100 ||
		pos_.y + (Game::kScreenHeight / 2) - playerpos.y < -100 ||
		pos_.y + (Game::kScreenHeight / 2) - playerpos.y > Game::kScreenHeight + 100) {
		isEnabled_ = false;
		isEnabledexp_ = false;
	}


	flamecount_++;

	if (flamecount_ >= 80) {
		flamecount_ = 0;
	}

	temphp_ = nowhp_;

}

void FlyingEye::Draw(bool charactervector,Vec2 playerpos)
{

	

	if (isEnabledexp_) {
		switch (explv_) {
		case 1:
			DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, expH1_, true);
			break;
		case 2:
			DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, expH2_, true);
			break;
		default:
			break;
		}
		for (int i = 0; i < 3; i++) {
			if (damagedrawframe_[i] >= 0) {
				DrawFormatString(damagepos_.x + (Game::kScreenWidth / 2) - playerpos.x - 5, damagepos_.y + (Game::kScreenHeight / 2) - playerpos.y - 5, 0xffffff, L"%d", damagepoint_[i], true);
			}
		}
		return;
	}

	

	if (flamecount_ >= 0 && flamecount_ < 10) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[0], true, left_or_right);
	}
	else if (flamecount_ >= 10 && flamecount_ < 20) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[1], true, left_or_right);
	}
	else if (flamecount_ >= 20 && flamecount_ < 30) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[2], true, left_or_right);
	}
	else if (flamecount_ >= 30 && flamecount_ < 40) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[3], true, left_or_right);
	}
	else if (flamecount_ >= 40 && flamecount_ < 50) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[4], true, left_or_right);
	}
	else if (flamecount_ >= 50 && flamecount_ < 60) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[5], true, left_or_right);
	}
	else if (flamecount_ >= 60 && flamecount_ < 70) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[6], true, left_or_right);
	}
	else if (flamecount_ >= 70 && flamecount_ < 80) {
		DrawRotaGraph(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 1, 0, FlyinteyeH_[7], true, left_or_right);
	}

	/*DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos.y, 0x000000, false);
	DrawCircle(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, hitcircle_, 0xff0000, false);*/

	for (int i = 0; i < 3; i++) {
		if (damagedrawframe_[i] >= 0) {
			DrawFormatString(pos_.x + (Game::kScreenWidth / 2) - playerpos.x, pos_.y + (Game::kScreenHeight / 2) - playerpos.y, 0xffffff, L"%d", damagepoint_[i], true);
		}
	}

}

void FlyingEye::SetData(int hitsound)
{
	hitsound_ = hitsound;
}

void FlyingEye::PlayerMove(Vec2 playermove)
{

	pos_ -= playermove;

}

void FlyingEye::Damage(int attackpoint,int attacknumber)
{

	damagepos_ = pos_;

	nowhp_ -= attackpoint;
	damagepoint_[attacknumber] = attackpoint;

	ChangeVolumeSoundMem(255, hitsound_);

	PlaySoundMem(hitsound_,DX_PLAYTYPE_BACK);

}

void FlyingEye::Death()
{

	//if (GetRand(100) / 10 <= 1) 
	{
		isEnabledexp_ = true;
		isEnabled_ = false;
		for (int i = 0; i < 8; i++) {
			DeleteGraph(FlyinteyeH_[i]);
		}
		explv_ = 1;
	}
	/*else {
		isEnabled_ = false;
	}*/

	cooldowntime_ = 1;

	if (isEnabledexp_ && level_ > 5 && GetRand(100) / 50 <= 1) {
		explv_ = 2;
		exppoint_ = 2;
		return;
	}

	exppoint_ = 1;

}

void FlyingEye::SetHitBox(Vec2 playerpos)
{

	minhitbox_.x = pos_.x - 20;
	minhitbox_.y = pos_.y - 10;
	maxhitbox_.x = pos_.x + 20;
	maxhitbox_.y = pos_.y + 20;
	minexphitbox_.x = pos_.x - 3;
	minexphitbox_.y = pos_.y - 3;
	maxexphitbox_.x = pos_.x + 3;
	maxexphitbox_.y = pos_.y + 3;

	hitcircle_ = 15;

}

void FlyingEye::SetCoolDownTime()
{

	cooldowntime_ = standardcooldowntime;

}

bool FlyingEye::CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2)
{

	if (minhitbox1.y > maxhitbox2.y)		return false;
	if (maxhitbox1.y < minhitbox2.y)		return false;
	if (minhitbox1.x > maxhitbox2.x)		return false;
	if (maxhitbox1.x < minhitbox2.x)		return false;

	return true;
}

void FlyingEye::EnemyLvUp(int level)
{
	level_ = level;
	nowhp_ *= level;
	if (level_ >= 4) {
		speed_ += 0.3;
	}
}

void FlyingEye::ChangeExp(Vec2 pos)
{

	pos_ = pos;

	isEnabledexp_ = true;
	isEnabled_ = false ;
	for (int i = 0; i < 8; i++) {
		DeleteGraph(FlyinteyeH_[i]);
	}
	explv_ = 1;
	exppoint_ = 1;
	cooldowntime_ = 1;

}

void FlyingEye::HitExp()
{

	expmove_ = true;

	expvector_ = playerpos_ - pos_;

	expvector_ = (expvector_.normalize()) * 5;
	//tmpexpvector_ = expvector_;

}

void FlyingEye::ExpMove()
{

	if (abs(expvector_.x) > abs(tmpexpvector_.x) || abs(expvector_.y) > abs(tmpexpvector_.y)) {

		vector_ = ((playerpos_ - pos_) / 10) * expspeed_;
		pos_ += vector_;
		expspeed_ += 0.1;
		//expvector_ = vector_;

	}
	else {
		expvector_ -= (expvector_ / 2);
		tmpexpvector_ = expvector_;
		pos_ -= (expvector_ * expspeed_);
	}

	
}
