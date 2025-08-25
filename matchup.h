//==============================
//
// ëäê´[matchup.h]
// Author:kaiti
//
//==============================
#ifndef MATCHUP_H_
#define MATCHUP_H_

#include "main.h"
#include "bullet.h"
#include "enemy.h"

#define ADVANTAGE (2) 
#define DISADVANTAGE (2)

//ÉNÉâÉX
class CMatchUp
{
public:
	//
	CMatchUp();
	~CMatchUp();

	int Check(CBullet::TYPE Bullet,CEnemy::TYPE Enemy);

	void One_Shot(void) { m_nAttack = ENEMY_LIFE; }
	void Advantage(void) { m_nAttack *= ADVANTAGE; }
	void Disadvantage(void) { m_nAttack /= DISADVANTAGE; }
	void NoDamage(void) { m_nAttack = 0; }

private:
	void CanToEnemy(void);
	void CapsuleToEnemy(void);
	void IceToEnemy(void);
	void PetBottleToEnemy(void);
	void DustToEnemy(void);
	void SnackToEnemy(void);
	void CigaretToEnemy(void);
	void CardToEnemy(void);
	void BottleToEnemy(void);



	//
	int m_nAttack;
	CEnemy::TYPE m_Enemy;
};

#endif