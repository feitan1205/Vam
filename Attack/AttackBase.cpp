#include "AttackBase.h"
#include "DxLib.h"

AttackBase::AttackBase()
{
	attack2sound_ = LoadSoundMem(L"Data//Sound//murasaki.wav");
}

AttackBase::~AttackBase()
{
}
