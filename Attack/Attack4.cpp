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
	shotspacecount_ = 32;
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
		shots_.push_back(std::make_shared<Shot>(playerpos_));
		shots_.back()->SetPos(enempos_);
		shotcount_++;
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

		shotspacecount_ = 32;

		shotcount_++;
	}

	for (auto& shot : shots_) {
		if ((Game::kScreenWidth / 2) + shot->GetPos().x - playerpos_.x < 0) {
			shot->Delete();
		}
		if ((Game::kScreenWidth / 2) + shot->GetPos().x - playerpos_.x > Game::kScreenWidth) {
			shot->Delete();
		}
		if ((Game::kScreenHeight / 2) + shot->GetPos().y - playerpos_.y < 0) {
			shot->Delete();
		}
		if ((Game::kScreenHeight / 2) + shot->GetPos().y - playerpos_.y > Game::kScreenHeight) {
			shot->Delete();
		}
	}

	auto rmIt = std::remove_if(shots_.begin(), shots_.end(),
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->GetIsEnabled();
		});

	shots_.erase(rmIt, shots_.end());

}

void Attack4::Draw()
{

	for (auto& shot : shots_) {
		DrawRotaGraph((Game::kScreenWidth / 2) + shot->GetPos().x - playerpos_.x, (Game::kScreenHeight / 2) + shot->GetPos().y - playerpos_.y, 1 + ((static_cast<float>(1) / 100) * static_cast<float>(attackscalepercentage_)), 0, attack4H_, true);
		DrawCircle((Game::kScreenWidth / 2) + shot->GetPos().x - playerpos_.x, (Game::kScreenHeight / 2) + shot->GetPos().y - playerpos_.y, 4, 0xff0000,true);
	}

}

Vec2 Attack4::GetPos(int i)
{
	int count = 0;

	for(auto& shot:shots_){
		if (count == i) {
			return shot->GetPos();
		}
		count++;
	}
}

void Attack4::SetLv(int i)
{
	nowlv_ = i;
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

	vector_ *= -1;

}
