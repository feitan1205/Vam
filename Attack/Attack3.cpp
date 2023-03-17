#include "DxLib.h"
#include "Attack3.h"
#include "../DrawFunctions.h"
#include "../game.h"

constexpr int cooldowntime = 200;

Attack3::Attack3() :
	circle_(),
	flamecount_(),
	cooldowntime_(0),
	attackflag_(false),
	attackpoint_(4),
	randattackpoint_(3),
	attackvector_(),
	nowlv_(0),
	maxlv_(9),
	alpha_(200),
	add_(-2)
{
	attack3H_ = my::MyLoadGraph(L"Data/Effect/attack3/attack3.png");
}

Attack3::~Attack3()
{
}

void Attack3::Init(int cooldownpercentage)
{

	circle_ = 35;
	cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);

}

void Attack3::End()
{
}

void Attack3::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos)
{

	if (nowlv_ == 0) {
		return;
	}

	alpha_ += add_;

	if (alpha_ <= 80 || alpha_ >= 210)
	{
		add_ = -add_;
	}


	playerpos_ = playerpos;

	cooldowntime_--;

	attackflag_ = true;

	if (cooldowntime_ < 0) {
		cooldowntime_ = (float)((cooldowntime * cooldownpercentage) / 100);
		attackflag_ = false;		
	}

}

void Attack3::Draw()
{

	if (nowlv_ == 0) {
		return;
	}
	
	//DrawCircle(Game::kScreenWidth / 2, Game::kScreenHeight / 2, circle_, 0xff0000, false);
	
	
	// 画像のアルファブレンドで描画
	// ( 描画した後ブレンドモードを元に戻す )
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, circle_ / 7, 0, attack3H_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



	//DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, circle_/7, 0, attack3H_, true);

	/*DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 48, 0xffffff, L"%f", minhitbox_.y, true);*/

}

void Attack3::SetHitBox()
{
}

void Attack3::SetLv(int i)
{
	nowlv_++;
	cooldowntime_ = 0;
	if (nowlv_ == 2) {
		circle_ *= 3;
	}
	if (nowlv_ == 3) {
		attackpoint_ += 5;
		randattackpoint_ += 3;
	}
	if (nowlv_ == 4) {
		cooldowntime_ -= 30;
		circle_ *= 2;
	}
	if (nowlv_ == 5) {
		attackpoint_ += 7;
		randattackpoint_ += 3;
	}
	if (nowlv_ == 6) {
		cooldowntime_ -= 50;
	}
	if (nowlv_ == 7) {

	}
}
