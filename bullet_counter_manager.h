//===========================================
//
// �^�C�}�[�}�l�[�W���[[timer_manager.h]
// Author:kaiti
//
//===========================================
#ifndef _BULLET_COUNTER_MANAGER_H_
#define _BULLET_COUNTER_MANAGER_H_

#include "main.h"
#include "bullet_counter.h"
#include "bullet_icon.h"

#define MAX_BULLETCNT (2)
#define BULLETCNTDATA (10)

//�I�u�W�F�N�g2D�N���X
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

	static CBulletCntMana* Create(D3DXVECTOR3 pos);
	static void SetBulletCount(void);
private:
	//�����o�ϐ�
	static int m_nCount;
	static CBullerCounter* m_pTimer[MAX_BULLETCNT];
	static CBulletIcon* m_pIcon;
};

#endif