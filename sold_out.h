//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _SOLD_OUT_H_
#define _SOLD_OUT_H_

#include "main.h"
#include "object2D.h"

//�I�u�W�F�N�g2D�N���X
class CSoldOut:public CObject2D
{
public:

	//�����o�֐�
	CSoldOut(int nPriority = 9);
	~CSoldOut();

	static CSoldOut* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	static bool GetUse(void) { return m_bUse; }

	//�ݒ菈��
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }
private:

	//�����o�ϐ�
	static bool m_bUse;
	D3DXCOLOR m_col;
};

#endif