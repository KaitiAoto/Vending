//==============================
//
// �G�t�F�N�g[effect.h]
// Author:kaiti
//
//==============================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "object.h"

#define EFFECT_SIZE (5)
#define EFFECT_LIFE (30)

//�I�u�W�F�N�g2D�N���X
class CEffect:public CObject
{
public:

	//�����o�֐�
	CEffect(int nPriority = 6);
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius, int nPriority);

private:
	void SetSize(float fRadius);
	void SetColor(D3DXCOLOR col);

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//�p�x
	D3DXVECTOR3 m_move;		//�ړ���
	float m_fLength;		//�Ίp���̒���
	float m_fAngle;			//�Ίp���̊p�x
	float m_fRadius;
	bool m_bUse;			//�g�p���Ă��邩
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	int m_nIdxTex;
	D3DXCOLOR m_col;
	int m_nLife;
};

#endif