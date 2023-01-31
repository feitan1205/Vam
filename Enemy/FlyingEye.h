#pragma once
#include "EnemyBase.h"
#include "../Vector2.h"

class FlyingEye :
    public EnemyBase
{

public:

    FlyingEye();
    ~FlyingEye();

    void Init(Vec2 playerpos);
    void End();
    void Update(Vec2 playerpos);
    void Draw(bool charactervector,Vec2 playerpos);
    void PlayerMove(Vec2 playermove);

private:

    Vec2 pos_;
    Vec2 vector_;
    int handle_[8];
    int flamecount;

};

