#pragma once
#include "../Vector2.h"

class AttackBase
{
public:

	AttackBase();
	~AttackBase();

	virtual void Init(int cooldownpercentage) = 0;
	virtual void End() = 0;
	virtual void Update(int cooldownpercentage, bool charactervector, Vec2 playerpos) = 0;
	virtual void Draw() = 0;
	virtual void SetHitBox() = 0;

	virtual bool GetIsAttack() = 0;
	virtual Vec2 GetAttackMinHitBox() = 0;
	virtual Vec2 GetAttackMaxHitBox() = 0;
	virtual float GetAttackHitCircle() = 0;
	virtual int GetAttackPoint() = 0;
	virtual int GetMyNumber() = 0;

private:

};

