#include "ItemSelectScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"

ItemSelectScene::ItemSelectScene(SceneManager& manager):
	Scene(manager)
{
}

ItemSelectScene::~ItemSelectScene()
{
}

void ItemSelectScene::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PopScene();
		return;
	}
}

void ItemSelectScene::Draw()
{
	constexpr int pw_width = 400;	//ポーズ枠の幅
	constexpr int pw_height = 300;	//ポーズ枠の高さ
	constexpr int pw_start_x = (640 - pw_width) / 2;	//ポーズ枠の左
	constexpr int pw_start_y = (480 - pw_height) / 2;	//ポーズ枠上

	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//ポーズウィンドウセロファン(黒い)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//通常描画に戻す

	//ポーズ中メッセージ
	DrawString(pw_start_x + 10, pw_start_y + 10, L"select...", 0xffff88);

	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}
