#include "DxLib.h"
#include "Red.h"
#include "../DrawFunctions.h"

Red::Red() :
	x(),
	y(),
	sizeX(),
	sizeY(),
	m_redH_()
{
	m_redH_ = my::MyLoadGraph(L"Data/red/Red.png");
	LoadDivGraph(L"Data/red/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
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

void Red::IdleAnimation()
{

}

void Red::MoveAnimation()
{

}
