//==============================
//
//  �Q�[�W����[Gauge.h]
//  Author:kaiti
//
//==============================
#ifndef _GAUGE_BILLBOARD_H_
#define _GAUGE_BILLBOARD_H_

#include"main.h"
#include "object.h"

//�N���X
class CGaugeBillboard
{
public:

	//�����o�֐�
	CGaugeBillboard();
	~CGaugeBillboard();
	HRESULT Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGaugeBillboard* Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col);

	void Set();

	void SetBase(float base) { m_Base = base; }
	void SetRate(float rate) { m_rate = rate; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	//�����o�ϐ�
	int m_nIdxTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	D3DXCOLOR m_col;
	float m_Base;
	float m_fHeight;
	float m_fWidth;
	float m_rate;
};
#endif
