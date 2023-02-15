#include "ItemSelectScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "../Player/PlayerBase.h"
#include "../game.h"

ItemSelectScene::ItemSelectScene(SceneManager& manager):
	Scene(manager),
	finishlvup(false)
{
	pw_width = Game::kScreenWidth / 2;	//�E�B���h�E�g�̕�
	pw_height = Game::kScreenHeight - 100;	//�E�B���h�E�g�̍���
	pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//�E�B���h�E�g�̍�
	pw_start_y = (Game::kScreenHeight - pw_height) / 2;	//�E�B���h�E�g��

	itemboxsize_.x = Game::kScreenWidth / 2 - 80;
	itemboxsize_.y = 100;

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

	if (finishlvup) {
		manager_.PopScene();
		return;
	}


	if (input.IsTriggered(InputType::next)) {
		for (int i = 0; i < Item::itemmax; i++) {
			if (CheckHit(pw_start_x + 50, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i), pw_start_x + itemboxsize_.x, (pw_start_y + 30 * i) + (itemboxsize_.y * (i + 1)))) {
				levelupweaponnumber_ = i;
				player_->SetLv(levelupweaponnumber_);
				finishlvup = true;
				break;
			}
		}
	}

}

void ItemSelectScene::Draw()
{
	
	if (finishlvup) {
		return;
	}

	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//�|�[�Y�E�B���h�E�Z���t�@��(����)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�ʏ�`��ɖ߂�

	//�|�[�Y�����b�Z�[�W
	DrawString((Game::kScreenWidth / 2) - 30, pw_start_y + 10, L"LvUP!!!", 0xffff88);

	//�|�[�Y�E�B���h�E�g��
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
	
	for (int i = 0; i < Item::itemmax; i++) {
		DrawBox(pw_start_x + 50, (pw_start_y + 30 * (i + 1))+ (itemboxsize_.y * i), pw_start_x + itemboxsize_.x, (pw_start_y + 30 * i) + (itemboxsize_.y * (i + 1)), 0xffffff, true);
		DrawFormatString(pw_start_x + 50 + 500, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5, 0x000000, L"Lv�F%d", player_->GetWeaponLv(i) + 1,true);
		switch (player_->GetAttackingNumber(i))
		{
		case Item::ao:
			DrawFormatString(pw_start_x + 50 + 50, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5, 0x000000, L"��", true);
			break;
		case Item::murasaki:
			DrawFormatString(pw_start_x + 50 + 50, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5, 0x000000, L"��", true);
			break;
		case Item::aka:
			DrawFormatString(pw_start_x + 50 + 50, (pw_start_y + 30 * (i + 1)) + (itemboxsize_.y * i) + 5, 0x000000, L"��", true);
			break;
		default:
			break;
		}
	}

}

bool ItemSelectScene::CheckHit(int posX, int posY, int sizeX, int sizeY)
{

	int mouseX = 0;
	int mouseY = 0;

	GetMousePoint(&mouseX, &mouseY);

	if (mouseX < posX) return false;
	if (mouseX > sizeX) return false;
	if (mouseY < posY) return false;
	if (mouseY > sizeY) return false;

	return true;
}