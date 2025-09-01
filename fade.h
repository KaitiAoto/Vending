//================================
//
// �t�F�[�h[fade.h]
// Author:kaiti
//
//================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "object2D.h"

// �O���錾
class CScene;

// �t�F�[�h�N���X
class CFade
{
public:
	// ���
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	}FADE;

	// �����o�֐�
	CFade();
	~CFade();
	void Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade* Create(CScene::MODE modeNext);

	// �擾
	FADE GetFade(void) { return m_fade; }

	// �ݒ�
	void Set(CScene::MODE modeNext);
	void SetColor(D3DXCOLOR col);
private:
	// �����o�ϐ�
	FADE m_fade;						// ���
	D3DXCOLOR m_col;					// �F
	CScene::MODE m_modeNext;			// ���̃V�[��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���
};

#endif