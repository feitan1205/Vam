#include "PlayerBase.h"
#include "../Attack/Attack1.h"

PlayerBase::PlayerBase() 
{
	attack1 = new Attack1();
}

PlayerBase::~PlayerBase()
{
	delete attack1;
}

void PlayerBase::Update()
{
	attack1->Update();
}

void PlayerBase::Draw(bool charactervector)
{
	attack1->Draw(charactervector);
}
