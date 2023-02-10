#include "PlayerBase.h"
#include "../Attack//AttackBase.h"
#include "../Attack//Attack1.h"
#include "../Attack//Attack2.h"
#include "../Attack//Attack3.h"

PlayerBase::PlayerBase()
{	
	
}

PlayerBase::PlayerBase(Vec2 playerpos)
{
}
	

PlayerBase::~PlayerBase()
{
	for (auto& attack : attack_) {
		delete attack;
	}
	attack_.clear();
}

void PlayerBase::Init(int cooldownpercentage)
{

	attack_.push_back(new Attack1());
	//attack_.push_back(new Attack2());
	//attack_.push_back(new Attack3());

	for (auto& attack : attack_) {
		attack->Init(cooldownpercentage);
	}

	
}

void PlayerBase::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos)
{

	for (auto& attack : attack_) {
		attack->Update(cooldownpercentage, charactervector, playerpos);
		attack->SetHitBox();
	}

}

void PlayerBase::Draw(bool charactervector)
{
	for (auto& attack : attack_) {
		if (attack->GetIsAttack()) {
			attack->Draw();
		}
	}
	
}

int PlayerBase::GetAttackPoint(int attacknum)
{
	
	return attack_[attacknum]->GetAttackPoint();
}

bool PlayerBase::GetIsAttack(int attacknum)
{
	return attack_[attacknum]->GetIsAttack();
}

Vec2 PlayerBase::GetAttackMinHitBox(int attacknum)
{
	return attack_[attacknum]->GetAttackMinHitBox();
}

Vec2 PlayerBase::GetAttackMaxHitBox(int attacknum)
{
	return attack_[attacknum]->GetAttackMaxHitBox();
}

float PlayerBase::GetAttackHitCircle(int attacknum)
{
	return attack_[attacknum]->GetAttackHitCircle();
}

int PlayerBase::GetAttackingNumber(int attacknum) {
	return attack_[attacknum]->GetMyNumber();
}

int PlayerBase::GetWeaponLv(int weaponnum)
{
	return attack_[weaponnum]->GetNowLv();
}

void PlayerBase::SetLv(int i)
{
	attack_[i]->SetNextLv();
}
