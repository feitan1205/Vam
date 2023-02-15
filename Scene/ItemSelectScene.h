#pragma once
#include "Scene.h"
#include "../Vector2.h"

class InputState;
class SceneManager;
class PlayerBase;

enum Item {
	ao,
	murasaki,
	aka,
	itemmax
};

class ItemSelectScene : public Scene
{
public:
	ItemSelectScene(SceneManager& manager);
	~ItemSelectScene();
	virtual void Update(const InputState& input)override;
	void Draw();

	void SetPlayer(PlayerBase* player) { player_ = player; }
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
};
