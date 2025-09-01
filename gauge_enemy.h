//==============================
//
//  �GHP�Q�[�W����[gauge_enemy.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_ENEMY_H_
#define _GAUGE_ENEMY_H_

#include "main.h"
#include "gauge_billboard.h"

// �GHP�Q�[�W�N���X
class CEnemyGauge :CObject
{
public:

	// �����o�֐�
	CEnemyGauge(int nPriority = 6);
	~CEnemyGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	
	// �ݒ�
	void SetBase(float nBase) { m_Base = nBase; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
	void SetRate(float rate) { m_rate = rate; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXCOLOR m_col;			// �F
	float m_Base;				// �
	float m_fHeight;			// ����
	float m_rate;				// ���[�g
	CGaugeBillboard* m_pGauge;	// �r���{�[�h�Q�[�W�ւ̃|�C���^
	bool m_bDraw;				// �`�悷�邩
};
#endif
