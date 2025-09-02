//============================
//
// ���f���\������[objectX.h]
// Author:kaiti
//
//============================

// ��d�C���N���[�h�h�~
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

// �C���N���[�h�h�~
#include "main.h"
#include "object.h"

// �I�u�W�F�N�gX�N���X
class CObjectX :public CObject
{
public:

	// �����o�֐�
	CObjectX(int nPriority = 3);
	// ���z�֐�
	~CObjectX();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	// �擾
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }

	// �ÓI�����o�֐�
	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	// �ÓI�����o�ϐ�
	LPD3DXMESH m_pMesh;			// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	int* m_nIdxTex;				// �e�N�X�`���C���f�b�N�X�ւ̃|�C���^
};

#endif
