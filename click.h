//==============================
//
// ����L�[UI[click.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _CLICK_H_
#define _CLICK_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// �}�N����`
#define CLICK_SIZE_X (250)
#define CLICK_SIZE_Y (50)

// ����L�[UI�N���X
class CClick:public CObject2D
{
public:
	//�����o�֐�
	CClick(int nPriority = 10);
	~CClick();

	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	//�ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CClick* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	void Blink(void);
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	bool m_bUse;		// �L����������
	int m_nCntTime;		// �J�E���^�[
};

#endif