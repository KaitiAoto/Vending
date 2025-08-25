//==============================
//
// ���̋@[vender.cpp]
// Author:kaiti
//
//==============================
#include "start.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "startUI.h"
//==================
// �R���X�g���N�^
//==================
CStart::CStart(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_mtxWorld = {};

	m_pModel = NULL;

	m_bDraw = true;
}
//================
// �f�X�g���N�^
//================
CStart::~CStart()
{

}
//===========
// ��������
//===========
CStart* CStart::Create(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CStart* pBullet = new CStart;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pFilename, pos, rot)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// ����������
//===============
HRESULT CStart::Init(const char* pFilename, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;

	m_pos.x -= 40.0f;

	//���f������
	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize();

	m_bDraw = true;

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_START);

	return S_OK;
}
//============
// �I������
//============
void CStart::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	CObject::Release();
}
//============
// �X�V����
//============
void CStart::Update(void)
{
	if (m_bDraw == true)
	{
		SetObjType(TYPE_STAGE);
	}
	else if (m_bDraw == false)
	{
		SetObjType(TYPE_START);

		//�����蔻��̃|�C���^�擾
		CCollision* pColl = CGame::GetColl();

		bool bColl = pColl->ToStart(m_pos, TYPE_START);

		if (bColl == true)
		{
			m_bDraw = true;
			m_pos.x -= 40.0f;
			SetObjType(TYPE_STAGE);

			CStartUI::Create("data\\TEXTURE\\game_start00.png", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), STARTUI_SIZE_X, STARTUI_SIZE_Y);

			CSound* pSound = CManager::GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_START);

			CGame::SetMode(CGame::MODE_PLAY);
		}
	}
}
//============
// �`�揈��
//============
void CStart::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bDraw == true)
	{
		m_pModel->SetPos(m_pos);
		//���f���`��
		m_pModel->Draw();
	}
}