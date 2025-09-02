//=====================================
//
// ���b�V�����\������[meshfield.h]
// Author:kaiti
//
//=====================================

// ��d�C���N���[�h�h�~
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define MESHVTX_X (15)	// ��
#define MESHVTX_Z (15)	// �c
#define MAX_VTX ((MESHVTX_X + 1) * (MESHVTX_Z + 1))						// ���_��
#define POLYGON_NO (MESHVTX_X * MESHVTX_Z * 2 + (MESHVTX_Z - 1) * 4)	//	�|���S����
#define INDEX_NO ((MESHVTX_X + 1) * 2 * MESHVTX_Z + (MESHVTX_Z - 1) * 2)// �C���f�b�N�X��
#define MESH_SIZE (500.0f)

// ���b�V�����N���X
class CMeshField:public CObject
{
public:

	// �����o�֐�
	CMeshField();
	~CMeshField();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@	
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�

};

#endif