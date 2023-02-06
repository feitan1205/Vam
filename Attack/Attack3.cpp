#include "DxLib.h"
#include "Attack3.h"
#include "../DrawFunctions.h"

constexpr int cooldowntime = 100;

Attack3::Attack3() :
	circle_(),
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(8),
	attackvector_()
{
	
}

Attack3::~Attack3()
{
}

void Attack3::Init(int cooldownpercentage)
{

	circle_ = 40;
	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);

}

void Attack3::End()
{
}

void Attack3::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos)
{

	playerpos_ = playerpos;

	cooldowntime_--;

	if (attackflag_) {
		attackflag_ = false;
	}

	if (cooldowntime_ < 0) {
		attackflag_ = true;
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	}

	if (!attackflag_) {
		attackvector_ = charactervector;
	}

}

void Attack3::Draw()
{
	
	DrawCircle(640, 370, circle_, 0xff0000, false);
	
	/*DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 48, 0xffffff, L"%f", minhitbox_.y, true);*/

}

void Attack3::SetHitBox()
{	
}