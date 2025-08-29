//===================
//
// �X�R�A[score.h]
// Author:kaiti
//
//===================
#include "score.h"
#include "renderer.h"
#include "manager.h"
//�ÓI�����o�ϐ�
int CScore::m_nPriority = 0;

//==================
// �R���X�g���N�^
//==================
CScore::CScore(int nPriority) :CObject(nPriority)
{
	m_nPriority = nPriority;
	m_nIdxTex = 0;
	m_pNumber = nullptr;
}
//================
// �f�X�g���N�^
//================
CScore::~CScore()
{
}
//===========
// ��������
//===========
CScore* CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore* pScore = new CScore;
	//������
	pScore->Init(pos, fWidth, fHeight);

	return pScore;
}
void CScore::SetColor(D3DXCOLOR col)
{
	m_pNumber->SetColor(col);
}
//===============
// ����������
//===============
HRESULT CScore::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//������
	m_pNumber = CNumber::Create("data\\TEXTURE\\number002.png", pos, fWidth, fHeight);
	
	SetObjType(TYPE_SCORE);

	return S_OK;
}
//============
// �I������
//============
void CScore::Uninit(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}
	CObject::Release();
}
//============
// �X�V����
//============
void CScore::Update(void)
{

}
//============
// �`�揈��
//============
void CScore::Draw(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Draw();
	}
}