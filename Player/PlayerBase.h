#pragma once
#include "../Vector2.h"
#include <vector>

class AttackBase;

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

	virtual void GetExp(int exppoint) = 0;

	int GetAttackPoint(int attacknum);
	bool GetIsAttack(int attacknum);
	Vec2 GetAttackMinHitBox(int attacknum);
	Vec2 GetAttackMaxHitBox(int attacknum);
	float GetAttackHitCircle(int attacknum);

	int GetAttackKindNum() { return attack_.size(); }
	int GetAttackingNumber(int attacknum);

protected:

	Vec2 pos_;
	std::vector<AttackBase*> attack_;

};

