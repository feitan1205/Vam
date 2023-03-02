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
	virtual int GetSize() = 0;

	virtual bool GetIsAttack() = 0;
	virtual Vec2 GetPos(int i) = 0;
	virtual Vec2 GetAttackMinHitBox() = 0;
	virtual Vec2 GetAttackMaxHitBox() = 0;
	virtual float GetAttackHitCircle() = 0;
	virtual int GetAttackPoint() = 0;
	virtual int GetMyNumber() = 0;
	virtual int GetNowLv() = 0;
	virtual int GetMaxLv() = 0;
	virtual void SetLv(int i) = 0;
	virtual void SetEnemyPos(Vec2 enempos) = 0;

	void SetScale(int attackscalepercentage) { attackscalepercentage_ = attackscalepercentage; }

private:

protected:

	int attackscalepercentage_;

};

