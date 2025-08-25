//============================
//
// ���f���\������[model.h]
// Author:kaiti
//
//============================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

class CMotion;

#define MAX_PARTS (13)//�p�[�c�̍ő吔
#define NUM_MODEL (13)

class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel* Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

	void SetParent(CModel* pModel) { m_pParent = pModel; }
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetOffSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_Offsetpos = pos, m_Offsetrot = rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetOffPos(D3DXVECTOR3 pos) { m_Offsetpos = pos; };
	void SetOffRot(D3DXVECTOR3 rot) { m_Offsetrot = rot; };
	D3DXVECTOR3 SetSize(void);
	void SetColorChange(bool bUse) { m_bColorChange = bUse; }
	void SetColor(D3DXCOLOR col) { m_forcedColor = col; }

	static void Load(const char* pFilename, CModel** model, int& outNumModel);

private:
	LPD3DXMESH m_pMesh;			//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;			//�}�e���A���̐�

	D3DXVECTOR3 m_pos;			//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_Offsetpos;	//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_Offsetrot;	//����

	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	int* m_nIdxTex;				//�e�N�X�`���C���f�b�N�X�ւ̃|�C���^
	CModel* m_pParent;

	D3DXCOLOR m_forcedColor;

	bool m_bColorChange;
};

#endif
