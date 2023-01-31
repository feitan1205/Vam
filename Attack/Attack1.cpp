#include "DxLib.h"
#include "Attack1.h"
#include "../DrawFunctions.h"

Attack1::Attack1():
	flamecount()
{
	attack1H_[0] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_01.png");
	attack1H_[1] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_02.png");
	attack1H_[2] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_03.png");
	attack1H_[3] = my::MyLoadGraph(L"Data/Effect/attack1/FE1002_04.png");
}

Attack1::~Attack1()
{
}

void Attack1::Init()
{
}

void Attack1::End()
{
}

void Attack1::Update()
{
}

void Attack1::Draw(bool charactervector)
{
	flamecount++;

	if (flamecount >= 40) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 5) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[0], true, charactervector);
	}
	else if (flamecount >= 5 && flamecount < 10) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[1], true, charactervector);
	}
	else if (flamecount >= 10 && flamecount < 15) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[2], true, charactervector);
	}
	else if (flamecount >= 15 && flamecount < 20) {
		DrawRotaGraph(640, 370, 4, 0, attack1H_[3], true, charactervector);
	}
	
}
