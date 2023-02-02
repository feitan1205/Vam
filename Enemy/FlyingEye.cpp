#include "DxLib.h"
#include "FlyingEye.h"
#include "../DrawFunctions.h"

constexpr float kspeed = 0.5;
constexpr int standardcooldowntime = 30;

FlyingEye::FlyingEye():
	flamecount_(),
	attackpoint_(2),
	cooldowntime_(),
	tmprand_(),
	nowhp_(100),
	temphp_(),
	damagepoint_(),
	damageflag_(),
	attack1hit_(false),
	damagedrawframe_()
{
	LoadDivGraph(L"Data/Enemy/FlyingEye.png", 8, 8, 1, 150, 63, handle_);
}

FlyingEye::~FlyingEye()
{
	for (int i = 0; i < 8; i++) {
		DeleteGraph(handle_[i]);
	}
}

void FlyingEye::Init(Vec2 playerpos)
{
	nowhp_ = 100;
		
	int tempx = 0;
	int tempy = 0;
	bool issetpos = true;

	while (issetpos) {

		tempx = (GetRand(700));
		tempy = (GetRand(450));

		if (tempx > 680){

			if (GetRand(1) == 0) {
				tempx *= 1;
			}
			else {
				tempx *= -1;
			}

			issetpos = false;

		}

		if (tempy > 400) {

			if (GetRand(1) == 0) {
				tempy *= 1;
			}
			else {
				tempy *= -1;
			}

			issetpos = false;

		}
		
	}

	/*tmprand_ = GetRand(3);

	if (tmprand_ == 1) {
		tempx *= -1;
	}
	else if (tmprand_ == 2) {
		tempy *= -1;
	}
	else if (tmprand_ == 3) {
		tempx *= -1;
		tempy *= -1;
	}*/

	pos_.x = playerpos.x + tempx;
	pos_.y = playerpos.y + tempy;


}

void FlyingEye::End()
{
}

void FlyingEye::Update(Vec2 playerpos)
{
	cooldowntime_--;

	vector_ = playerpos - pos_;

	vector_ = vector_.normalize();

	pos_ += (vector_ * kspeed);

	if (attack1hit_ && damagedrawframe_ == 30) {
		damagepoint_ = temphp_ - nowhp_;
	}

	if (attack1hit_) {
		damagedrawframe_--;
	}
	else {
		damagedrawframe_ = 30;
	}


	flamecount_++;

	if (flamecount_ >= 80) {
		flamecount_ = 0;
	}

	temphp_ = nowhp_;

}

void FlyingEye::Draw(bool charactervector,Vec2 playerpos)
{

	DrawFormatString(0, 0, 0xffffff, L"%f", pos_.x, true);
	DrawFormatString(0, 16, 0xffffff, L"%f", pos_.y, true);

	

	if (flamecount_ >= 0 && flamecount_ < 10) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[0], true, charactervector);
	}
	else if (flamecount_ >= 10 && flamecount_ < 20) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[1], true, charactervector);
	}
	else if (flamecount_ >= 20 && flamecount_ < 30) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[2], true, charactervector);
	}
	else if (flamecount_ >= 30 && flamecount_ < 40) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[3], true, charactervector);
	}
	else if (flamecount_ >= 40 && flamecount_ < 50) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[4], true, charactervector);
	}
	else if (flamecount_ >= 50 && flamecount_ < 60) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[5], true, charactervector);
	}
	else if (flamecount_ >= 60 && flamecount_ < 70) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[6], true, charactervector);
	}
	else if (flamecount_ >= 70 && flamecount_ < 80) {
		DrawRotaGraph(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 1, 0, handle_[7], true, charactervector);
	}

	DrawBox(minhitbox_.x + 640 - playerpos.x, minhitbox_.y + 370 - playerpos.y, maxhitbox_.x + 640 - playerpos.x, maxhitbox_.y + 370 - playerpos.y, 0x000000, false);

	//DrawFormatString(0, 0, 0xffffff, L"%d", tmprand_, true);

	if (damagedrawframe_ >= 0 && damagedrawframe_ != 30) {
		DrawFormatString(pos_.x + 640 - playerpos.x, pos_.y + 370 - playerpos.y, 0xffffff, L"%d", damagepoint_, true);
	}
}

void FlyingEye::PlayerMove(Vec2 playermove)
{

	pos_ -= playermove;

}

void FlyingEye::Damage(int attackpoint)
{

	nowhp_ -= attackpoint;
	

}

void FlyingEye::SetHitBox(Vec2 playerpos)
{

	minhitbox_.x = pos_.x - 20;
	minhitbox_.y = pos_.y - 10;
	maxhitbox_.x = pos_.x + 20;
	maxhitbox_.y = pos_.y + 20;

}

void FlyingEye::SetCoolDownTime()
{

	cooldowntime_ = standardcooldowntime;

}
