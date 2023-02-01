#include "DxLib.h"
#include "Red.h"
#include "../DrawFunctions.h"

Red::Red(Vec2 playerpos) :
	sizeX_(),
	sizeY_(),
	m_redH_(),
	flamecount_(),
	cooldownpercentage_(80)
{
	m_redH_ = my::MyLoadGraph(L"Data/red/Red.png");
	LoadDivGraph(L"Data/red/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
	LoadDivGraph(L"Data/red/Move.png", 6, 6, 1, 24, 24, m_moveH_);
	GetGraphSize(m_redH_, &sizeX_, &sizeY_);
}

Red::~Red()
{
	DeleteGraph(m_redH_);
	for (int i = 0; i < 4; i++) {
		DeleteGraph(m_idleH_[i]);
	}
}

void Red::Init()
{
}

void Red::End()
{
}

void Red::Update(Vec2 playerpos, bool charactervector)
{
	PlayerBase::Update(cooldownpercentage_, charactervector,playerpos);
}

void Red::Draw()
{
	DrawGraph((1280 / 2) - (sizeX_ / 2), (740 / 2) - (sizeY_ / 2), m_redH_, true);
}

void Red::IdleAnimation(bool charactervector)
{
	flamecount_++;

	if (flamecount_ >= 40) {
		flamecount_ = 0;
	}

	if (flamecount_ >= 0 && flamecount_ < 10) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[0], true, charactervector);
	}
	else if (flamecount_ >= 10 && flamecount_ < 20) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[1], true, charactervector);
	}
	else if (flamecount_ >= 20 && flamecount_ < 30) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[2], true, charactervector);
	}
	else if (flamecount_ >= 30 && flamecount_ < 40) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_idleH_[3], true, charactervector);
	}

	PlayerBase::Draw(charactervector);

}

void Red::MoveAnimation(bool charactervector)
{
	flamecount_++;

	if (flamecount_ >= 60) {
		flamecount_ = 0;
	}

	if (flamecount_ >= 0 && flamecount_ < 10) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[0], true, charactervector);
	}
	else if (flamecount_ >= 10 && flamecount_ < 20) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[1], true, charactervector);
	}
	else if (flamecount_ >= 20 && flamecount_ < 30) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[2], true, charactervector);
	}
	else if (flamecount_ >= 30 && flamecount_ < 40) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[3], true, charactervector);
	}
	else if (flamecount_ >= 40 && flamecount_ < 50) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[4], true, charactervector);
	}
	else if (flamecount_ >= 50 && flamecount_ < 60) {
		DrawRotaGraph((1280 / 2), (740 / 2), 2, 0, m_moveH_[5], true, charactervector);
	}

	PlayerBase::Draw(charactervector);

}

void Red::SetHitBox(Vec2 playerpos)
{
}
