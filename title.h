//================================
//
// �^�C�g������[title.h]
// Author:kaiti
//
//================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "title_logo.h"

////�}�N����`
//#define GRAVITY (0.2f)

class CScene;
class CLoadStage;

//�}�l�[�W���[�N���X
class CTitle:public CScene
{
public:
	//�����o�֐�
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleLogo* GetLogo(void) { return m_pLogo; }

private:
	static CLoadStage* m_pStage;
	static CTitleLogo* m_pLogo;
};

#endif