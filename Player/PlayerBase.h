#pragma once
#include "../Vector2.h"

class PlayerBase
{
public:

	PlayerBase() {}
	virtual ~PlayerBase() {}

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void IdleAnimation(bool charactervector) = 0;
	virtual void MoveAnimation(bool charactervector) = 0;

protected:

	Vec2 pos_;

};

