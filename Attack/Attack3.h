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
	int GetSize() { return 0; }

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetPos(int i) { return Vec2(0, 0); }
	Vec2 GetAttackMinHitBox() { return { 0,0 }; }
	Vec2 GetAttackMaxHitBox() { return { 0,0 }; }
	float GetAttackHitCircle() { return circle_; }
	int GetAttackPoint() { return attackpoint_ + GetRand(randattackpoint_); }
	int GetMyNumber() { return 2; }
	int GetNowLv() { return nowlv_; }
	int GetMaxLv() { return maxlv_; }
	void SetLv(int i);
	void SetEnemyPos(Vec2 enempos) {};

private:

	int attack3H_;
	int alpha_;
	int add_;	//アルファの変化値
	int nowlv_;
	int maxlv_;
	float defaultcircle_;
	float circle_;
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	int randattackpoint_;
	bool attackvector_;
	Vec2 playerpos_;
	Vec2 minhitbox_;
	Vec2 maxhitbox_;

};
