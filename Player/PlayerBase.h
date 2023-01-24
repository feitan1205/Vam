#pragma once
class PlayerBase
{
public:

	PlayerBase() {}
	virtual ~PlayerBase() {}

	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void IdleAnimation() = 0;
	virtual void MoveAnimation() = 0;
};

