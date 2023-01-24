#include <DxLib.h>
#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include "PauseScene.h"
#include "../Player/Blue.h"
#include "../Player/Red.h"
#include "CharacterSelectScene.h"

GameplayingScene::GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input) :
	Scene(manager),
	m_player(nullptr),
	input_(input),
	animationcount(40)
{
	if (selectcharacter == static_cast<int>(Character::blue)) {
		m_player = new Blue();
	}
	else if (selectcharacter == static_cast<int>(Character::red)) {
		m_player = new Red();
	}
}


void GameplayingScene::Update(const InputState& input)
{

	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}

	m_player->Update();

}

void GameplayingScene::Draw()
{

	if (input_.IsPressed(InputType::right)) {
		m_player->MoveAnimation();
	}
	else if (input_.IsPressed(InputType::left)) {
		m_player->MoveAnimation();
	}
	else {
		m_player->IdleAnimation();
	}

}