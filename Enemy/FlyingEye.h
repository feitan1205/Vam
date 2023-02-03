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
    void Damage(int attackpoint);
    void Death();
    bool GetIsEnabled() { if (isEnabled_ && isEnabledexp_) { return false; } else { return true; } }

    void SetHitBox(Vec2 playerpos);
    void SetCoolDownTime();

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }
    int GetNowHP() { return nowhp_; };
    int GetCoolDownTime() { return cooldowntime_; }
    int GetAttackPoint() { return attackpoint_; }

    void Attack1Hit(bool attack1hit) { attack1hit_ = attack1hit; }
    bool IsHitAttack1() { return attack1hit_; }
    void Attack2Hit(bool attack2hit) { attack2hit_ = attack2hit; }
    bool IsHitAttack2() { return attack2hit_; }

private:

    Vec2 pos_;
    Vec2 vector_;
    int handle_[8];
    int expH_;
    int flamecount_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    int tmprand_;
    bool damageflag_;
    int damagedrawframe_;

private:

    int nowhp_;
    int temphp_;
    int damagepoint_;
    int attackpoint_;
    int cooldowntime_;
    bool attack1hit_;
    bool attack2hit_;
    bool isEnabled_;
    bool isEnabledexp_;

};

