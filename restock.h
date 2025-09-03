//==============================
//
// ��[����[restock.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _RESTOCK_H_
#define _RESTOCK_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"
#include "bullet.h"
#include "vender.h"

// �}�N����`
#define RESTOCK_SIZE (150)

// �I�u�W�F�N�g2D�N���X
class CRestock:public CObject2D
{
public:

	// �����o�֐�
	CRestock(int nPriority = 7);
	~CRestock();

	static CRestock* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	// �ݒ菈��
	void Set(int nRestock, CBullet::TYPE type, CVender* pVender);
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }

private:
	
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// �p�x

	int m_nIdxTex;		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	bool m_bUse;		// �g�p���Ă��邩
};

#endif