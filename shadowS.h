//==============================
//
// �X�e���V���e[shadowS.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _SHADOWS_H_
#define _SHADOWS_H_

// �C���N���[�h
#include "main.h"
#include "objectX.h"
#include "object2D.h"

// �X�e���V���e�N���X
class CShadowS:public CObjectX
{
public:

	// �����o�֐�
	CShadowS(int nPriority = 5);
	~CShadowS();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_pos = pos; m_rot = rot; }

	// �ÓI�����o�֐�
	static CShadowS* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);

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
	CObject2D* m_pObj2D;	// 2D�I�u�W�F�N�g�ւ̃|�C���^
};

#endif