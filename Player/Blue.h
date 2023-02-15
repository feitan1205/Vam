#pragma once
#include "PlayerBase.h"
#include "../Vector2.h"

class Blue :
    public PlayerBase
{
public:

    Blue(Vec2 playerpos);
    ~Blue();

    void Init();
    void End();
    void Update(Vec2 playerpos, bool charactervector);
    void Draw();
    //•`‰æ
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    void SetHitBox(Vec2 playerpos);
    int GetHandle() { return m_blueH_; }

    void Damage(int enemyattackpoint);

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }

    void GetExp(int exppoint);
    int GetNowLv() { return nowLv_; }
    int GetPlayerSpeed() { return speed_; }

private:

    int m_blueH_;
    int m_idleH_[4];
    int m_moveH_[6];
    int sizeX;
    int sizeY;
    int flamecount;
    Vec2 playerpos_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    float hppercentage_;
    float exppercentage_;

private:

    int maxhp_;
    int nowhp_;
    int maxexp_;
    int nowexp_;
    int nowLv_;
    int speed_;
    int cooldownpercentage_;

};

