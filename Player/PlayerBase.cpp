#include "PlayerBase.h"
#include "../Attack//Attack1.h"
#include "../Attack//Attack2.h"
#include "../Attack//Attack3.h"

PlayerBase::PlayerBase()
{	
	attack1_ = new Attack1();
	attack2_ = new Attack2();
	attack3_ = new Attack3();
}

PlayerBase::PlayerBase(Vec2 playerpos)
{
}
	

PlayerBase::~PlayerBase()
{
	delete attack1_;
	delete attack2_;
	delete attack3_;
}

void PlayerBase::Init(int cooldownpercentage)
{
	attack1_->Init(cooldownpercentage);
	attack2_->Init(cooldownpercentage);
	attack3_->Init(cooldownpercentage);
}

void PlayerBase::Update(int cooldownpercentage, bool charactervector,Vec2 playerpos)
{
	attack1_->Update(cooldownpercentage,charactervector,playerpos);
	attack1_->SetHitBox();
	attack2_->Update(cooldownpercentage, charactervector, playerpos);
	attack2_->SetHitBox();
	attack3_->Update(cooldownpercentage, charactervector, playerpos);
	attack3_->SetHitBox();
}

void PlayerBase::Draw(bool charactervector)
{
	if (attack1_->GetIsAttack()) {
		attack1_->Draw();
	}

	if (attack2_->GetIsAttack()){
		attack2_->Draw();
	}

	attack3_->Draw();

}

int PlayerBase::GetAttack1Point()
{
	return attack1_->GetAttack1Point();
}

bool PlayerBase::GetIsAttack1()
{
	return attack1_->GetIsAttack();
}

Vec2 PlayerBase::GetAttack1MinHitBox()
{
	return attack1_->GetAttack1MinHitBox();
}

Vec2 PlayerBase::GetAttack1MaxHitBox()
{
	return attack1_->GetAttack1MaxHitBox();
}

int PlayerBase::GetAttack2Point()
{
	return attack2_->GetAttack2Point();
}

bool PlayerBase::GetIsAttack2()
{
	return attack2_->GetIsAttack();
}

Vec2 PlayerBase::GetAttack2MinHitBox()
{
	return attack2_->GetAttack2MinHitBox();
}

Vec2 PlayerBase::GetAttack2MaxHitBox()
{
	return attack2_->GetAttack2MaxHitBox();
}

int PlayerBase::GetAttack3Point()
{
	return attack3_->GetAttack3Point();
}

bool PlayerBase::GetIsAttack3()
{
	return attack3_->GetIsAttack();
}

Vec2 PlayerBase::GetAttack3MinHitBox()
{
	return attack3_->GetAttack3MinHitBox();
}

Vec2 PlayerBase::GetAttack3MaxHitBox()
{
	return attack3_->GetAttack3MaxHitBox();
}
