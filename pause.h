//================================
//
// �|�[�Y[pause.h]
// Author:kaiti
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _PAUSE_H_
#define _PAUSE_H_

// �C���N���[�h
#include "main.h"
#include "scene.h"
#include "object2D.h"
#include "pause_manager.h"
#include "click.h"

// �|�[�Y�N���X
class CPause
{
public:
	// �����o�֐�
	CPause();
	~CPause();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	// �ÓI�����o�֐�
	static CPause* Create();

private:
	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���

	// �ÓI�����o�ϐ�
	static CPauseMana* m_pPauseMana;	// �|�[�Y�}�l�[�W���[�ւ̃|�C���^
	static CClick* m_pClick;			// ����L�[�t�h�ւ̃|�C���^
};

#endif