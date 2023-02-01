#pragma once
#include "../Vector2.h"

class Attack1
{
public:

	Attack1();
	~Attack1();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage,bool charactervector);
	void Draw();
	void SetHitBox();

	bool GetIsAttack() { return attackflag_; }
	//int GetAttack1Point() { return attackpoint + GetRand(5); }

private:

	int attack1H_[4];
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	bool attackvector_;

};

