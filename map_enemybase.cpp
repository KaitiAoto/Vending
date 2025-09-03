//==============================
//
// ��[����[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "map_enemybase.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CMapEnemyBase::CMapEnemyBase(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CMapEnemyBase::~CMapEnemyBase()
{
}
//===========
// ��������
//===========
CMapEnemyBase* CMapEnemyBase::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMapEnemyBase* pObject2D;
	pObject2D = new CMapEnemyBase;
	//������
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CMapEnemyBase::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;
	m_bUse = true;

	CObject2D::Init("data\\TEXTURE\\conveni02.jpg", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);

	// �~�j�}�b�v�̏��
	const float miniMapCenterX = CGame::GetMap()->GetPos().x;
	const float miniMapCenterY = CGame::GetMap()->GetPos().y;
	const float miniMapW = CGame::GetMap()->GetWidth();
	const float miniMapH = CGame::GetMap()->GetHeight();

	// ���[���h���W�𐳋K��
	const float worldSizeX = 2000.0f;
	const float worldSizeZ = 2000.0f;

	float normX = (pos.x + worldSizeX / 2.0f) / worldSizeX;
	float normZ = (pos.z + worldSizeZ / 2.0f) / worldSizeZ;

	// ���S����ɕ`��
	float iconX = miniMapCenterX - miniMapW / 2.0f + normX * miniMapW;
	float iconY = miniMapCenterY - miniMapH / 2.0f + (1.0f - normZ) * miniMapH;

	m_pos = D3DXVECTOR3(iconX, iconY, 0.0f);

	CObject2D::SetPos(m_pos);


	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CMapEnemyBase::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CMapEnemyBase::Update(void)
{

}
//============
// �`�揈��
//============
void CMapEnemyBase::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
