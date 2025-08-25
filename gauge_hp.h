//==============================
//
//  HP�Q�[�W����[Gauge_hp.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_HP_H_
#define _GAUGE_HP_H_

#include"main.h"
#include "gauge.h"

//�I�u�W�F�N�g2D�N���X
class CHpGauge :CObject
{
public:

	//�����o�֐�
	CHpGauge(int nPriority = 7);
	~CHpGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CHpGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;
	float m_rate;

	CGauge* m_pGauge;
};
#endif
