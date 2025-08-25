//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _CLICK_H_
#define _CLICK_H_

#include "main.h"
#include "object2D.h"

#define CLICK_SIZE_X (250)
#define CLICK_SIZE_Y (50)

//�I�u�W�F�N�g2D�N���X
class CClick:public CObject2D
{
public:

	//�����o�֐�
	CClick(int nPriority = 9);
	~CClick();

	static CClick* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	//�ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu

	bool m_bUse;
};

#endif