//================================
//
// �^�C�g������[title.h]
// Author : Kaiti Aoto
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _TITLE_H_
#define _TITLE_H_

// �C���N���[�h
#include "main.h"
#include "scene.h"
#include "object.h"
#include "title_logo.h"

// �O���錾
class CScene;
class CLoadStage;

// �^�C�g���N���X
class CTitle:public CScene
{
public:
	// �����o�֐�
	CTitle();
	~CTitle();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTitleLogo* GetLogo(void) { return m_pLogo; }

private:

	// �ÓI�����o�ϐ�
	static CLoadStage* m_pStage;	// �X�e�[�W�ւ̃|�C���^
	static CTitleLogo* m_pLogo;		//���S�ւ̃|�C���^
};

#endif