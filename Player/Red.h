#pragma once
#include "PlayerBase.h"
class Red :
    public PlayerBase
{
public:

    Red();
    ~Red();

    void Init();
    void End();
    void Update();

    void Draw();
    void IdleAnimation(bool charactervector);
    void MoveAnimation(bool charactervector);

    int GetHandle() { return m_redH_; }

private:

    int m_redH_;
    int m_idleH_[4];
    int x;
    int y;
    int sizeX;
    int sizeY;
    int flamecount;
};
