//=====================================
//
// ��ʃt���b�V��[screen_flash.h]
// Author:kaiti
//
//=====================================

// ��d�C���N���[�h�h�~
#ifndef _SCREEN_FLASH_H_
#define _SCREEN_FLASH_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// ��ʃt���b�V���N���X
class CScreenFlash:public CObject2D
{
public:

	// �����o�֐�
	CScreenFlash(int nPriority = 9);
	~CScreenFlash();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	
	// �ݒ菈��
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }

	// �ÓI�����o�֐�
	static CScreenFlash* Create(void);

private:

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F
	bool m_bUse;		// �g�p���Ă��邩
};

#endif