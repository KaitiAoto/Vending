//==============================================
//
// ���b�V�����\������[MeshSphere.h]
// Author:kaiti
//
//==============================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

#include "main.h"
#include "object.h"

//�}�N����`
#define MESHSPHEREVTX_X (20)
#define MESHSPHEREVTX_Z (20)

// ���_�� = (��+1) * (�c+1)
#define MAXSPHERE_VTX ((MESHSPHEREVTX_X + 1) * (MESHSPHEREVTX_Z + 1))

// �C���f�b�N�X���i�g���C�A���O���X�g���b�v�p�j
#define SPHERE_STRIP_COUNT ((MESHSPHEREVTX_X + 1) * 2 + 2)
#define SPHERE_STRIP_TOTAL (MESHSPHEREVTX_Z)
#define SPHEREINDEX_NO (SPHERE_STRIP_COUNT * SPHERE_STRIP_TOTAL * 2)  // ���ʕ��܂ލő吔

#define MESHSPHERE_SIZE (150.0f)

class CMeshSphere :public CObject
{
public:
	//���
	typedef enum
	{
		TYPE_IN = 0,
		TYPE_OUT,
		TYPE_BOTHSIDES,
		TYPE_HALF_TOP,
		TYPE_HALF_BOTTOM,
		TYPE_MAX
	}TYPE;


	CMeshSphere();
	~CMeshSphere();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshSphere* Create(const char* pFilename,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col, TYPE type);
	void SetUse(bool bUse) { m_bUse = bUse; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_nIdxTex;

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;

	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_rot;//����
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X

	TYPE m_type;
	bool m_bUse;
};

#endif