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

	virtual void Damage(int attackpoint,int attacknumber) = 0;
	virtual void Death() = 0;
	virtual bool GetIsEnabled() = 0;

	virtual void SetHitBox(Vec2 playerpos) = 0;
	virtual void SetCoolDownTime() = 0;

	virtual Vec2 GetMinHitBox() = 0;
	virtual Vec2 GetMaxHitBox() = 0;
	virtual int GetNowHP() = 0;
	virtual int GetCoolDownTime() = 0;
	virtual int GetAttackPoint() = 0;
	virtual Vec2 GetPos() = 0;
	virtual float GetCircle() = 0;
	virtual bool GetIsExp() = 0;
	virtual float GetExpPoint() = 0;
	virtual void AttackHit(bool attack3hit,int attacknumber) = 0;
	virtual bool IsHitAttack(int attacknumber) = 0;
	virtual void DeleteEnable() = 0;
	virtual void EnemyLvUp(int level) = 0;
	virtual void ChangeExp(Vec2 pos) = 0;

private:



};

