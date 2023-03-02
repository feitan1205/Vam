#pragma once
#include "DxLib.h"
#include "AttackBase.h"
#include <memory>
#include <list>

class Attack4 :
    public AttackBase
{
public:

	Attack4();
	~Attack4();

	void Init(int cooldownpercentage);
	void End();
	void Update(int cooldownpercentage, bool charactervector, Vec2 playerpos);
	void Draw();
	void SetHitBox() {};
	int GetSize() { return shots_.size(); };

	bool GetIsAttack() { return attackflag_; }
	Vec2 GetPos(int i);
	Vec2 GetAttackMinHitBox() { return { 0,0 }; }
	Vec2 GetAttackMaxHitBox() { return { 0,0 }; }
	float GetAttackHitCircle() { return circle_; }
	int GetAttackPoint() { return attackpoint_ + GetRand(randattackpoint_); }
	int GetMyNumber() { return 3; }
	int GetNowLv() { return nowlv_; }
	int GetMaxLv() { return maxlv_; }
	void SetLv(int i);
	void SetEnemyPos(Vec2 enempos) { enempos_ = enempos; }

	class Shot {
	public:

		Shot(Vec2 playerpos) :playerpos_(playerpos),speed_(2) ,isenable_(true) {};
		virtual ~Shot();

		void Update();

		void SetPos(Vec2 enempos);
		Vec2 GetPos() { return pos_; }
		void Delete() { isenable_ = false; }

		bool GetIsEnabled() { return isenable_; }

	private:

		Vec2 playerpos_;
		Vec2 pos_;
		Vec2 vector_;
		bool isenable_;
		int speed_;

	};

private:

	int nowlv_;
	int maxlv_;
	int attack4H_;
	int flamecount_;
	float cooldowntime_;
	bool attackflag_;
	int attackpoint_;
	int randattackpoint_;
	bool attackvector_;
	int shotspacecount_;
	int shotcount_;
	int shotmaxcount_;
	Vec2 playerpos_;
	Vec2 enempos_;
	float circle_;


	std::list<std::shared_ptr<Shot>> shots_;

};

