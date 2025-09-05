//===================================
//
//  �GHP�Q�[�W����[gauge_enemy.h]
//  Author : Kaiti Aoto
//
//===================================

// ��d�C���N���[�h�h�~
#ifndef _GAUGE_ENEMYBASE_H_
#define _GAUGE_ENEMYBASE_H_

// �C���N���[�h
#include "main.h"
#include "gauge_billboard.h"
#include "objectBillboard.h"
#include "bullet.h"
#include "enemy_base.h"

class CEnemyBase;

// �GHP�Q�[�W�N���X
class CEnemyBaseGauge :CObject
{
public:

	// �����o�֐�
	CEnemyBaseGauge(int nPriority = 7);
	~CEnemyBaseGauge();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, CBullet::TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// �ݒ�
	void SetBase(float nBase) { m_Base = nBase; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
	void SetRate(float rate) { m_rate = rate; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	// �ÓI�����o�֐�
	static CEnemyBaseGauge* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, CBullet::TYPE type, CEnemyBase* pEnemyBase);

private:
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXCOLOR m_col;			// �F
	float m_Base;				// �
	float m_fHeight;			// ����
	float m_rate;				// ���[�g
	CGaugeBillboard* m_pGauge;	// �r���{�[�h�Q�[�W�ւ̃|�C���^
	CObjectBillboard* m_pIcon;	// �r���{�[�h�ւ̃|�C���^
	CEnemyBase* m_pEnemyBase;	// �G���_�ւ̃|�C���^
	bool m_bDraw;				// �`�悷�邩
};
#endif
