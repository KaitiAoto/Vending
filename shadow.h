//==============================
//
// �e[shadow.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _SHADOW_H_
#define _SHADOW_H_

// �C���N���[�h
#include "main.h"
#include "object3D.h"

// �e�N���X
class CShadow:public CObject3D
{
public:

	// �����o�֐�
	CShadow(int nPriority = 2);
	~CShadow();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXCOLOR m_col;		// �F
	bool m_bUse;			// �g�p���Ă��邩
	float m_fLength;		// �Ίp���̒���
	float m_fRadius;		// ���a
	int m_nIdxTex;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif