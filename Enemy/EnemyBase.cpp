#include "EnemyBase.h"
#include "DxLib.h"

EnemyBase::EnemyBase()
{
	LoadDivGraph(L"Data/Enemy/FlyingEye.png", 8, 8, 1, 150, 63, FlyinteyeH_);
}

EnemyBase::~EnemyBase()
{
	for (int i = 0; i < 8; i++) {
		DeleteGraph(FlyinteyeH_[i]);
	}
}