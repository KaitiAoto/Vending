//==============================================
//
// ���b�V���~���\������[meshcylinder.h]
// Author:kaiti
//
//==============================================

// ��d�C���N���[�h�h�~
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define MESHCYLINDERVTX_X (8)	// ��
#define MESHCYLINDERVTX_Z (2)	// �c
#define MAXCYLINDER_VTX ((MESHCYLINDERVTX_X + 1) * (MESHCYLINDERVTX_Z + 1))								// ���_��
#define CYLINDERPOLYGON_NO (MESHCYLINDERVTX_X * MESHCYLINDERVTX_Z * 2 + (MESHCYLINDERVTX_Z - 1) * 4)	// �|���S����
#define CYLINDERINDEX_NO ((MESHCYLINDERVTX_X + 1) * 2 * MESHCYLINDERVTX_Z + (MESHCYLINDERVTX_Z - 1) * 2)// �C���f�b�N�X��
#define MESHCYLINDER_SIZE (150.0f)

// ���b�V���~���N���X
class CMeshCylinder :public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_IN = 0,
		TYPE_OUT,
		TYPE_BOTHSIDES,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CMeshCylinder();
	~CMeshCylinder();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ݒ�
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CMeshCylinder* Create(const char* pFilename,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	TYPE m_type;						// ��� 
	bool m_bUse;						// �g�p���Ă��邩
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif