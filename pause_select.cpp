//=================================
//
// �|�[�Y�I��[pause_select.cpp]
// Author : Kaiti Aoto
//
//=================================
#include "pause_select.h"
#include "renderer.h"
#include "manager.h"

//==================
// �R���X�g���N�^
//==================
CPauseSelect::CPauseSelect(int nPriority) :CObject2D(nPriority)
{
}
//================
// �f�X�g���N�^
//================
CPauseSelect::~CPauseSelect()
{
}
//===========
// ��������
//===========
CPauseSelect* CPauseSelect::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CPauseSelect* pScore = new CPauseSelect;
	//������
	pScore->Init(pTexName, pos, fWidth, fHeight);

	return pScore;
}
//===============
// ����������
//===============
HRESULT CPauseSelect::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//������
	CObject2D::Init(pTexName, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);

	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CPauseSelect::Uninit(void)
{
	CObject::Release();
}
//============
// �X�V����
//============
void CPauseSelect::Update(void)
{

}
//============
// �`�揈��
//============
void CPauseSelect::Draw(void)
{
	if (CManager::GetPause() == true)
	{
		CObject2D::Draw();
	}
}