//================================
//
// �V�[������[scene.cpp]
// Author:kaiti
//
//================================
#include "scene.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"

//==================
// �R���X�g���N�^
//==================
CScene::CScene(MODE mode):CObject(0)
{
	m_mode = mode;
}

//==================
// �f�X�g���N�^
//==================
CScene::~CScene()
{

}
//============
// ��������
//============
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;
	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;
		break;
	case MODE_GAME:
		pScene = new CGame;
		break;
	case MODE_RESULT:
		pScene = new CResult;
		break;
	case MODE_RANKING:
		pScene = new CRanking;
		break;

	default:
		break;
	}

	//if (pScene != nullptr)
	//{
	//	pScene->Init();
	//}

	return pScene;
}
