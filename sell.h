//==============================
//
// ����[matchup.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _SELL_H_
#define _SELL_H_

// �C���N���[�h
#include "main.h"
#include "enemy_base.h"

// �}�N����`

// �����N���X
class CSell
{
public:
	// �����o�֐�
	CSell();
	~CSell();

	static void Update(void);

private:
	

	// �����o�ϐ�
	static int m_nCntSellTime;

};

#endif