//===================================
//
// �^�C�g���I��[title_select.h]
// Author:kaiti
//
//====================================
#ifndef _PAUSE_MANAGER_H_
#define _PAUSE_MANAGER_H_

#include "main.h"
#include "object.h"
#include "pause_select.h"

#define P_SELECT_X (250)
#define P_SELECT_Y (100)

//�I�u�W�F�N�g2D�N���X
class CPauseMana
{
public:
	typedef enum
	{
		SELECT_CONTNUE = 0,
		SELECT_RESTART,
		SELECT_END,
		SELECT_MAX
	}SELECT;


	//�����o�֐�
	CPauseMana();
	~CPauseMana();

	static CPauseMana* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//�ݒ菈��
private:
	void Select(void);
	
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x

	CPauseSelect* m_pSelect[SELECT_MAX];
	CObject2D* m_pBack;

	int m_Select;
};

#endif