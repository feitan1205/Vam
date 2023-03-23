#include "PlayerBase.h"
#include "../Attack//AttackBase.h"
#include "../Attack//Attack1.h"
#include "../Attack//Attack2.h"
#include "../Attack//Attack3.h"
#include "../Attack//Attack4.h"

PlayerBase::PlayerBase()
{	
	
	attackscalepercentage_ = 0;

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
	attack_.push_back(new Attack2());
	attack_.push_back(new Attack3());
	attack_.push_back(new Attack4());

	for (auto& attack : attack_) {
		attack->Init(cooldownpercentage);
	}

	for (int i = 0; i < PlayerStatus::kindmax; i++) {
		item[i].level = 0;

		if (i < 3) {
			item[i].maxlevel = attack_[i]->GetMaxLv();
		}
		else {
			item[i].maxlevel = 5;
		}
	}

	
}

void PlayerBase::Update(int cooldownpercentage, bool charactervector, Vec2 playerpos,Vec2 enemypos)
{

	for (auto& attack : attack_) {
		attack->SetEnemyPos(enemypos);
		attack->Update(cooldownpercentage, charactervector, playerpos);
		attack->SetHitBox();
		attack->SetScale(attackscalepercentage_);
	}

}

void PlayerBase::Draw(bool charactervector)
{
	for (auto& attack : attack_) {
		//if (attack->GetIsAttack()) 
		{
			attack->Draw();
		}
	}
	
}

int PlayerBase::GetSize(int attacknum)
{
	return attack_[attacknum]->GetSize();
}

Vec2 PlayerBase::GetBulletPos(int attacknum,int j)
{
	return attack_[attacknum]->GetPos(j);
}

int PlayerBase::GetAttackPoint(int attacknum)
{
	
	return (attack_[attacknum]->GetAttackPoint() + ((attack_[attacknum]->GetAttackPoint() / 100) * attackpointpercentage_));
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
	return item[weaponnum].level;
}

int PlayerBase::GetWeaponMaxLv(int weaponnum)
{
	return item[weaponnum].maxlevel;
}

void PlayerBase::SetLv(int i)
{
	switch (i)
	{
	case ao:item[ao].level++; attack_[i]->SetLv(item[i].level); break;
	case murasaki:item[murasaki].level++; attack_[i]->SetLv(item[i].level); break;
	case siro:item[siro].level++; attack_[i]->SetLv(item[i].level); break;
	//case bullet:item[bullet].level++; attack_[i]->SetLv(item[i].level); break;
	case boots:item[boots].level++; movespeedpercentage_ += 10; break;
	case book:item[book].level++; cooltimepercentage_ += 10; break;
	case candle:item[candle].level++; attackscalepercentage_ += 20; break;
	case spinach:item[spinach].level++; attackpointpercentage_ += 10; break;
	case crown:item[crown].level++; exppointpercentage_ += 20; break;
	case orb:item[orb].level++; circlescale_++; break;
	default:
		break;
	}

	//attack_[i]->SetLv(item[i].level);
}

void PlayerBase::CreatAttack(int creatweapon) {

	if (creatweapon == 0) {
		attack_.push_back(new Attack1());
	}
	else if(creatweapon == 1) {
		attack_.push_back(new Attack2());
	}
	else if (creatweapon == 2) {
		attack_.push_back(new Attack3());
	}
}

void PlayerBase::AttackSoundStop()
{
	for (auto& at : attack_) {
		at->SoundStop();
	}
}
