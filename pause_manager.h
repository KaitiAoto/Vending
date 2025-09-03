//=======================================
//
// �|�[�Y�}�l�[�W���[[pause_manager.h]
// Author : Kaiti Aoto
//
//=======================================

// ��d�C���N���[�h�h�~
#ifndef _PAUSE_MANAGER_H_
#define _PAUSE_MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "pause_select.h"

// �}�N����`
#define P_SELECT_X (250)
#define P_SELECT_Y (100)

// �|�[�Y�}�l�[�W���[�N���X
class CPauseMana
{
public:
	// �I����
	typedef enum
	{
		SELECT_CONTNUE = 0,
		SELECT_RESTART,
		SELECT_END,
		SELECT_MAX
	}SELECT;

	// �����o�֐�
	CPauseMana();
	~CPauseMana();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//�ݒ菈��

	// �ÓI�����o�֐�
	static CPauseMana* Create(D3DXVECTOR3 pos);
private:
	void Select(void);
	
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// �p�x
	CPauseSelect* m_pSelect[SELECT_MAX];	// �|�[�Y�I���ւ̃|�C���^
	CObject2D* m_pBack;						// �w�i�ւ̃|�C���^
	int m_Select;							// �I�����Ă������
};

#endif