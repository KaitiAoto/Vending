//==============================
//
// ����[matchup.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "matchup.h"
#include "manager.h"
#include "camera.h"

//==================
// �R���X�g���N�^
//==================
CMatchUp::CMatchUp()
{
	m_nAttack = 0;
	m_Enemy = CEnemy::TYPE_LIGHTER;
}
//================
// �f�X�g���N�^
//================
CMatchUp::~CMatchUp()
{

}
//===================
// �����𒲂ׂ鏈��
//===================
int CMatchUp::Check(CBullet::TYPE Bullet, CEnemy::TYPE Enemy)
{	
	m_nAttack = BULLET_ATTACK;
	m_Enemy = Enemy;

	switch (Bullet)
	{
	case CBullet::TYPE_CAN:
		CanToEnemy();
		break;
	case CBullet::TYPE_CAPSULE:
		CapsuleToEnemy();
		break;
	case CBullet::TYPE_ICE:
		IceToEnemy();
		break;
	case CBullet::TYPE_PETBOTTLE:
		PetBottleToEnemy();
		break;
	case CBullet::TYPE_DUST:
		DustToEnemy();
		break;
	case CBullet::TYPE_SNACK:
		SnackToEnemy();
		break;
	case CBullet::TYPE_CIGARET:
		CigaretToEnemy();
		break;
	case CBullet::TYPE_CARD:
		CardToEnemy();
		break;
	case CBullet::TYPE_BOTTLE:
		BottleToEnemy();
		break;

	default:
		break;
	}

	return m_nAttack;
}
//====================
// �ʂƂ̑����𒲂ׂ�
//====================
void CMatchUp::CanToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		break;
	case CEnemy::TYPE_MONEY0:
		break;
	case CEnemy::TYPE_MONEY1:
		break;
	case CEnemy::TYPE_MAGNET:
		NoDamage();
		break;
	case CEnemy::TYPE_TORNADO:
		break;
	case CEnemy::TYPE_SPRAY:
		break;
	case CEnemy::TYPE_EXT:
		break;
	case CEnemy::TYPE_KETTLE:
		break;
	case CEnemy::TYPE_RANGE:
		Advantage();
		break;

	default:
		break;
	}
}
//===========================
// �J�v�Z���Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::CapsuleToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		Disadvantage();
		break;
	case CEnemy::TYPE_MONEY0:
		Advantage();
		break;
	case CEnemy::TYPE_MONEY1:
		Advantage();
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		Disadvantage();
		break;
	case CEnemy::TYPE_SPRAY:
		break;
	case CEnemy::TYPE_EXT:
		Disadvantage();
		break;
	case CEnemy::TYPE_KETTLE:
		break;
	case CEnemy::TYPE_RANGE:
		Disadvantage();
		break;

	default:
		break;
	}
}
//===========================
// �A�C�X�Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::IceToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		NoDamage();
		break;
	case CEnemy::TYPE_MONEY0:	
		break;
	case CEnemy::TYPE_MONEY1:
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		Disadvantage();
		break;
	case CEnemy::TYPE_SPRAY:
		Disadvantage();
		break;
	case CEnemy::TYPE_EXT:
		break;
	case CEnemy::TYPE_KETTLE:
		Disadvantage();
		break;
	case CEnemy::TYPE_RANGE:
		NoDamage();
		break;

	default:
		break;
	}
}
//================================
// �y�b�g�{�g���Ƃ̑����𒲂ׂ�
//================================
void CMatchUp::PetBottleToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		Advantage();
		break;
	case CEnemy::TYPE_MONEY0:
		break;
	case CEnemy::TYPE_MONEY1:
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		break;
	case CEnemy::TYPE_SPRAY:
		Disadvantage();
		break;
	case CEnemy::TYPE_EXT:
		break;
	case CEnemy::TYPE_KETTLE:
		Disadvantage();
		break;
	case CEnemy::TYPE_RANGE:
		Disadvantage();
		break;

	default:
		break;
	}
}
//===========================
// �󂫊ʂƂ̑����𒲂ׂ�
//===========================
void CMatchUp::DustToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		Disadvantage();
		break;
	case CEnemy::TYPE_MONEY0:
		Disadvantage();
		break;
	case CEnemy::TYPE_MONEY1:
		Disadvantage();
		break;
	case CEnemy::TYPE_MAGNET:
		NoDamage();
		break;
	case CEnemy::TYPE_TORNADO:
		Disadvantage();
		break;
	case CEnemy::TYPE_SPRAY:
		break;
	case CEnemy::TYPE_EXT:
		Disadvantage();
		break;
	case CEnemy::TYPE_KETTLE:
		Advantage();
		break;
	case CEnemy::TYPE_RANGE:
		Advantage();
		break;

	default:
		break;
	}
}
//===========================
// ���َq�Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::SnackToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		break;
	case CEnemy::TYPE_MONEY0:
		break;
	case CEnemy::TYPE_MONEY1:
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		Disadvantage();
		break;
	case CEnemy::TYPE_SPRAY:
		Disadvantage();
		break;
	case CEnemy::TYPE_EXT:
		break;
	case CEnemy::TYPE_KETTLE:
		break;
	case CEnemy::TYPE_RANGE:
		break;

	default:
		break;
	}
}
//===========================
// �^�o�R�Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::CigaretToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		NoDamage();
		break;
	case CEnemy::TYPE_MONEY0:
		Disadvantage();
		break;
	case CEnemy::TYPE_MONEY1:
		Disadvantage();
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		Disadvantage();
		break;
	case CEnemy::TYPE_SPRAY:
		break;
	case CEnemy::TYPE_EXT:
		NoDamage();
		break;
	case CEnemy::TYPE_KETTLE:
		Disadvantage();
		break;
	case CEnemy::TYPE_RANGE:
		break;

	default:
		break;
	}

}
//===========================
// �J�[�h�Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::CardToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		Disadvantage();
		break;
	case CEnemy::TYPE_MONEY0:
		Advantage();
		break;
	case CEnemy::TYPE_MONEY1:
		Advantage();
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		NoDamage();
		break;
	case CEnemy::TYPE_SPRAY:
		Disadvantage();
		break;
	case CEnemy::TYPE_EXT:
		NoDamage();
		break;
	case CEnemy::TYPE_KETTLE:
		NoDamage();
		break;
	case CEnemy::TYPE_RANGE:
		break;

	default:
		break;
	}

}
//===========================
// �r�Ƃ̑����𒲂ׂ�
//===========================
void CMatchUp::BottleToEnemy(void)
{
	switch (m_Enemy)
	{
	case CEnemy::TYPE_LIGHTER:
		Advantage();
		break;
	case CEnemy::TYPE_MONEY0:
		break;
	case CEnemy::TYPE_MONEY1:
		break;
	case CEnemy::TYPE_MAGNET:
		break;
	case CEnemy::TYPE_TORNADO:
		Advantage();
		break;
	case CEnemy::TYPE_SPRAY:
		Advantage();
		break;
	case CEnemy::TYPE_EXT:
		break;
	case CEnemy::TYPE_KETTLE:
		break;
	case CEnemy::TYPE_RANGE:
		Advantage();
		break;

	default:
		break;
	}

}
