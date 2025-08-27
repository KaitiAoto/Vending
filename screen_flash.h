//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _SCREEN_FLASH_H_
#define _SCREEN_FLASH_H_

#include "main.h"
#include "object2D.h"

//�I�u�W�F�N�g2D�N���X
class CScreenFlash:public CObject2D
{
public:

	//�����o�֐�
	CScreenFlash(int nPriority = 9);
	~CScreenFlash();

	static CScreenFlash* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	
	//�ݒ菈��
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }
private:

	//�����o�ϐ�
	bool m_bUse;
	D3DXCOLOR m_col;
};

#endif