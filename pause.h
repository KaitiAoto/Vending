//================================
//
// リザルト処理[result.h]
// Author:kaiti
//
//================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"
#include "object2D.h"
#include "pause_manager.h"
#include "click.h"

//クラス
class CPause
{
public:
	//メンバ関数
	CPause();
	~CPause();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause* Create();

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点情報

	static CPauseMana* m_pPauseMana;
	static CClick* m_pClick;
};

#endif