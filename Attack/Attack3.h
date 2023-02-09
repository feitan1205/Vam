#pragma once
#include "../Vector2.h"
#include <DxLib.h>
#include "AttackBase.h"

class Attack3:
	public AttackBase
{
public:

	Attack3();
	~Attack3();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage, bool charactervector, Vec2 playerpos);
	void Draw();
	void SetHitBox();

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetAttackMinHitBox() { return { 0,0 }; }
	Vec2 GetAttackMaxHitBox() { return { 0,0 }; }
	float GetAttackHitCircle() { return circle_; }
	int GetAttackPoint() { return attackpoint_ + GetRand(5); }
	int GetMyNumber() { return 2; }

private:

	float circle_;
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	bool attackvector_;
	Vec2 playerpos_;
	Vec2 minhitbox_;
	Vec2 maxhitbox_;

};
