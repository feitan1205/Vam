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
	virtual void Draw(bool charactervector) = 0;

};

