//====================================
//
// �}�b�v�v���C���[[map_player.h]
// Author:kaiti
//
//====================================

// ��d�C���N���[�h�h�~
#ifndef _MAP_PLAYER_H_
#define _MAP_PLAYER_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"
#include "bullet.h"

// �}�b�v�v���C���[�N���X
class CMapPlayer:public CObject2D
{
public:

	// �����o�֐�
	CMapPlayer(int nPriority = 8);
	~CMapPlayer();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}
	//�ݒ菈��
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CMapPlayer* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	int m_nIdxTex;		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	bool m_bUse;		// �g�p���Ă��邩
};

#endif