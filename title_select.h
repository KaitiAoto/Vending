//===================================
//
// �^�C�g���I��[title_select.h]
// Author:kaiti
//
//====================================
#ifndef _TITLE_SELECT_H_
#define _TITLE_SELECT_H_

#include "main.h"
#include "object.h"
#include "object2D.h"

#define T_SELECT_X (250)
#define T_SELECT_Y (100)

//�I�u�W�F�N�g2D�N���X
class CTitleSelect:public CObject
{
public:
	typedef enum
	{
		SELECT_GAME = 0,
		SELECT_END,
		SELECT_MAX
	}SELECT;


	//�����o�֐�
	CTitleSelect(int nPriority = 7);
	~CTitleSelect();

	static CTitleSelect* Create(D3DXVECTOR3 pos);
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

	CObject2D* m_pSelect[SELECT_MAX];
	CObject2D* m_pCursor;

	int m_Select;
};

#endif