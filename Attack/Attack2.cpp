#include "DxLib.h"
#include "Attack2.h"
#include "../DrawFunctions.h"

constexpr int cooldowntime = 100;

Attack2::Attack2() :
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(1),
	attackvector_(),
	attackscale_(),
	attackingtime_(100),
	animationcount_()
{
	attack2H_[0] = my::MyLoadGraph(L"Data/Effect/attack2/BFX003_01.png");
	attack2H_[1] = my::MyLoadGraph(L"Data/Effect/attack2/BFX003_02.png");
	attack2H_[2] = my::MyLoadGraph(L"Data/Effect/attack2/BFX003_03.png");
	GetGraphSizeF(attack2H_[0], &graphsize_.x, &graphsize_.y);
}

Attack2::~Attack2()
{
}

void Attack2::Init(int cooldownpercentage)
{

	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);

}

void Attack2::End()
{
}

void Attack2::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos)
{

	playerpos_ = playerpos;

	

	if (cooldowntime_ <= 0) {
		attackflag_ = true;
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	}

	if (!attackflag_) {
		cooldowntime_--;
		attackvector_ = charactervector;		
	}

	if (attackflag_) {
		flamecount_++;
		animationcount_++;
		if (flamecount_ <= 20) {
			attackscale_ += 0.1;
		}
		if (flamecount_ >= 80 && flamecount_ < 100) {
			attackscale_ -= 0.1;
		}

		if (animationcount_ >= 15) {
			animationcount_ = 0;
		}
	}

	if (flamecount_ >= attackingtime_)
	{
		flamecount_ = 0;
		attackflag_ = false;
		return;
	}

}

void Attack2::Draw()
{
	
	if (animationcount_ >= 0 && animationcount_ < 5)
	{
		DrawRotaGraph(640, 370 - 30, attackscale_, 0, attack2H_[0], true, attackvector_);
	}
	else if (animationcount_ >= 5 && animationcount_ < 10)
	{
		DrawRotaGraph(640, 370 - 30, attackscale_, 0, attack2H_[1], true, attackvector_);
	}
	else if (animationcount_ >= 10 && animationcount_ < 15)
	{
		DrawRotaGraph(640, 370 - 30, attackscale_, 0, attack2H_[2], true, attackvector_);
	}

	DrawBox(minhitbox_.x + (1280 / 2) - playerpos_.x, minhitbox_.y + (740 / 2) - playerpos_.y, maxhitbox_.x + (1280 / 2) - playerpos_.x, maxhitbox_.y + (740 / 2) - playerpos_.y, 0xff0000, false);

	DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 48, 0xffffff, L"%f", minhitbox_.y, true); 

}

void Attack2::SetHitBox()
{
	
	minhitbox_.x = playerpos_.x - ((graphsize_.x * attackscale_) / 2);
	minhitbox_.y = playerpos_.y - 30 - (((graphsize_.y - 8.0f) * attackscale_) / 2);
	maxhitbox_.x = playerpos_.x + ((graphsize_.x * attackscale_) / 2);
	maxhitbox_.y = playerpos_.y - 30 + (((graphsize_.y - 8.0f) * attackscale_) / 2);

}
