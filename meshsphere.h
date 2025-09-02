//==============================================
//
// ���b�V�����\������[meshsphere.h]
// Author:kaiti
//
//==============================================

// ��d�C���N���[�h�h�~
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define MESHSPHEREVTX_X (20)
#define MESHSPHEREVTX_Z (20)
#define MAXSPHERE_VTX ((MESHSPHEREVTX_X + 1) * (MESHSPHEREVTX_Z + 1))	// ���_��
#define SPHERE_STRIP_COUNT ((MESHSPHEREVTX_X + 1) * 2 + 2)				// �C���f�b�N�X��
#define SPHERE_STRIP_TOTAL (MESHSPHEREVTX_Z)
#define SPHEREINDEX_NO (SPHERE_STRIP_COUNT * SPHERE_STRIP_TOTAL * 2)	// ���ʕ��܂ލő吔
#define MESHSPHERE_SIZE (150.0f)

// ���b�V�����N���X
class CMeshSphere :public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_IN = 0,
		TYPE_OUT,
		TYPE_BOTHSIDES,
		TYPE_HALF_TOP,
		TYPE_HALF_BOTTOM,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// �ݒ�
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CMeshSphere* Create(const char* pFilename,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);

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