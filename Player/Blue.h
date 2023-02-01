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
    void Update(Vec2 playerpos);
    void Draw();
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    void SetHitBox(Vec2 playerpos);
    int GetHandle() { return m_blueH_; }

private:

    int m_blueH_;
    int m_idleH_[4];
    int m_moveH_[6];
    int sizeX;
    int sizeY;
    int flamecount;
    int cooldownpercentage_;
    Vec2 playerpos_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
    float hppercentage_;
    
private:

    int maxhp_;
    int nowhp_;

};

