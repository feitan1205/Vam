#pragma once
#include "../Vector2.h"

class Attack1;

class PlayerBase
{
public:

	PlayerBase();
	~PlayerBase();

	virtual void Init() = 0;
	virtual void Init(int cooldownpercentage);
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Update(int cooldownpercentage);
	virtual void Draw(bool charactervector);
	virtual void IdleAnimation(bool charactervector) = 0;
	virtual void MoveAnimation(bool charactervector) = 0;

protected:

	Vec2 pos_;
	Attack1* attack1;

};

