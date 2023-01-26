#include "DxLib.h"
#include "Red.h"
#include "../DrawFunctions.h"

Red::Red() :
	x(),
	y(),
	sizeX(),
	sizeY(),
	m_redH_(),
	flamecount()
{
	m_redH_ = my::MyLoadGraph(L"Data/red/Red.png");
	LoadDivGraph(L"Data/red/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
	LoadDivGraph(L"Data/red/Move.png", 6, 6, 1, 24, 24, m_moveH_);
	GetGraphSize(m_redH_, &sizeX, &sizeY);
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

void Red::Update()
{
}

void Red::Draw()
{
	DrawGraph((1280 / 2) - (sizeX / 2), (740 / 2) - (sizeY / 2), m_redH_, true);
}

void Red::IdleAnimation(bool charactervector)
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
}

void Red::MoveAnimation(bool charactervector)
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
}
