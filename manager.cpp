//================================
//
// �}�l�[�W���[����[manager.cpp]
// Author:kaiti
//
//================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "debugproc.h"
//�ÓI�����o�ϐ�
CRenderer* CManager::m_pRenderer = NULL;
CInputKey* CManager::m_pInputKey = NULL;
CInputMouse* CManager::m_pInputMouse = NULL;
CInputPad* CManager::m_pInputPad = NULL;
CTexture* CManager::m_pTex = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CSound* CManager::m_pSound = NULL;
CDebugProc* CManager::m_pDebug = NULL;
CScene* CManager::m_pScene = NULL;
CFade* CManager::m_pFade = NULL;

bool CManager::m_bPause = false;
//==================
// �R���X�g���N�^
//==================
CManager::CManager()
{
	
}
//================
// �f�X�g���N�^
//================
CManager::~CManager()
{
}
//=======================
// �}�l�[�W���[�̏�����
//=======================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�S�|�C���^����
	CreatePointa(hInstance, hWnd, bWindow);

	//SetMode(CScene::MODE_TITLE);

	return S_OK;
}
//================
// �|�C���^����
//================
HRESULT CManager::CreatePointa(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[����
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}
	//�����_���[�̏�����
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	//�L�[���͐���
	if (m_pInputKey == NULL)
	{
		m_pInputKey = new CInputKey;
	}
	//�L�[���͂̏�����
	if (FAILED(m_pInputKey->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�L�[���͐���
	if (m_pInputMouse == NULL)
	{
		m_pInputMouse = new CInputMouse;
	}
	//�L�[���͂̏�����
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�L�[���͐���
	if (m_pInputPad == NULL)
	{
		m_pInputPad = new CInputPad;
	}
	//�L�[���͂̏�����
	if (FAILED(m_pInputPad->Init(hInstance)))
	{
		return E_FAIL;
	}

	//�T�E���h����
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}
	//�T�E���h�̏�����
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	//�J��������
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//���C�g����
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//�e�N�X�`������
	if (m_pTex == NULL)
	{
		m_pTex = new CTexture;
		m_pTex->Load();
	}

	//�f�o�b�O����
	if (m_pDebug == NULL)
	{
		m_pDebug = new CDebugProc;
		m_pDebug->Init();
	}

	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CScene::MODE_TITLE);
		m_pFade->Set(CScene::MODE_TITLE);
	}

	return S_OK;
}
//
//
//
void CManager::SetMode(CScene::MODE mode)
{
	if (mode != CScene::MODE_RANKING)
	{
		m_pSound->Stop();
	}

	//�X�R�A�ۑ�
	int nScore = 0;

	if (m_pScene != nullptr)
	{
		if (mode == CScene::MODE_RESULT && m_pScene->GetMode() == CScene::MODE_GAME)
		{//���݂��Q�[���Ŏ������U���g
			nScore = CGame::GetScoreMana()->GetScore();//�X�R�A�ۑ�
		}
		else if (mode == CScene::MODE_RANKING && m_pScene->GetMode() == CScene::MODE_RESULT)
		{//���݂��Q�[���Ŏ������U���g
			nScore = CResult::GetScoreMana()->GetScore();//�X�R�A�ۑ�
		}

		m_pScene->Uninit();
	}

	CObject::ReleaseAll();


	m_pScene = CScene::Create(mode);
	
	if (mode == CScene::MODE_RANKING)
	{//NULL�`�F�b�N�����݂����U���g
		CRanking::GetRankMana()->Set(nScore);
	}
	
	m_pScene->Init();

	if (m_pScene != nullptr && m_pScene->GetMode() == CScene::MODE_RESULT)
	{//NULL�`�F�b�N�����݂����U���g
		//�X�R�A���
		CResult::GetScoreMana()->Set(nScore);
	}
	//else if (m_pScene != nullptr && m_pScene->GetMode() == CScene::MODE_RANKING)
	//{//NULL�`�F�b�N�����݂����U���g
	//	CRanking::GetRankMana()->Set(nScore);
	//}

	//�J����������
	m_pCamera->Init();
}
//=============
// �I������
//=============
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�j��
	CObject::ReleaseAll();
	//�S�|�C���^�j��
	ReleasePointa();
}
//===============
// �|�C���^�j��
//===============
void CManager::ReleasePointa(void)
{
	//�����_���[�j���i�Ō�ɐ������ꂽ���̂��ŏ��ɔj���j
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�L�[���͔j��
	if (m_pInputKey != NULL)
	{
		m_pInputKey->Uninit();
		delete m_pInputKey;
		m_pInputKey = NULL;
	}
	//�L�[���͔j��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
	//�L�[���͔j��
	if (m_pInputPad != NULL)
	{
		m_pInputPad->Uninit();
		delete m_pInputPad;
		m_pInputPad = NULL;
	}

	//�T�E���h�j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//���C�g�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//�J�����j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�e�N�X�`���j��
	if (m_pTex != NULL)
	{
		m_pTex->Unload();
		delete m_pTex;
		m_pTex = NULL;
	}
	//�f�o�b�O
	if (m_pDebug != NULL)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

}
//=======================
// �}�l�[�W���[�̍X�V
//=======================
void CManager::Update(void)
{
	//CalculateFPS();

	if (m_bPause == false)
	{
		//�����_���[�X�V
		m_pRenderer->Update();

		if (m_pCamera != nullptr)
		{
			if (m_pScene != nullptr)
			{
				if (m_pScene->GetMode() == CScene::MODE_GAME)
				{
					//�J�����X�V
					m_pCamera->Update();
				}
				else
				{
					m_pCamera->UpdateMenu();
				}
			}
		}
	}
	else
	{
		CPause* pPause = CGame::GetPause();
		pPause->Update();
	}

	if (m_pInputKey != nullptr)
	{
		//�L�[���͍X�V
		m_pInputKey->Update();
	}
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}
	if (m_pInputPad != nullptr)
	{
		m_pInputPad->Update();
	}

	m_pFade->Update();
}
//=======================
// �}�l�[�W���[�̕`��
//=======================
void CManager::Draw(void)
{
	//�����_���[�`��
	m_pRenderer->Draw();

	//DrawFPS();
}
