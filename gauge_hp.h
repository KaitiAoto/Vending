//==============================
//
//  HP�Q�[�W����[gauge_hp.h]
//  Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _GAUGE_HP_H_
#define _GAUGE_HP_H_

// �C���N���[�h
#include"main.h"
#include "gauge.h"

// HP�Q�[�W�N���X
class CHpGauge :CObject
{
public:
	// �����o�֐�
	CHpGauge(int nPriority = 7);
	~CHpGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CHpGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	float m_Base;		// �
	float m_fHeight;	// ����
	float m_rate;		// ���[�g

	CGauge* m_pGauge;	// �Q�[�W�ւ̃|�C���^
};
#endif
