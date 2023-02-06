#pragma once
#include "../Vector2.h"
#include <DxLib.h>

class Attack3
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
	Vec2 GetAttack3MinHitBox() { return minhitbox_; }
	Vec2 GetAttack3MaxHitBox() { return maxhitbox_; }
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
