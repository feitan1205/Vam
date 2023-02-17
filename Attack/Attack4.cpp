#include "DxLib.h"
#include "Attack4.h"
#include "../DrawFunctions.h"
#include "../game.h"
namespace {
	constexpr int kMaxlv = 5;
	constexpr int cooldowntime = 200;
}

Attack4::Attack4() :
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(6),
	randattackpoint_(3),
	attackvector_(),
	nowlv_(0),
	maxlv_()
{
	attack1H_[0] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_01.png");
	attack1H_[1] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_02.png");
	attack1H_[2] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_03.png");
	attack1H_[3] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_04.png");
}

Attack4::~Attack4()
{
}

void Attack4::Init(int cooldownpercentage)
{

	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	maxlv_ = kMaxlv;

}

void Attack4::End()
{
}

void Attack4::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos)
{

	if (nowlv_ == 0) {
		return;
	}

	playerpos_ = playerpos;

	cooldowntime_--;

	if (cooldowntime_ < 0) {
		attackflag_ = true;
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
		attackpoint_ = 6;
		randattackpoint_ = 3;
		if (nowlv_ >= 2) {
			cooldowntime_ -= 40;
		}
		if (nowlv_ >= 3) {
			attackpoint_ += 3;
			randattackpoint_ += 2;
		}
		if (nowlv_ >= 4) {
			cooldowntime_ -= 40;
		}
		if (nowlv_ >= 5) {
			cooldowntime_ -= 40;
		}
		if (nowlv_ >= 6) {
			attackpoint_ += 10;
			randattackpoint_ += 8;
		}
		if (nowlv_ >= 7) {
			cooldowntime_ -= 40;
		}
		if (nowlv_ >= 8) {
			attackpoint_ += 15;
			randattackpoint_ += 5;
		}
	}
	else {
		attackvector_ = charactervector;
	}

}

void Attack4::Draw()
{

	if (nowlv_ == 0) {
		return;
	}

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