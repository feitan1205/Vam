#include "DxLib.h"
#include "FlyingEye.h"
#include "../DrawFunctions.h"

constexpr float kspeed = 0.5;

FlyingEye::FlyingEye():
	flamecount_()
{
	LoadDivGraph(L"Data/Enemy/FlyingEye.png", 8, 8, 1, 150, 63, handle_);
}

FlyingEye::~FlyingEye()
{
}

void FlyingEye::Init(Vec2 playerpos)
{

	int tempx;
	int tempy;

	while (1) {

		tempx = (GetRand(700));
		tempy = (GetRand(450));

		if (tempx > 680) break;
		if (tempy > 400) break;
	}

	int tmprand = GetRand(3);

	if (tmprand == 1) {
		tempx *= -1;
	}
	else if (tmprand == 2) {
		tempy *= -1;
	}
	else if (tmprand == 3) {
		tempx *= -1;
		tempy *= -1;
	}

	pos_.x = playerpos.x + tempx;
	pos_.y = playerpos.y + tempy;


}

void FlyingEye::End()
{
}

void FlyingEye::Update(Vec2 playerpos)
{

	vector_ = playerpos - pos_;

	vector_ = vector_.normalize();

	pos_ += (vector_ * kspeed);

}

void FlyingEye::Draw(bool charactervector,Vec2 playerpos)
{

	DrawFormatString(0, 0, 0xffffff, L"%f", pos_.x, true);
	DrawFormatString(0, 16, 0xffffff, L"%f", pos_.y, true);

	flamecount_++;

	if (flamecount_ >= 80) {
		flamecount_ = 0;
	}

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

	DrawBox(minhitbox_.x + 640, minhitbox_.y + 370, maxhitbox_.x + 650, maxhitbox_.y + 380, 0x000000, false);

}

void FlyingEye::PlayerMove(Vec2 playermove)
{

	pos_ -= playermove;

}

void FlyingEye::SetHitBox(Vec2 playerpos)
{

	minhitbox_.x = pos_.x - playerpos.x - 10;
	minhitbox_.y = pos_.y - playerpos.y - 10;
	maxhitbox_.x = pos_.x - playerpos.x + 10;
	maxhitbox_.y = pos_.y - playerpos.y + 10;

}
