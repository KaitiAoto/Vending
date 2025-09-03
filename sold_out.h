//==============================
//
// ����؂�\��[sold_out.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _SOLD_OUT_H_
#define _SOLD_OUT_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// ����؂�\���N���X
class CSoldOut:public CObject2D
{
public:

	// �����o�֐�
	CSoldOut(int nPriority = 9);
	~CSoldOut();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	static bool GetUse(void) { return m_bUse; }

	// �ݒ菈��
	void SetColor(D3DXCOLOR col) { m_col = col; m_bUse = true; }

	// �ÓI�����o�֐�
	static CSoldOut* Create(void);
private:

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F

	// �ÓI�����o�ϐ�
	static bool m_bUse;	// �g�p���Ă��邩
};

#endif