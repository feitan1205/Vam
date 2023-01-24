#include "DxLib.h"
#include "Blue.h"
#include "../DrawFunctions.h"

Blue::Blue() :
	x(),
	y(),
	sizeX(),
	sizeY(),
	m_blueH_(),
	flamecount()
{
	m_blueH_ = my::MyLoadGraph(L"Data/blue/Blue.png");
	LoadDivGraph(L"Data/blue/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
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
}

void Blue::Draw()
{
	DrawGraph((1280 / 2) - (sizeX / 2), (740 / 2) - (sizeY / 2), m_blueH_, true);
}

void Blue::IdleAnimation(bool charactervector)
{
	flamecount++;

	if (flamecount == 40) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 10) {
		DrawExtendGraph((1280 / 2) - (sizeX), (740 / 2) - (sizeY), (1280 / 2) + (sizeX), (740 / 2) + (sizeY), m_idleH_[0], true);
	}
	else if (flamecount >= 10 && flamecount < 20) {
		DrawExtendGraph((1280 / 2) - (sizeX), (740 / 2) - (sizeY), (1280 / 2) + (sizeX), (740 / 2) + (sizeY), m_idleH_[1], true);
	}
	else if (flamecount >= 20 && flamecount < 30) {
		DrawExtendGraph((1280 / 2) - (sizeX), (740 / 2) - (sizeY), (1280 / 2) + (sizeX), (740 / 2) + (sizeY), m_idleH_[2], true);
	}
	else if (flamecount >= 30 && flamecount < 40) {
		DrawExtendGraph((1280 / 2) - (sizeX), (740 / 2) - (sizeY), (1280 / 2) + (sizeX), (740 / 2) + (sizeY), m_idleH_[3], true);
	}

}

void Blue::MoveAnimation(bool charactervector)
{

}

