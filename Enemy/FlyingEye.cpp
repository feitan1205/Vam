#include "DxLib.h"
#include "FlyingEye.h"
#include "../DrawFunctions.h"

FlyingEye::FlyingEye():
	flamecount()
{
	LoadDivGraph(L"Data/Enemy/FlyingEye.png", 8, 8, 1, 150, 63, handle_);
}

FlyingEye::~FlyingEye()
{
}

void FlyingEye::Init(Vec2 playerpos)
{
	pos_.x = playerpos.x + (GetRand(100) + 640);
	pos_.y = playerpos.y + (GetRand(100) + 370);

	int tmprand = GetRand(3);

	if (tmprand == 1) {
		pos_.x *= -1;
	}
	else if (tmprand == 2) {
		pos_.y *= -1;
	}
	else if (tmprand == 3) {
		pos_.x *= -1;
		pos_.y *= -1;
	}
}

void FlyingEye::End()
{
}

void FlyingEye::Update(Vec2 playerpos)
{
	if (playerpos.x > pos_.x) {
		pos_.x++;
	}
	if (playerpos.x < pos_.x) {
		pos_.x--;
	}
	if (playerpos.y < pos_.y) {
		pos_.y--;
	}
	if (playerpos.y > pos_.y) {
		pos_.y++;
	}
}

void FlyingEye::Draw(bool charactervector)
{

	flamecount++;

	if (flamecount >= 80) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 10) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[0], true, charactervector);
	}
	else if (flamecount >= 10 && flamecount < 20) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[1], true, charactervector);
	}
	else if (flamecount >= 20 && flamecount < 30) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[2], true, charactervector);
	}
	else if (flamecount >= 30 && flamecount < 40) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[3], true, charactervector);
	}
	else if (flamecount >= 40 && flamecount < 50) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[4], true, charactervector);
	}
	else if (flamecount >= 50 && flamecount < 60) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[5], true, charactervector);
	}
	else if (flamecount >= 60 && flamecount < 70) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[6], true, charactervector);
	}
	else if (flamecount >= 70 && flamecount < 80) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, handle_[7], true, charactervector);
	}

}
