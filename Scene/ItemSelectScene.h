#pragma once
#include "Scene.h"
#include "../Vector2.h"

class InputState;
class SceneManager;
class PlayerBase;


class ItemSelectScene : public Scene
{
public:
	ItemSelectScene(SceneManager& manager);
	~ItemSelectScene();
	virtual void Update(const InputState& input)override;
	void Draw();

	void SetPlayer(PlayerBase* player);
	
	bool CheckHit(int posX, int posY, int sizeX, int sizeY);

private:

	PlayerBase* player_;
	int levelupweaponnumber_;
	bool finishlvup;

	Vec2 mousepos_;

	int pw_width;
	int	pw_height;
	int	pw_start_x;
	int	pw_start_y;
	Vec2 itemboxsize_;
	int selectidx_;
	int selectnum_;
	bool selectok_;
	int selectkind_[4];
	Vec2 allmoveposition_;

};
