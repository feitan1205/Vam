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

void PlayerBase::Update(int cooldownpercentage, bool charactervector,Vec2 playerpos)
{
	attack1_->Update(cooldownpercentage,charactervector,playerpos);
	attack1_->SetHitBox();
}

void PlayerBase::Draw(bool charactervector)
{
	if (attack1_->GetIsAttack()) {
		attack1_->Draw();
	}
}

int PlayerBase::GetAttackPoint()
{
	return attack1_->GetAttack1Point();
}

bool PlayerBase::GetIsAttack1()
{
	return attack1_->GetIsAttack();
}

Vec2 PlayerBase::GetAttackMinHitBox()
{
	return attack1_->GetAttack1MinHitBox();
}

Vec2 PlayerBase::GetAttackMaxHitBox()
{
	return attack1_->GetAttack1MaxHitBox();;
}
