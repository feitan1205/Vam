#pragma once
#include "Scene.h"

class InputState;
class SceneManager;

class ItemSelectScene : public Scene
{
public:
	ItemSelectScene(SceneManager& manager);
	~ItemSelectScene();
	virtual void Update(const InputState& input)override;
	void Draw();
private:
};
