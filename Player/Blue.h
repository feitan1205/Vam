#pragma once
#include "PlayerBase.h"
#include "../Vector2.h"

class Blue :
    public PlayerBase
{
public:

    Blue(Vec2 playerpos);
    virtual ~Blue();

    void Init();
    void End();
    void Update(Vec2 playerpos, bool charactervector, Vec2 enemypos);
    void Draw();

    void SetData(int lvupsound,int catchexpsound);

    //•`‰æ
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    void SetHitBox(Vec2 playerpos);
    int GetHandle() { return m_blueH_; }

    void Damage(int enemyattackpoint);

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }
    Vec2 GetExpMinHitBox() { return minexphitbox_; }
    Vec2 GetExpMaxHitBox() { return maxexphitbox_; }

    void GetExp(float exppoint);
    int GetNowLv() { return nowLv_; }
    float GetPlayerSpeed() { return (speed_ + (speed_ / 100 * movespeedpercentage_)); }
    float GetCatchExpCircle() { return catchexpcircle_ + (40 * circlescale_); }
    int GetNowHp() { return nowhp_; }

private:

    int m_blueH_;
    int m_idleH_[4];
    int idledamageH_[4];
    int m_moveH_[6];
    int movedamageH_[6];
    int damageflame_;
    int sizeX;
    int sizeY;
    int flamecount;
    Vec2 playerpos_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    Vec2 minexphitbox_;
    Vec2 maxexphitbox_;
    float hppercentage_;
    float exppercentage_;
    int lvupsound_;
    int catchexpsound_;

private:

    int maxhp_;
    int nowhp_;
    float maxexp_;
    float nowexp_;
    float maxexpscale_;
    int nowLv_;
    float speed_;
    int cooldownpercentage_;
    float catchexpcircle_;

};

