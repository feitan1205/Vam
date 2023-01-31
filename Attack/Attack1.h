#pragma once
#include "../Vector2.h"

class Attack1
{
public:

	Attack1();
	~Attack1();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage);
	void Draw(bool charactervector);

	bool GetIsAttack() { return attackflag_; }

private:

	int attack1H_[4];
	int flamecount;
	float cooldowntime_;
	bool attackflag_;

};

