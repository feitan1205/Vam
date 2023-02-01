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

    void SetHitBox(Vec2 playerpos);
    void SetCoolDownTime();

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }

    int GetCoolDownTime() { return cooldowntime_; }
    int GetAttackPoint() { return attackpoint_; }

private:

    Vec2 pos_;
    Vec2 vector_;
    int handle_[8];
    int flamecount_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;

private:

    int attackpoint_;
    int cooldowntime_;

};

