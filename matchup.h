//==============================
//
// ����[matchup.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef MATCHUP_H_
#define MATCHUP_H_

// �C���N���[�h
#include "main.h"
#include "bullet.h"
#include "enemy.h"

// �}�N����`
#define ADVANTAGE (2) 
#define DISADVANTAGE (2)

// �����N���X
class CMatchUp
{
public:
	// �����o�֐�
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

	// �����o�ϐ�
	int m_nAttack;			// �U����
	CEnemy::TYPE m_Enemy;	// �G�̎��
};

#endif