//===================================
//
// �^�C�g���I��[title_select.h]
// Author:kaiti
//
//====================================

// ��d�C���N���[�h�h�~
#ifndef _TITLE_SELECT_H_
#define _TITLE_SELECT_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "object2D.h"

// �}�N����`
#define T_SELECT_X (250)
#define T_SELECT_Y (100)

// �^�C�g���I���N���X
class CTitleSelect:public CObject
{
public:
	// �I����
	typedef enum
	{
		SELECT_GAME = 0,
		SELECT_END,
		SELECT_MAX
	}SELECT;


	// �����o�֐�
	CTitleSelect(int nPriority = 7);
	~CTitleSelect();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// �ݒ菈��

	// �ÓI�����o�֐�
	static CTitleSelect* Create(D3DXVECTOR3 pos);

private:
	void Select(void);
	
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// �p�x
	CObject2D* m_pSelect[SELECT_MAX];	// �I�����ւ̃|�C���^
	CObject2D* m_pCursor;				// �I���J�[�\���ւ̃|�C���^
	int m_Select;						// �ǂ��I�����Ă��邩
	float m_fAnim[SELECT_MAX];			// �A�j���J�E���g
};

#endif