#include "DxLib.h"
#include "Attack4.h"
#include "../DrawFunctions.h"
#include "../game.h"
namespace {
	constexpr int kMaxlv = 9;
	constexpr int cooldowntime = 100;
}

Attack4::Attack4() :
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(6),
	randattackpoint_(3),
	attackvector_(),
	nowlv_(0),
	maxlv_(),
	shotcount_(),
	shotmaxcount_(),
	circle_(16)
{
	attack4H_ = my::MyLoadGraph(L"Data/Effect/attack4/bullet.png");	
}

Attack4::~Attack4()
{
}

void Attack4::Init(int cooldownpercentage)
{

	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
	maxlv_ = kMaxlv;
	shotspacecount_ = 6;
	shotmaxcount_ = 3;
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

	for (auto& shot : shots_) {
		shot->Update();
	}

	if (shotcount_ >= shotmaxcount_) {
		attackflag_ = false;
		shotcount_ = 0;
	}

	if (!attackflag_) {
		cooldowntime_--;
	}

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

	if (attackflag_) {
		shotspacecount_--;
	}
	if (attackflag_ && shotspacecount_ < 0) {

		shots_.push_back(std::make_shared<Shot>(playerpos_));
		shots_.back()->SetPos(enempos_);

		shotspacecount_ = 6;

		shotcount_++;
	}

}

void Attack4::Draw()
{

	for (auto& shot : shots_) {
		DrawRotaGraph((Game::kScreenWidth / 2) + shot->GetPos().x, (Game::kScreenHeight / 2) + shot->GetPos().y, 1 + ((static_cast<float>(1) / 100) * static_cast<float>(attackscalepercentage_)), 0, attack4H_, true);
	}
}

void Attack4::SetLv(int i)
{
}

Attack4::Shot::~Shot()
{
}

void Attack4::Shot::Update() {

	pos_ += vector_ * speed_;

}

void Attack4::Shot::SetPos(Vec2 enempos) {

	pos_ = playerpos_;
	vector_ = playerpos_ - enempos;

	vector_ = vector_.normalize();

}
