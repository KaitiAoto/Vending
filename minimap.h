//==============================
//
// �~�j�}�b�v[minimap.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

// �C���N���[�h
#include "object.h"
#include "map_player.h"

// �}�b�v�N���X
class CMap:public CObject
{
public:
	// �����o�֐�
	CMap();
	~CMap();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	// �ÓI�����o�֐�
	static CMap* Create(const D3DXVECTOR3 pos, float fWidth, float fHeight);
	// �擾
	static CMapPlayer* GetMapPlayer(void) { return m_pMapPlayer; }

private:
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	float m_fWidth;		// ����
	float m_fHeight;	// ����

	// �ÓI�����o�ϐ�
	static CMapPlayer* m_pMapPlayer;	//�}�b�v�v���C���[�ւ̃|�C���^ 
};

#endif