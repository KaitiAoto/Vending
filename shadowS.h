//==============================
//
// �e[shadow.h]
// Author:kaiti
//
//==============================
#ifndef _SHADOWS_H_
#define _SHADOWS_H_

#include "main.h"
#include "objectX.h"
#include "object2D.h"

//�I�u�W�F�N�g2D�N���X
class CShadowS:public CObjectX
{
public:

	//�����o�֐�
	CShadowS(int nPriority = 4);
	~CShadowS();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_pos = pos; m_rot = rot; }
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//�p�x
	float m_fLength;		//�Ίp���̒���
	//float m_fAngle;			//�Ίp���̊p�x
	float m_fRadius;
	bool m_bUse;			//�g�p���Ă��邩
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	int m_nIdxTex;
	D3DXCOLOR m_col;

	CObject2D* m_pObj2D;
};

#endif