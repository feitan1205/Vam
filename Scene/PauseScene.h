#pragma once
#include "Scene.h"
#include "../Vector2.h"
#include "GameplayingScene.h"

class InputState;
class SceneManager;

/// <summary>
/// ポーズシーン
/// </summary>

class PauseScene : public Scene
{
private:

	Vec2 itemboxsize_;
	Vec2 allmoveposition_;
	int pw_width;
	int pw_height;
	int pw_start_x;
	int pw_start_y;
	int buttonH_;
	GameplayingScene* playingscene_;

public:

	PauseScene(SceneManager& manager);
	~PauseScene();
	void SetPlayingScene(GameplayingScene* playingscene);
	virtual void Update(const InputState& input)override;
	void Draw();
	bool CheckHit(int posX, int posY, int sizeX, int sizeY);
};

