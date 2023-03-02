#include "DxLib.h"
#include "Blue.h"
#include "../DrawFunctions.h"
#include "../game.h"

Blue::Blue(Vec2 playerpos) :
	sizeX(),
	sizeY(),
	m_blueH_(),
	flamecount(),
	cooldownpercentage_(100),
	playerpos_(playerpos),
	maxhp_(100),
	nowhp_(100),
	hppercentage_(),
	maxexp_(),
	nowexp_(),
	nowLv_(0),
	speed_(1),
	maxexpscale_(2),
	damageflame_(0)
{
	m_blueH_ = my::MyLoadGraph(L"Data/blue/Blue.png");
	LoadDivGraph(L"Data/blue/Idledamage.png", 4, 4, 1, 24, 24, idledamageH_);
	LoadDivGraph(L"Data/blue/Idle.png", 4, 4, 1, 24, 24, m_idleH_);
	LoadDivGraph(L"Data/blue/Movedamage.png", 6, 6, 1, 24, 24, movedamageH_);
	LoadDivGraph(L"Data/blue/Move.png", 6, 6, 1, 24, 24, m_moveH_);
	GetGraphSize(m_blueH_, &sizeX, &sizeY);
}

Blue::~Blue()
{

	DeleteGraph(m_blueH_);

	for (int i = 0; i < 4; i++) {
		DeleteGraph(m_idleH_[i]);
		DeleteGraph(idledamageH_[i]);
	}

	for (int i = 0; i < 6; i++) {
		DeleteGraph(m_moveH_[i]);
		DeleteGraph(movedamageH_[i]);
	}

}

void Blue::Init()
{
	PlayerBase::Init(cooldownpercentage_);
	nowexp_ = 0;
	maxexp_ = 1;
}

void Blue::End()
{
}

void Blue::Update(Vec2 playerpos, bool charactervector, Vec2 enemypos)
{
	PlayerBase::Update(cooldownpercentage_, charactervector,playerpos, enemypos);

	hppercentage_ = static_cast <float>(nowhp_) / static_cast <float>(maxhp_);
	exppercentage_ = static_cast <float>(nowexp_) / static_cast <float>(maxexp_);
	playerpos_ = playerpos;

}

void Blue::Draw()
{
	DrawGraph((1280 / 2) - (sizeX / 2), (740 / 2) - (sizeY / 2), m_blueH_, true);
}

void Blue::IdleAnimation(bool charactervector)
{
	flamecount++;

	if (flamecount >= 40) {
		flamecount = 0;
	}

	if (damageflame_ == 0) {
		if (flamecount >= 0 && flamecount < 10) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_idleH_[0], true, charactervector);
		}
		else if (flamecount >= 10 && flamecount < 20) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_idleH_[1], true, charactervector);
		}
		else if (flamecount >= 20 && flamecount < 30) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_idleH_[2], true, charactervector);
		}
		else if (flamecount >= 30 && flamecount < 40) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_idleH_[3], true, charactervector);
		}
	}

	if (damageflame_ > 0) {

		if (flamecount >= 0 && flamecount < 10) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, idledamageH_[0], true, charactervector);
		}
		else if (flamecount >= 10 && flamecount < 20) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, idledamageH_[1], true, charactervector);
		}
		else if (flamecount >= 20 && flamecount < 30) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, idledamageH_[2], true, charactervector);
		}
		else if (flamecount >= 30 && flamecount < 40) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, idledamageH_[3], true, charactervector);
		}

		damageflame_--;
	}

	DrawBox((Game::kScreenWidth / 2) - 20 - 1, (Game::kScreenHeight / 2) + 27 - 1, (Game::kScreenWidth / 2) - 20 + (40 * 1) + 1, (Game::kScreenHeight / 2) + 35 + 1, 0x000000, true);
	DrawBox((Game::kScreenWidth / 2) - 20 , (Game::kScreenHeight / 2) + 27 , (Game::kScreenWidth / 2) - 20 + (40 * hppercentage_), (Game::kScreenHeight / 2) + 35,0xff0000, true);

	DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);

	DrawBox(0, 1, Game::kScreenWidth, 20, 0x000000, true);
	DrawBox(1, 1, Game::kScreenWidth * exppercentage_, 20, 0x00ffff, true);
	DrawBox(0, 1, Game::kScreenWidth, 20, 0xffffff, false);

	DrawFormatString(Game::kScreenWidth - 60, 3, 0xffffff, L"LvF%d", nowLv_, true);

	PlayerBase::Draw(charactervector);
	
	/*DrawFormatString(0, 32, 0xffffff, L"%f", minhitbox_.x, true);
	DrawFormatString(0, 64, 0xffffff, L"%f", minhitbox_.y, true);*/
}

void Blue::MoveAnimation(bool charactervector)
{
	flamecount++;

	if (flamecount >= 60) {
		flamecount = 0;
	}

	if (flamecount >= 0 && flamecount < 10) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[0], true, charactervector);
	}
	else if (flamecount >= 10 && flamecount < 20) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[1], true, charactervector);
	}
	else if (flamecount >= 20 && flamecount < 30) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[2], true, charactervector);
	}
	else if (flamecount >= 30 && flamecount < 40) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[3], true, charactervector);
	}
	else if (flamecount >= 40 && flamecount < 50) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[4], true, charactervector);
	}
	else if (flamecount >= 50 && flamecount < 60) {
		DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, m_moveH_[5], true, charactervector);
	}

	if (damageflame_ > 0) {

		if (flamecount >= 0 && flamecount < 10) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[0], true, charactervector);
		}
		else if (flamecount >= 10 && flamecount < 20) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[1], true, charactervector);
		}
		else if (flamecount >= 20 && flamecount < 30) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[2], true, charactervector);
		}
		else if (flamecount >= 30 && flamecount < 40) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[3], true, charactervector);
		}
		else if (flamecount >= 40 && flamecount < 50) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[4], true, charactervector);
		}
		else if (flamecount >= 50 && flamecount < 60) {
			DrawRotaGraph((Game::kScreenWidth / 2), (Game::kScreenHeight / 2), 2, 0, movedamageH_[5], true, charactervector);
		}

		damageflame_--;
	}

	DrawBox((Game::kScreenWidth / 2) - 20 - 1, (Game::kScreenHeight / 2) + 27 - 1, (Game::kScreenWidth / 2) - 20 + (40 * 1) + 1, (Game::kScreenHeight / 2) + 35 + 1, 0x000000, true);
	DrawBox((Game::kScreenWidth / 2) - 20, (Game::kScreenHeight / 2) + 27, (Game::kScreenWidth / 2) - 20 + (40 * hppercentage_), (Game::kScreenHeight / 2) + 35, 0xff0000, true);

	DrawBox(minhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, minhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, maxhitbox_.x + (Game::kScreenWidth / 2) - playerpos_.x, maxhitbox_.y + (Game::kScreenHeight / 2) - playerpos_.y, 0xff0000, false);

	DrawBox(0, 1, Game::kScreenWidth, 20, 0x000000, true);
	DrawBox(1, 1, Game::kScreenWidth * exppercentage_, 20, 0x00ffff, true);
	DrawBox(0, 1, Game::kScreenWidth, 20, 0xffffff, false); 

	DrawFormatString(Game::kScreenWidth - 60, 3, 0xffffff, L"LvF%d", nowLv_, true);

	PlayerBase::Draw(charactervector);
}

void Blue::SetHitBox(Vec2 playerpos)
{

	minhitbox_.x = playerpos.x - 10;
	minhitbox_.y = playerpos.y - 10;
	maxhitbox_.x = playerpos.x + 10;
	maxhitbox_.y = playerpos.y + 10;

}

void Blue::Damage(int enemyattackpoint)
{

	nowhp_ -= enemyattackpoint;

	damageflame_ = 10;

}

void Blue::GetExp(float exppoint)
{

	exppoint = exppoint + (exppoint / 100) * exppointpercentage_;

	nowexp_ += exppoint;

	if (nowexp_ >= maxexp_) {
		nowLv_++;
		nowexp_ = 0;
		if (nowLv_ == 4)
		{
			maxexpscale_ = 1.5f;
		}
		if (nowLv_ == 7) {
			maxexpscale_ = 1.3f;
		}

		maxexp_ *= maxexpscale_;

	}
}

