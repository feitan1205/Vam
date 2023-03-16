#pragma once
#include <memory>
#include <map>
#include <list>
#include "../Vector2.h"
#include "Scene.h"

class PlayerBase;
class EnemyBase;
class InputState;
class Map;

/// <summary>
/// �Q�[�����V�[��
/// </summary>
class GameplayingScene : public Scene
{
public:

	GameplayingScene(SceneManager& manager, int selectcharacter, const InputState& input);
	~GameplayingScene();

	void Update(const InputState& input);
	void Draw();

	bool CheckHit(Vec2 minhitbox1, Vec2 maxhitbox1, Vec2 minhitbox2, Vec2 maxhitbox2);		//�l�p�̓����蔻��
	bool CheckHitCircle(Vec2 playerpos, float circle, Vec2 enemypos, float enemycircle);	//�~�̓����蔻��

private:

	const InputState& input_;	//���̓L�[�̎擾
	Map* map_;					//�}�b�v
	PlayerBase* player_;		//�v���C���[
	Vec2 playerpos_;			//�v���C���[�̍��W
	Vec2 playervector_;			//�v���C���[�̈ړ��x�N�g��
	bool charactervector_;		//�v���C���[�̌����Ă�������@�E�Ffalse�A���Ftrue
	std::list<std::shared_ptr<EnemyBase>> enemies_;	//�G�l�~�[
	int animationcount_;		//�A�j���[�V�����̂��߂̃J�E���g
	int enemflamecount_;		//�G�l�~�[�����̃J�E���g
	int tmpLv_;					//�ߋ����x���̕ۊ�
	bool tmpishitkey_;			//�ߋ��L�[�̕ۊ�
	int frametimer;
	int timer;
	int maxenemynum_;
	int enemylv_;
	int enemynum_;
	Vec2 enemypos_;
	int hitsoundhandle_;
	int lvupsoundhandle_;
	int catchexpsoundhandle_;
	int gamebgm_;
	bool timeenemycreat_;

	static constexpr int fade_interval = 60;
	int fadeTimer_ = 0;	//�t�F�[�h�^�C�}�[
	int fadeVolume_ = 0;	//����`�Ƃ̃u�����h�

};

