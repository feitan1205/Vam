#include "PlayerBase.h"
#include "../Attack/Attack1.h"

PlayerBase::PlayerBase() 
{	
	attack1_ = new Attack1();
}

PlayerBase::PlayerBase(Vec2 playerpos)
{
}
	

PlayerBase::~PlayerBase()
{
	delete attack1_;
}

void PlayerBase::Init(int cooldownpercentage)
{
	attack1_->Init(cooldownpercentage);
}

void PlayerBase::Update(int cooldownpercentage, bool charactervector)
{
	attack1_->Update(cooldownpercentage,charactervector);
}

void PlayerBase::Draw(bool charactervector)
{
	if (attack1_->GetIsAttack()) {
		attack1_->Draw();
	}
}
