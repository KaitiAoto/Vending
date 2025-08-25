//=====================================
//
// �r���{�[�h�\������[billboard.h]
// Author:kaiti
//
//=====================================
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

#include "main.h"
#include "object.h"

#define BILLBOARD_SIZE (20)

//�N���X
class CObjectBillboard:public CObject
{
public:
	//�����o�֐�
	CObjectBillboard(int nPriority = 3);
	//���z�֐�
	~CObjectBillboard();
	HRESULT Init(const char* pTexName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	virtual void Draw(void);

	static CObjectBillboard* Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

	void SetSize(float fRadius);
	void SetColor(D3DXCOLOR col);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;

	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_rot;//����
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	int m_nIdxTex;
};

#endif
