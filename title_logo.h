//=====================================
//
// �^�C�g�����S[title_logo.h]
// Author : Kaiti Aoto
//
//=====================================

// ��d�C���N���[�h�h�~
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// �}�N����`
#define LOGO_SIZE_X (550)
#define LOGO_SIZE_Y (350)

// �^�C�g�����S�N���X
class CTitleLogo:public CObject2D
{
public:

	// �����o�֐�
	CTitleLogo(int nPriority = 8);
	~CTitleLogo();

	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetStop(void) { return m_bStop; }
	// �ݒ菈��

	// �ÓI�����o�֐�
	static CTitleLogo* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posStay;	// �~�܂�ʒu
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_move;		// �ړ���
	bool m_bUse;			// �g�p���Ă��邩
	bool m_bStop;			// �~�܂��Ă��邩
	int m_nTime;			// �~�܂��Ă��鎞��
	int m_AnimCnt;			// �A�j���J�E���g
};

#endif