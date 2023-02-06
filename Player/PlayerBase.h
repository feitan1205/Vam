#pragma once
#include "../Vector2.h"

class Attack1;
class Attack2;
class Attack3;

class PlayerBase
{
public:

	PlayerBase();
	PlayerBase(Vec2 playerpos);
	~PlayerBase();

	virtual void Init() = 0;
	virtual void Init(int cooldownpercentage);
	virtual void End() = 0;
	virtual void Update(Vec2 playerpos, bool charactervector) = 0;
	virtual void Update(int cooldownpercentage, bool charactervector,Vec2 playerpos);
	virtual void Draw(bool charactervector);
	virtual void IdleAnimation(bool charactervector) = 0;
	virtual void MoveAnimation(bool charactervector) = 0;
	virtual void SetHitBox(Vec2 playerpos) = 0;
	virtual void Damage(int enemyattackpoint) = 0;

	virtual Vec2 GetMinHitBox() = 0;
	virtual Vec2 GetMaxHitBox() = 0;

	int GetAttack1Point();
	bool GetIsAttack1();
	Vec2 GetAttack1MinHitBox();
	Vec2 GetAttack1MaxHitBox();
	int GetAttack2Point();
	bool GetIsAttack2();
	Vec2 GetAttack2MinHitBox();
	Vec2 GetAttack2MaxHitBox();
	int GetAttack3Point();
	bool GetIsAttack3();
	Vec2 GetAttack3MinHitBox();
	Vec2 GetAttack3MaxHitBox();

protected:

	Vec2 pos_;
	Attack1* attack1_;
	Attack2* attack2_;
	Attack3* attack3_;

};

