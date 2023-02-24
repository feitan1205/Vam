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
    bool GetIsEnabled() { return isEnabled_; }

    void SetHitBox(Vec2 playerpos);
    void SetCoolDownTime();

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }
    int GetNowHP() { return nowhp_; }
    int GetCoolDownTime() { return cooldowntime_; }
    int GetAttackPoint() { return attackpoint_; }
    Vec2 GetPos() { return pos_; }
    float GetCircle() { return hitcircle_; }
    bool GetIsExp() { return isEnabledexp_; }
    float GetExpPoint() { return exppoint_; }
    void AttackHit(bool attackhit, int attacknumber) {
        attackhit_[attacknumber] = attackhit;
        if (attackhit) { damagedrawframe_[attacknumber] = 30; };
    }
    bool IsHitAttack(int attacknumber) { return attackhit_[attacknumber]; }
    void DeleteEnable() { isEnabledexp_ = false; }
    bool CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2);
    void EnemyLvUp(int level);
    void ChangeExp(Vec2 pos);

private:

    Vec2 pos_;
    Vec2 vector_;
    int handle_[8];
    int expH1_;
    int expH2_;
    int flamecount_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    float hitcircle_;
    int tmprand_;
    bool damageflag_[3];
    int damagedrawframe_[3];
    bool left_or_right;

private:

    int level_;
    int nowhp_;
    int temphp_;
    int damagepoint_[3];
    int attackpoint_;
    int cooldowntime_;
    bool attackhit_[3];
    bool isEnabled_;
    bool isEnabledexp_;
    int explv_;
    float exppoint_;
    float speed_;

};

