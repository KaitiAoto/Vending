//=====================================
//
// �r���{�[�h�\������[billboard.h]
// Author : Kaiti Aoto
//
//=====================================

// ��d�C���N���[�h�h�~
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �}�N����`
#define BILLBOARD_SIZE (20)

// �r���{�[�h�N���X
class CObjectBillboard:public CObject
{
public:
	// �����o�֐�
	CObjectBillboard(int nPriority = 3);
	// ���z�֐�
	~CObjectBillboard();
	HRESULT Init(const char* pTexName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	virtual void Draw(void);

	// �ݒ�
	void SetSize(float fRadius);
	void SetColor(D3DXCOLOR col);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void Set();
	// �ÓI�����o�֐�
	static CObjectBillboard* Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	static CObjectBillboard* Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nPriority);
	
private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
};

#endif
