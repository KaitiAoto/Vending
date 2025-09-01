//==============================
//
// �e�A�C�R��[bullet_icon.h]
// Author:kaiti
//
//==============================
#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"
// �}�N����`
#define BULLETICON_SIZE (80)

// �e�A�C�R���N���X
class CBulletIcon:public CObject2D
{
public:

	// �����o�֐�
	CBulletIcon(int nPriority = 7);
	~CBulletIcon();

	static CBulletIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeIcon(CBullet::TYPE type);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}
	// �ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	bool m_bUse;			// �g�p���Ă��邩
	CBullet::TYPE m_type;	// ���
};

#endif