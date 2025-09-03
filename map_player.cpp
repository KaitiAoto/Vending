//==============================
//
// ��[����[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "map_player.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CMapPlayer::CMapPlayer(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CMapPlayer::~CMapPlayer()
{
}
//===========
// ��������
//===========
CMapPlayer* CMapPlayer::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMapPlayer* pObject2D;
	pObject2D = new CMapPlayer;
	//������
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CMapPlayer::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;
	m_bUse = true;

	CObject2D::Init("data\\TEXTURE\\build007.png", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);


	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CMapPlayer::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CMapPlayer::Update(void)
{
	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	// ���[���h���W���擾
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// �~�j�}�b�v�̏��
	const float miniMapCenterX = CGame::GetMap()->GetPos().x;
	const float miniMapCenterY = CGame::GetMap()->GetPos().y;
	const float miniMapW = CGame::GetMap()->GetWidth();   // 200
	const float miniMapH = CGame::GetMap()->GetHeight();  // 200

	// ���[���h���W�𐳋K�� (-950�`+950 �� 0.0�`1.0)
	const float worldSizeX = 1900.0f;
	const float worldSizeZ = 1900.0f;

	float normX = (playerPos.x + worldSizeX / 2.0f) / worldSizeX;  // 0.0�`1.0
	float normZ = (playerPos.z + worldSizeZ / 2.0f) / worldSizeZ;  // 0.0�`1.0

	// ���S����ɕ`��
	float iconX = miniMapCenterX - miniMapW / 2.0f + normX * miniMapW;
	float iconY = miniMapCenterY - miniMapH / 2.0f + (1.0f - normZ) * miniMapH;

	m_pos = D3DXVECTOR3(iconX, iconY, 0.0f);

	CObject2D::SetPos(m_pos);
}
//============
// �`�揈��
//============
void CMapPlayer::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
