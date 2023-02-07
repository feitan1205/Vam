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
    void Damage(int attackpoint,int attacknumber);
    void Death();
    bool GetIsEnabled() { if (isEnabled_ && isEnabledexp_) { return false; } else { return true; } }

    void SetHitBox(Vec2 playerpos);
    void SetCoolDownTime();

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }
    int GetNowHP() { return nowhp_; }
    int GetCoolDownTime() { return cooldowntime_; }
    int GetAttackPoint() { return attackpoint_; }
    Vec2 GetPos() { return pos_; }
    float GetCircle() { return hitcircle_; }

    void AttackHit(bool attackhit,int attacknumber) { attackhit_[attacknumber] = attackhit; }
    bool IsHitAttack(int attacknumber) { return attackhit_[attacknumber]; }
   
private:

    Vec2 pos_;
    Vec2 vector_;
    int handle_[8];
    int expH_;
    int flamecount_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    float hitcircle_;
    int tmprand_;
    bool damageflag_;
    int damagedrawframe_[3];

private:

    int nowhp_;
    int temphp_;
    int damagepoint_[3];
    int attackpoint_;
    int cooldowntime_;
    bool attackhit_[3];
    bool isEnabled_;
    bool isEnabledexp_;

};

