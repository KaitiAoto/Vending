//=================================
//
// ポーズ選択[pause_select.cpp]
// Author : Kaiti Aoto
//
//=================================
#include "pause_select.h"
#include "renderer.h"
#include "manager.h"

//==================
// コンストラクタ
//==================
CPauseSelect::CPauseSelect(int nPriority) :CObject2D(nPriority)
{
}
//================
// デストラクタ
//================
CPauseSelect::~CPauseSelect()
{
}
//===========
// 生成処理
//===========
CPauseSelect* CPauseSelect::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CPauseSelect* pScore = new CPauseSelect;
	//初期化
	pScore->Init(pTexName, pos, fWidth, fHeight);

	return pScore;
}
//===============
// 初期化処理
//===============
HRESULT CPauseSelect::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//初期化
	CObject2D::Init(pTexName, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);

	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// 終了処理
//============
void CPauseSelect::Uninit(void)
{
	CObject::Release();
}
//============
// 更新処理
//============
void CPauseSelect::Update(void)
{

}
//============
// 描画処理
//============
void CPauseSelect::Draw(void)
{
	if (CManager::GetPause() == true)
	{
		CObject2D::Draw();
	}
}