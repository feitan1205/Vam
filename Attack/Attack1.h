#pragma once
#include "../Vector2.h"
#include <DxLib.h>

class Attack1
{
public:

	Attack1();
	~Attack1();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage,bool charactervector,Vec2 playerpos);
	void Draw();
	void SetHitBox();

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetAttack1MinHitBox() { return minhitbox_; }
	Vec2 GetAttack1MaxHitBox() { return maxhitbox_; }
	int GetAttack1Point() { return attackpoint_ + GetRand(5); }

private:

	int attack1H_[4];
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	bool attackvector_;
	Vec2 playerpos_;
	Vec2 minhitbox_;
	Vec2 maxhitbox_;

};

