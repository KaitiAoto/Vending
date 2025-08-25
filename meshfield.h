//=====================================
//
// ���b�V�����\������[meshfield.h]
// Author:kaiti
//
//=====================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

//�}�N����`
#define MESHVTX_X (15)//��
#define MESHVTX_Z (15)//�c
#define MAX_VTX ((MESHVTX_X + 1) * (MESHVTX_Z + 1))//���_��
#define POLYGON_NO (MESHVTX_X * MESHVTX_Z * 2 + (MESHVTX_Z - 1) * 4)//�|���S����
#define INDEX_NO ((MESHVTX_X + 1) * 2 * MESHVTX_Z + (MESHVTX_Z - 1) * 2)//�C���f�b�N�X��
#define MESH_SIZE (500.0f)

class CMeshField:public CObject
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	int m_nIdxTex;

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;

	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_rot;//����
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X

};

#endif