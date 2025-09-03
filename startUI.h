//==============================
//
// �J�n�t�h[startUI.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _STARTUI_H_
#define _STARTUI_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// �}�N����`
#define STARTUI_SIZE_X (600)
#define STARTUI_SIZE_Y (300)

// �J�n�t�h�N���X
class CStartUI:public CObject2D
{
public:

	// �����o�֐�
	CStartUI(int nPriority = 7);
	~CStartUI();

	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// �ݒ菈��

	// �ÓI�����o�֐�
	static CStartUI* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	void Move(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posStay;	// �ʒu(�~�܂�ꏊ)
	D3DXVECTOR3 m_rot;		// �p�x
	bool m_bStop;			// �~�܂��Ă��邩�ǂ���
	bool m_bUse;			// �g�p���Ă��邩
	int m_nTime;			// �~�܂��Ă��鎞��
};

#endif