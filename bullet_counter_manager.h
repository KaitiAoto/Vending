//================================================================
//
// �e���J�E���^�[�}�l�[�W���[[bullet_counter_manager.h]
// Author:kaiti
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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBulletCntMana* Create(D3DXVECTOR3 pos);
	static void SetBulletCount(void);

private:
	//�ÓI�����o�ϐ�
	static int m_nCount;								// �J�E���g
	static CBullerCounter* m_pTimer[MAX_BULLETCNT];		// �J�E���^�[�ւ̃|�C���^
	static CBulletIcon* m_pIcon;						// �e�A�C�R���ւ̃|�C���^
};

#endif