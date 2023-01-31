#include "DxLib.h"
#include "Blue.h"
#include "../DrawFunctions.h"

Blue::Blue() :
	posx_(),
	posy_(),
	sizeX(),
	sizeY(),
	m_blueH_(),
	flamecount(),
	cooldownpercentage_(100)
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

void Blue::Update()
{
	PlayerBase::Update(cooldownpercentage_);
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

	PlayerBase::Draw(charactervector);

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

	PlayerBase::Draw(charactervector);

}

