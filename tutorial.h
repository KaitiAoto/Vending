//==============================
//
// �`���[�g���A��[tutorial.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"

// �}�N����`
#define TUTORIAL_SIZE (200)

// �`���[�g���A���N���X
class CTutorial:public CObject2D
{
public:
	// ���
	typedef enum
	{
		TYPE_MOVE = 0,
		TYPE_CAMERA,
		TYPE_BULLET,
		TYPE_RESTOCK,
		TYPE_HOLD,
		TYPE_CONTENTS,
		TYPE_MATCHUP,
		TYPE_MAX
	}TYPE;
	// ���
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	// �����o�֐�
	CTutorial(int nPriority = 9);
	~CTutorial();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	TYPE GetType(void) { return m_type; }
	// �ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }
	void SetClear(bool bClear) { m_bClear = bClear; }

	// �ÓI�����o�֐�
	static CTutorial* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	void BackBlink(void);
	void CheckClear(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_posStay;				// �~�܂�ʒu
	D3DXVECTOR3 m_posOut;				// ��ʊO�ʒu
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXCOLOR m_col;					// �F
	TYPE m_type;						// ���
	STATE m_state;						// ���
	CObject2D* m_pBack;					// �w�i�ւ̃|�C���^
	CObject2D* m_pSkip;					// �X�L�b�v�t�h�ւ̃|�C���^
	const char* m_apFileName[TYPE_MAX];	// �e�N�X�`����
	bool m_bUse;						// �g�p���Ă��邩
	bool m_bClear;						// �N���A���Ă��邩
	int m_nIdxTex;						// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nTime;						// �^�C�}�[
	int m_nCntTime;						// �^�C�}�[�J�E���g

};

#endif