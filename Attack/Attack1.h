#pragma once
#include "../Vector2.h"

class Attack1
{
public:

	Attack1();
	~Attack1();

	void Init();
	void End();
	void Update();
	void Draw(bool charactervector);

private:

	int attack1H_[4];
	int flamecount;

};

