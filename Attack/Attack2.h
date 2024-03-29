#pragma once
#include "../Vector2.h"
#include <DxLib.h>
#include "AttackBase.h"

class Attack2 :
	public AttackBase
{
public:

	Attack2();
	~Attack2();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage, bool charactervector, Vec2 playerpos);
	void Draw();
	void SetHitBox();
	int GetSize() { return 0; }

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetPos(int i) { return Vec2(0, 0); }
	Vec2 GetAttackMinHitBox() { return minhitbox_; }
	Vec2 GetAttackMaxHitBox() { return maxhitbox_; }
	float GetAttackHitCircle() { return 0; }
	int GetAttackPoint() { return attackpoint_ + GetRand(randattackpoint_); }
	int GetMyNumber() { return 1; }
	int GetNowLv() { return nowlv_; }
	int GetMaxLv() { return maxlv_; }
	void SetLv(int i) { nowlv_ = i; }
	void SetEnemyPos(Vec2 enempos) {};
	void SoundStop();

private:

	int nowlv_;
	int maxlv_;
	int attack2H_[3];
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	int randattackpoint_;
	bool attackvector_;
	double attackscale_;
	int attackingtime_;
	int animationcount_;
	Vec2 playerpos_;
	Vec2 minhitbox_;
	Vec2 maxhitbox_;
	Vec2 graphsize_;

};

