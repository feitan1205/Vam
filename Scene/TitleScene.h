#pragma once
#include "Scene.h"
#include "../Vector2.h"

class InputState;

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene
{

	//�`��ϐ�
private:
	static constexpr int fade_interval = 60;
	int m_background = -1;	//�^�C�g���摜
	int gradH_ = -1;
	int fadeTimer_ = fade_interval;	//�t�F�[�h�^�C�}�[
	int fadeValue_ = 255;	//����`�Ƃ̃u�����h�

	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);

	//Update�p�����o�֐��|�C���^
	void (TitleScene::* updateFunc_)(const InputState& input);

	//�e��{�^���ϐ�
private:

	int m_startbuttonH = -1;
	Vec2 m_startbutton;
	Vec2 m_buttonsize;
	int m_optionbuttonH = -1;
	int m_optionbuttonX;
	int m_optionbuttonY;
	int m_optionbuttonsizeX;
	int m_optionbuttonsizeY;
	bool isnextscene_;
	int titleBGM_;
	int selectsound_;

public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(int posX, int posY, int sizeX, int sizeY);

};