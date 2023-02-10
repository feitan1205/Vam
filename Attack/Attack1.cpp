#include "DxLib.h"
#include "Attack1.h"
#include "../DrawFunctions.h"
#include "../game.h"
namespace {
	constexpr int kMaxlv = 5;
	constexpr int cooldowntime = 100;
}

Attack1::Attack1():
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(8),
	attackvector_(),
	nowlv_(1),
	maxlv_()
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
	maxlv_ = kMaxlv;

}

void Attack1::End()
{
}

void Attack1::Update(int cooldownpercentage,bool charactervector,Vec2 playerpos)
{

	playerpos_ = playerpos;

	cooldowntime_--;

	if (cooldowntime_ < 0) {
		attackflag_ = true;
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	}
	else{
		attackvector_ = charactervector;
	}

}

void Attack1::Draw()
{
	flamecount_++;

	if (flamecount_ >= 20) 
	{
		flamecount_ = 0;
		attackflag_ = false;
		return;
	}

	if (flamecount_ >= 0 && flamecount_ < 5)
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 4, 0, attack1H_[0], true, attackvector_);
		//DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);
	}
	else if (flamecount_ >= 5 && flamecount_ < 10) 
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 4, 0, attack1H_[1], true, attackvector_);
		//DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);
	}
	else if (flamecount_ >= 10 && flamecount_ < 15) 
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 4, 0, attack1H_[2], true, attackvector_);
		//DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);
	}
	else if (flamecount_ >= 15 && flamecount_ < 20)
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 4, 0, attack1H_[3], true, attackvector_);
		//DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);
	}

	/*DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 48, 0xffffff, L"%f", minhitbox_.y, true);*/

}

void Attack1::SetHitBox()
{
	int rightorleft = 1;

	if (attackvector_) {
		rightorleft = -1;
	}

	if (!attackvector_) {
		if (flamecount_ >= 0 && flamecount_ < 5)
		{
			minhitbox_.x = playerpos_.x - (rightorleft * 0);
			minhitbox_.y = playerpos_.y - 50;
			maxhitbox_.x = playerpos_.x + (rightorleft * 50);
			maxhitbox_.y = playerpos_.y - 10;
		}
		else if (flamecount_ >= 5 && flamecount_ < 10)
		{
			minhitbox_.x = playerpos_.x + (rightorleft * 20);
			minhitbox_.y = playerpos_.y - 30;
			maxhitbox_.x = playerpos_.x + (rightorleft * 60);
			maxhitbox_.y = playerpos_.y + 20;
		}
		else if (flamecount_ >= 10 && flamecount_ < 15)
		{
			minhitbox_.x = playerpos_.x - (rightorleft * 50);
			minhitbox_.y = playerpos_.y + 10;
			maxhitbox_.x = playerpos_.x + (rightorleft * 60);
			maxhitbox_.y = playerpos_.y + 45;
		}
		else if (flamecount_ >= 15 && flamecount_ < 20)
		{
			minhitbox_.x = playerpos_.x - (rightorleft * 40);
			minhitbox_.y = playerpos_.y + 0;
			maxhitbox_.x = playerpos_.x + (rightorleft * 0);
			maxhitbox_.y = playerpos_.y + 50;
		}
	}
	else if (attackvector_) {
		if (flamecount_ >= 0 && flamecount_ < 5)
		{
			maxhitbox_.x = playerpos_.x - (rightorleft * 0);
			minhitbox_.y = playerpos_.y - 50;
			minhitbox_.x = playerpos_.x + (rightorleft * 50);
			maxhitbox_.y = playerpos_.y - 10;
		}
		else if (flamecount_ >= 5 && flamecount_ < 10)
		{
			maxhitbox_.x = playerpos_.x + (rightorleft * 20);
			minhitbox_.y = playerpos_.y - 30;
			minhitbox_.x = playerpos_.x + (rightorleft * 60);
			maxhitbox_.y = playerpos_.y + 20;
		}
		else if (flamecount_ >= 10 && flamecount_ < 15)
		{
			maxhitbox_.x = playerpos_.x - (rightorleft * 50);
			minhitbox_.y = playerpos_.y + 10;
			minhitbox_.x = playerpos_.x + (rightorleft * 60);
			maxhitbox_.y = playerpos_.y + 45;
		}
		else if (flamecount_ >= 15 && flamecount_ < 20)
		{
			maxhitbox_.x = playerpos_.x - (rightorleft * 40);
			minhitbox_.y = playerpos_.y + 0;
			minhitbox_.x = playerpos_.x + (rightorleft * 0);
			maxhitbox_.y = playerpos_.y + 50;
		}
	}

}
