#include "DxLib.h"
#include "Attack1.h"
#include "../DrawFunctions.h"

constexpr int cooldowntime = 100;

Attack1::Attack1():
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(10)
{
	attack1H_[0] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_01.png");
	attack1H_[1] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_02.png");
	attack1H_[2] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_03.png");
	attack1H_[3] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_04.png");
}

Attack1::~Attack1()
{
}

void Attack1::Init(int cooldownpercentage)
{

	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);

}

void Attack1::End()
{
}

void Attack1::Update(int cooldownpercentage)
{

	cooldowntime_--;

	if (cooldowntime_ < 0) {
		attackflag_ = true;
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	}

}

void Attack1::Draw(bool charactervector)
{
	flamecount_++;

	if (flamecount_ >= 20) {
		flamecount_ = 0;
		attackflag_ = false;
		return;
	}

	if (flamecount_ >= 0 && flamecount_ < 5) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[0], true, charactervector);
	}
	else if (flamecount_ >= 5 && flamecount_ < 10) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[1], true, charactervector);
	}
	else if (flamecount_ >= 10 && flamecount_ < 15) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[2], true, charactervector);
	}
	else if (flamecount_ >= 15 && flamecount_ < 20) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[3], true, charactervector);
	}
	
}

void Attack1::SetHitBox()
{

	if (flamecount_ >= 0 && flamecount_ < 5) {
	}
	else if (flamecount_ >= 5 && flamecount_ < 10) {
	}
	else if (flamecount_ >= 10 && flamecount_ < 15) {
	}
	else if (flamecount_ >= 15 && flamecount_ < 20) {
	}

}
