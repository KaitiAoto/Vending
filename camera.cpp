//=============================
//
//�@�J��������[camera.cpp]
//�@Author:kaiti
//
//=============================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
//================
// �R���X�g���N�^
//================
CCamera::CCamera(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;

	m_posVOffSet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxProjection = {};
	m_mtxView = {};
}
//================
// �f�X�g���N�^
//================
CCamera::~CCamera()
{
}
//=================
// �J�����̏�����
//=================
HRESULT CCamera::Init(void)
{
	//���_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(-1500.0f, 300.0f, -1200.0f);
	m_posVOffSet = m_posV;
	m_posR = D3DXVECTOR3(-1500.0f, 0.0f, -880.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�p�x

	m_fDistance = sqrtf(((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x))
					  + ((m_posV.y - m_posR.y) * (m_posV.y - m_posR.y))
					  + ((m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)));	//���_�ƒ����_�̋���

	return S_OK;
}
//===================
// �J�����̏I������
//===================
void CCamera::Uninit(void)
{

}
//====================
// �J�����̍X�V����
//====================
void CCamera::Update(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	CDebugProc* pDegub = CManager::GetDebug();

	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();
	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = pPlayer->GetPos();
		D3DXVECTOR3 rot = pPlayer->GetRot();

		//�Ǐ]
		m_posRDest.x = pos.x + sinf(rot.x) * (pos.x - m_posR.x);
		//m_posRDest.y = pos.y;
		m_posRDest.z = pos.z + cosf(rot.z) * (pos.z - m_posR.z);

		m_posVDest.x = pos.x + sinf(m_rot.y - D3DX_PI) * m_fDistance;
		m_posVDest.z = pos.z + cosf(m_rot.y - D3DX_PI) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 0.08f;
		//m_posR.y += (m_posRDest.y - m_posR.y) * 1.0f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.08f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.08f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.08f;
	}

	//�J�����A�b�v
	if (pInputPad->GetTrigger(CInputPad::JOYKEY_R3) == true || pInputMouse->GetTrigger(2) == true)
	{
		m_fDistance -= 100.0f;
		m_posV.y -= 80.0f;
		if (m_posV.y <= 40.0f)
		{
			m_posV.y = 40.0f;
		}

		//��苗���Ō��ɖ߂�
		if (m_fDistance <= 100.0f)
		{
			m_posV.y = m_posVOffSet.y;

			m_fDistance = sqrtf(((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x))
							  + ((m_posV.y - m_posR.y) * (m_posV.y - m_posR.y))
							  + ((m_posV.z - m_posR.z) * (m_posV.z - m_posR.z)));	//���_�ƒ����_�̋���
		}
	}


	//�}�E�X�̍��E�ړ��Ŏ��_����i���x�͓K�X�����j
	if (pInputMouse != nullptr)
	{
		int mouseMoveX = pInputMouse->GetRelX();

		const float sensitivity = 0.0005f; // ���x�����p

		m_rot.y += mouseMoveX * sensitivity;

		int mouseMoveY = pInputMouse->GetRelY();

		const float sensitivityY = 0.05f; // ���x�����p

		m_posV.y += mouseMoveY * sensitivityY;

		if (m_posV.y <= 40.0f)
		{
			m_posV.y = 40.0f;
		}
		else if (m_posV.y >= 700.0f)
		{
			m_posV.y = 700.0f;
		}
	}

	if (pInputPad != nullptr)
	{
		const float sensitivity = 0.05f; // ���x�����p

		const float sensitivityY = 1.0f; // ���x�����p

		float rx = pInputPad->GetRightStickX(); // ��
		float ry = pInputPad->GetRightStickY(); // �c

		// �f�b�h�]�[�������i�킸���ȌX���ɂ��듮��h�~�j
		const float deadZone = 0.2f;
		if (fabsf(rx) > deadZone)
		{
			m_rot.y += rx * sensitivity;
		}
		if (fabsf(ry) > deadZone)
		{
			m_posV.y += ry * sensitivityY;
			
			if (m_posV.y <= 40.0f)
			{
				m_posV.y = 40.0f;
			}
			else if (m_posV.y >= 700.0f)
			{
				m_posV.y = 700.0f;
			}
		}
	}

#ifdef _DEBUG

	//���_�̐���
	if (pInputKey->GetPress(DIK_Q) == true)
	{
		m_rot.y += 0.05f;
	}
	else if (pInputKey->GetPress(DIK_E) == true)
	{
		m_rot.y -= 0.05f;
	}
	//���_�̏㉺
	if (pInputKey->GetPress(DIK_Y) == true)
	{//��
		if (m_posV.y <= 500)
		{
			m_posV.y += 3;
		}
	}
	if (pInputKey->GetPress(DIK_N) == true)
	{//��
		if (m_posV.y >= -500)
		{
			m_posV.y -= 3;
		}
	}
#endif // DEBUG

	//�p�x�̐��K��
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;


	pDegub->Print("�J�����̊p�x�F(%.1f, %.1f, %.1f)", m_rot.x, m_rot.y, m_rot.z);
	pDegub->Print("�J�����̎��_�F(%.1f, %.1f, %.1f)", m_posV.x, m_posV.y, m_posV.z);
	pDegub->Print("���_�ƒ����_�̋����F%.1f", m_fDistance);
}
//
//
//
void CCamera::UpdateMenu(void)
{
	m_fDistance = 800.0f;//

	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posV.y = 200.0f;

	//��]
	m_rot.y += 0.003f;

	//�p�x�̐��K��
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;


	CDebugProc* pDegub = CManager::GetDebug();

	pDegub->Print("�J�����̊p�x�F(%.1f, %.1f, %.1f)", m_rot.x, m_rot.y, m_rot.z);
	pDegub->Print("�J�����̎��_�F(%.1f, %.1f, %.1f)", m_posV.x, m_posV.y, m_posV.z);
	pDegub->Print("���_�ƒ����_�̋����F%.1f", m_fDistance);
}
//================
// �J�����̐ݒ�
//================
void CCamera::Set(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f), //����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //�A�X�y�N�g��
		10.0f,
		5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
