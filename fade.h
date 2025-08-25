//================================
//
// �^�C�g������[title.h]
// Author:kaiti
//
//================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "object2D.h"

////�}�N����`
//#define GRAVITY (0.2f)

class CScene;

//�}�l�[�W���[�N���X
class CFade
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	//�����o�֐�
	CFade();
	~CFade();
	void Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade* Create(CScene::MODE modeNext);

	FADE GetFade(void) { return m_fade; }

	void Set(CScene::MODE modeNext);
	void SetColor(D3DXCOLOR col);
private:
	FADE m_fade;
	D3DXCOLOR m_col;
	CScene::MODE m_modeNext;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_���

};

#endif