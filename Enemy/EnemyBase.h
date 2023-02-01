#pragma once
#include "../Vector2.h" 

class EnemyBase
{
public:

	EnemyBase(){};
	virtual ~EnemyBase(){};

	virtual void Init(Vec2 playerpos) = 0;
	virtual void End() = 0;
	virtual void Update(Vec2 playerpos) = 0;
	virtual void Draw(bool charactervector,Vec2 playerpos) = 0;
	virtual void PlayerMove(Vec2 playermove) = 0;

	virtual void SetHitBox(Vec2 playerpos) = 0;
	virtual void SetCoolDownTime() = 0;

	virtual Vec2 GetMinHitBox() = 0;
	virtual Vec2 GetMaxHitBox() = 0;

	virtual int GetCoolDownTime() = 0;
	virtual int GetAttackPoint() = 0;

private:



};

