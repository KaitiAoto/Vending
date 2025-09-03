//================================
//
// �V�[������[scene.h]
// Author : Kaiti Aoto
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _SCENE_H_
#define _SCENE_H_

// �C���N���[�h
#include "main.h"
#include "object.h"

// �V�[���N���A
class CScene:public CObject
{
public:
	// ���[�h
	typedef enum
	{
		MODE_TITLE=0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,

		MODE_END,
		MODE_MAX
	}MODE;

	// �����o�֐�
	CScene(MODE mode);
	// �������z�֐�
	virtual ~CScene() = 0;
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// �擾
	MODE GetMode(void) { return  m_mode; }

	// �ÓI�����o�֐�
	static CScene* Create(MODE mode);

private:
	// �����o�ϐ�
	MODE m_mode;
};


#endif