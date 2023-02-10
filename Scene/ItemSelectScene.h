#pragma once
#include "Scene.h"

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

	void SetPlayer(PlayerBase* player) { player_ = player; }

private:

	PlayerBase* player_;
	bool lvup_or_creat;
	int levelupweaponnumber_;
	bool finishlvup_or_creat;
};
