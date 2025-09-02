//======================================
//
//  ���Z�b�g�Q�[�W����[gauge_reset.h]
//  Author:kaiti
//
//======================================

// ��d�C���N���[�h�h�~
#ifndef _GAUGE_RESET_H_
#define _GAUGE_RESET_H_

// �C���N���[�h
#include "main.h"
#include "gauge.h"
#include "object2D.h"

// ���Z�b�g�Q�[�W�N���X
class CResetGauge :CObject
{
public:

	// �����o�֐�
	CResetGauge(int nPriority = 6);
	~CResetGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CResetGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXCOLOR m_col;		// �F
	float m_Base;			// �
	float m_fHeight;		// ����	
	CGauge* m_pGauge;		// �Q�[�W�ւ̃|�C���^
	bool m_bUse;			// �g�p���Ă��邩
	int m_nCntReset;		// ���Z�b�g�����܂ł̎��ԃJ�E���g	
	CObject2D* m_pObj2D;	// 2D�I�u�W�F�N�g�ւ̃|�C���^
};
#endif
