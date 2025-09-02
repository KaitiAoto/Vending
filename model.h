//============================
//
// ���f���\������[model.h]
// Author:kaiti
//
//============================

// ��d�C���N���[�h�h�~
#ifndef _MODEL_H_
#define _MODEL_H_

// �C���N���[�h
#include "main.h"

// �O���錾
class CMotion;

// �}�N����`
#define MAX_PARTS (13)	// �p�[�c�̍ő吔
#define NUM_MODEL (13)

// ���f���N���X
class CModel
{
public:
	// �����o�֐�
	CModel();
	~CModel();

	HRESULT Init(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	// �ݒ�
	void SetParent(CModel* pModel) { m_pParent = pModel; }
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	void SetOffPos(D3DXVECTOR3 pos) { m_Offsetpos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetOffRot(D3DXVECTOR3 rot) { m_Offsetrot = rot; };
	void SetOffSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_Offsetpos = pos, m_Offsetrot = rot; }
	void SetColorChange(bool bUse) { m_bColorChange = bUse; }
	void SetColor(D3DXCOLOR col) { m_forcedColor = col; }
	D3DXVECTOR3 SetSize(void);

	// �ÓI�����o�֐�
	static CModel* Create(const char* pFilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static void Load(const char* pFilename, CModel** model, int& outNumModel);

private:
	// �����o�ϐ�
	LPD3DXMESH m_pMesh;			// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_Offsetpos;	// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_Offsetrot;	// ����(�I�t�Z�b�g)
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXCOLOR m_forcedColor;	// �F
	CModel* m_pParent;			// �e���f��
	int* m_nIdxTex;				// �e�N�X�`���C���f�b�N�X�ւ̃|�C���^
	bool m_bColorChange;		// �F��ς��邩�ǂ���
};

#endif
