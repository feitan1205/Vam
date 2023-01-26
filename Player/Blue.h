#pragma once
#include "PlayerBase.h"


class Blue :
    public PlayerBase
{
public:

    Blue();
    ~Blue();

    void Init();
    void End();
    void Update();

    void Draw();
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    int GetHandle() { return m_blueH_; }

private:

    int m_blueH_;
    int m_idleH_[4];
    int m_moveH_[6];
    int x;
    int y;
    int sizeX;
    int sizeY;
    int flamecount;
};

