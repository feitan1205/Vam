#pragma once
#include "../Vector2.h"
#include <DxLib.h>

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
	float GetAttack3HitCircle() { return circle_; }
	int GetAttack3Point() { return attackpoint_ + GetRand(5); }

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
