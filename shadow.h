//==============================
//
// �e[shadow.h]
// Author:kaiti
//
//==============================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

//�I�u�W�F�N�g2D�N���X
class CShadow:public CObject3D
{
public:

	//�����o�֐�
	CShadow(int nPriority = 2);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
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
};

#endif