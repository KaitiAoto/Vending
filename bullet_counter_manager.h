//================================================================
//
// �e���J�E���^�[�}�l�[�W���[[bullet_counter_manager.h]
// Author : Kaiti Aoto
//
//================================================================

// ��d�C���N���[�h�h�~
#ifndef _BULLET_COUNTER_MANAGER_H_
#define _BULLET_COUNTER_MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "bullet_counter.h"
#include "bullet_icon.h"

// �}�N����`
#define MAX_BULLETCNT (2)
#define BULLETCNTDATA (10)

// �e���J�E���^�[�}�l�[�W���[�N���X
class CBulletCntMana
{
public:

	//�����o�֐�
	CBulletCntMana();
	~CBulletCntMana();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBulletCntMana* Create(D3DXVECTOR3 pos);
	static void UpdateCounter(void);

private:
	//�ÓI�����o�ϐ�
	static int m_nCount;								// �J�E���g
	static CBullerCounter* m_pCounter[MAX_BULLETCNT];	// �J�E���^�[�ւ̃|�C���^
	static CBulletIcon* m_pIcon;						// �e�A�C�R���ւ̃|�C���^
};

#endif