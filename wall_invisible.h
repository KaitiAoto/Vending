//==============================
//
// �����ȕ�[wall_invisible.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _WALL_INVISIBLE_H_
#define _WALL_INVISIBLE_H_

// �C���N���[�h
#include "main.h"
#include "object3D.h"

// �����ȕǃN���X
class CInvisibleWall:public CObject3D
{
public:

	// �����o�֐�
	CInvisibleWall(int nPriority = 1);
	~CInvisibleWall();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize();
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	// �ÓI�����o�֐�
	static CInvisibleWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXCOLOR m_col;		// �F
	bool m_bUse;			// �g�p���Ă��邩
	bool m_bDraw;			// �`�悷�邩
	int m_nIdxTex;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
	float m_fWidth;			// ����
	float m_fHeight;		// ����
};

#endif