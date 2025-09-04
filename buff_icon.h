//==============================
//
// �o�t�A�C�R��[buff_icon.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _BUFF_ICON_H_
#define _BUFF_ICON_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"
#include "buff.h"

// �}�N����`
#define BUFF_X (300)
#define BUFF_Y (100)

// �o�t�A�C�R���N���X
class CBuffIcon:public CObject2D
{
public:
	// ���
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	// �����o�֐�
	CBuffIcon(int nPriority = 8);
	~CBuffIcon();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	// �ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CBuffIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posStay;	// �ҋ@�ʒu
	D3DXVECTOR3 m_posOut;	// ��ʊO�ʒu
	D3DXVECTOR3 m_rot;		// �p�x

	bool m_bUse;			// �g�p���Ă��邩
	bool m_bClear;			// �N���A���Ă��邩
	int m_nIdxTex;			// �e�N�X�`���̃C���f�b�N�X�ԍ�
	CBuff::TYPE m_type;		// ���
	STATE m_state;			// ���
	const char* m_apFileName[CBuff::TYPE_MAX];// �e�N�X�`����
};

#endif