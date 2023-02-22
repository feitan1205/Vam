#pragma once
#include "DxLib.h"
#include "AttackBase.h"

class Attack4 :
    public AttackBase
{
public:

	Attack4();
	~Attack4();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage, bool charactervector, Vec2 playerpos);
	void Draw();
	//void SetHitBox();

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetAttackMinHitBox() { return minhitbox_; }
	Vec2 GetAttackMaxHitBox() { return maxhitbox_; }
	float GetAttackHitCircle() { return 0; }
	int GetAttackPoint() { return attackpoint_ + GetRand(randattackpoint_); }
	int GetMyNumber() { return 0; }
	int GetNowLv() { return nowlv_; }
	void SetNextLv() { nowlv_++; }

private:

	int nowlv_;
	int maxlv_;
	int attack1H_[4];
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	int randattackpoint_;
	bool attackvector_;
	Vec2 playerpos_;
	Vec2 minhitbox_;
	Vec2 maxhitbox_;

};

