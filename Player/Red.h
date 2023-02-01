#pragma once
#include "PlayerBase.h"
#include "../Vector2.h"


class Red :
    public PlayerBase
{
public:

    Red(Vec2 playerpos);
    ~Red();

    void Init();
    void End();
    void Update(Vec2 playerpos);

    void Draw();
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    int GetHandle() { return m_redH_; }
    void SetHitBox(Vec2 playerpos);

    void Damage(int enemyattackpoint) {};

    Vec2 GetMinHitBox() { return minhitbox_; }
    Vec2 GetMaxHitBox() { return maxhitbox_; }

private:

    int m_redH_;
    int m_idleH_[4];
    int m_moveH_[6];
    int sizeX_;
    int sizeY_;
    int flamecount_;
    int cooldownpercentage_;
    Vec2 minhitbox_;
    Vec2 maxhitbox_;
};
