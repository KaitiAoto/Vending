//=================================
//
// ポーズ選択[pause_select.h]
// Author:kaiti
//
//=================================
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
#include "object2D.h"

//オブジェクト2Dクラス
class CPauseSelect:public CObject2D
{
public:

	//メンバ関数
	CPauseSelect(int nPriority = 10);
	~CPauseSelect();
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseSelect* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
	//メンバ変数
};

#endif