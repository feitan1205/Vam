#pragma once
#include "../Vector2.h"
#include <vector>

class AttackBase;

class Attack1;
class Attack2;
class Attack3;
class Attack4;

enum PlayerStatus {
	ao,
	murasaki,
	aka,
	//bullet,
	boots,
	book,
	candle,
	spinach,
	crown,
	orb,
	kindmax
};

struct Item{

	int level;
	int maxlevel;

};


class PlayerBase
{
public:

	PlayerBase();
	PlayerBase(Vec2 playerpos);
	~PlayerBase();

	virtual void Init() = 0;
	virtual void Init(int cooldownpercentage);
	virtual void End() = 0;
	virtual void Update(Vec2 playerpos, bool charactervector,Vec2 enemypos) = 0;
	virtual void Update(int cooldownpercentage, bool charactervector,Vec2 playerpos,Vec2 enemypos);
	virtual void Draw(bool charactervector);
	virtual void SetData(int lvupsound,int catchexpsound) = 0;
	virtual void IdleAnimation(bool charactervector) = 0;
	virtual void MoveAnimation(bool charactervector) = 0;
	virtual void SetHitBox(Vec2 playerpos) = 0;
	virtual void Damage(int enemyattackpoint) = 0;

	virtual Vec2 GetMinHitBox() = 0;
	virtual Vec2 GetMaxHitBox() = 0;
	virtual Vec2 GetExpMinHitBox() = 0;
	virtual Vec2 GetExpMaxHitBox() = 0;

	virtual void GetExp(float exppoint) = 0;
	virtual int GetNowLv() = 0;
	virtual float GetPlayerSpeed() = 0;
	virtual float GetCatchExpCircle() = 0;
	virtual int GetNowHp() = 0;

	int GetSize(int attacknum);
	Vec2 GetBulletPos(int attacknum,int j);
	int GetAttackPoint(int attacknum);
	bool GetIsAttack(int attacknum);
	Vec2 GetAttackMinHitBox(int attacknum);
	Vec2 GetAttackMaxHitBox(int attacknum);
	float GetAttackHitCircle(int attacknum);

	int GetAttackKindNum() { return attack_.size(); }
	int GetAttackingNumber(int attacknum);

	int GetWeaponLv(int weaponnum);
	int GetWeaponMaxLv(int weaponnum);
	void SetLv(int i);
	void CreatAttack(int creatweapon);


protected:

	Vec2 pos_;
	std::vector<AttackBase*> attack_;

	Item item[PlayerStatus::kindmax];

	int attackpointpercentage_ = 0;
	float movespeedpercentage_ = 0;
	int exppointpercentage_ = 0;
	int attackscalepercentage_ = 0;
	int cooltimepercentage_ = 0;
	int circlescale_ = 0;
};

