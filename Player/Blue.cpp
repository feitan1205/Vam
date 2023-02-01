#include "DxLib.h"
#include "Blue.h"
#include "../DrawFunctions.h"

Blue::Blue(Vec2 playerpos) :
	sizeX(),
	sizeY(),
	m_blueH_(),
	flamecount(),
	cooldownpercentage_(100),
	playerpos_(playerpos),
	maxhp_(100),
	nowhp_(100),
	hppercentage_()
{
	m_blueH_ = my::MyLoadGraph(L"Data/blue/Blue.png");
	LoadDivGraph(L"Data/blue/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
	LoadDivGraph(L"Data/blue/Move.png", 6, 6, 1, 24, 24, m_moveH_);
	//LoadGraph(L"Data/blue/Blue.png", m_blueH_);
	GetGraphSize(m_blueH_, &sizeX, &sizeY);
}

Blue::~Blue()
{
	DeleteGraph(m_blueH_);
	for (int i = 0; i < 4; i++) {
		DeleteGraph(m_idleH_[i]);
	}
}

void Blue::Init()
{
}

void Blue::End()
{
}

void Blue::Update(Vec2 playerpos)
{
	PlayerBase::Update(cooldownpercentage_);

	hppercentage_ = static_cast <float>(nowhp_) / static_cast <float>(maxhp_);

	playerpos_ = playerpos;

}

void Blue::Draw()
{
	DrawGraph((1280 / 2) - (sizeX / 2), (740 / 2) - (sizeY / 2), m_blueH_, true);
}

void Blue::IdleAnimation(bool charactervector)
{
	flamecount++;

	if (flamecount >= 40) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 10) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[0], true, charactervector);
	}
	else if (flamecount >= 10 && flamecount < 20) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[1], true, charactervector);
	}
	else if (flamecount >= 20 && flamecount < 30) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[2], true, charactervector);
	}
	else if (flamecount >= 30 && flamecount < 40) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[3], true, charactervector);
	}

	DrawBox((1280 / 2) - 20 - 1, (740 / 2) + 27 - 1, (1280 / 2) - 20 + (40 * 1) + 1, (740 / 2) + 35 + 1, 0x000000, true);
	DrawBox((1280 / 2) - 20 , (740 / 2) + 27 , (1280 / 2) - 20 + (40 * hppercentage_), (740 / 2) + 35,0xff0000, true);

	DrawBox(minhitbox_.x + (1280 / 2) - playerpos_.x, minhitbox_.y + (740 / 2) - playerpos_.y, maxhitbox_.x + (1280 / 2) - playerpos_.x, maxhitbox_.y + (740 / 2) - playerpos_.y, 0xff0000, false);

	PlayerBase::Draw(charactervector);
	
	DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 64, 0xffffff, L"%f", minhitbox_.y, true);
}

void Blue::MoveAnimation(bool charactervector)
{
	flamecount++;

	if (flamecount >= 60) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 10) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[0], true, charactervector);
	}
	else if (flamecount >= 10 && flamecount < 20) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[1], true, charactervector);
	}
	else if (flamecount >= 20 && flamecount < 30) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[2], true, charactervector);
	}
	else if (flamecount >= 30 && flamecount < 40) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[3], true, charactervector);
	}
	else if (flamecount >= 40 && flamecount < 50) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[4], true, charactervector);
	}
	else if (flamecount >= 50 && flamecount < 60) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[5], true, charactervector);
	}

	DrawBox((1280 / 2) - 20 - 1, (740 / 2) + 27 - 1, (1280 / 2) - 20 + (40 * 1) + 1, (740 / 2) + 35 + 1, 0x000000, true);
	DrawBox((1280 / 2) - 20, (740 / 2) + 27, (1280 / 2) - 20 + (40 * hppercentage_), (740 / 2) + 35, 0xff0000, true);

	DrawBox(minhitbox_.x + (1280 / 2) - playerpos_.x, minhitbox_.y + (740 / 2) - playerpos_.y, maxhitbox_.x + (1280 / 2) - playerpos_.x, maxhitbox_.y + (740 / 2) - playerpos_.y, 0xff0000, false);

	PlayerBase::Draw(charactervector);

	DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 64, 0xffffff, L"%f", minhitbox_.y, true);

}

void Blue::SetHitBox(Vec2 playerpos)
{

	minhitbox_.x = playerpos.x - 10;
	minhitbox_.y = playerpos.y - 10;
	maxhitbox_.x = playerpos.x + 10;
	maxhitbox_.y = playerpos.y + 10;

}

void Blue::Damage(int enemyattackpoint)
{

	nowhp_ -= enemyattackpoint;

}

