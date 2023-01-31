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

void PlayerBase::Init(int cooldownpercentage)
{
	attack1->Init(cooldownpercentage);
}

void PlayerBase::Update(int cooldownpercentage)
{
	attack1->Update(cooldownpercentage);
}

void PlayerBase::Draw(bool charactervector)
{
	if (attack1->GetIsAttack()) {
		attack1->Draw(charactervector);
	}
}
