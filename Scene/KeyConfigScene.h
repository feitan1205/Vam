#pragma once
#include "Scene.h"

class InputState;
class SceneManager;

/// <summary>
/// �L�[�R���t�B�O�V�[��
/// </summary>
class KeyConfigScene : public Scene
{
private:
	const InputState& inputState_;

	//���ݑI�𒆂̃C���f�b�N�X
	int currentInputIndex_;

	//���ݓ���̓��͕͂ҏW���ł�
	bool isEditing = false;
public:
	KeyConfigScene(SceneManager& manager, const InputState& input);
	void Update(const InputState& input);
	void Draw();
};

