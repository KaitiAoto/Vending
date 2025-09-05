//==============================
//
// 相性[matchup.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "sell.h"
#include "manager.h"
#include "camera.h"

//
int CSell::m_nCntSellTime = 0;

//==================
// コンストラクタ
//==================
CSell::CSell()
{
}
//================
// デストラクタ
//================
CSell::~CSell()
{

}

void CSell::Update(void)
{
	const int nDecreaseTime = 30;

	m_nCntSellTime++;

	if (m_nCntSellTime >= nDecreaseTime)
	{
		int nNumBase = CEnemyBase::GetNum();

		int nTarget = rand() % nNumBase;

		int nCntBase = 0;

		CObject* pObj = CObject::GetTop(PRIORITY_ENEMYBASE);
		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();
			if (pObj->GetObjType() == CObject::TYPE_ENEMY_BASE)
			{
				if (nTarget == nCntBase)
				{
					CEnemyBase* pBase = (CEnemyBase*)pObj;
					pBase->SoldOut();
					break;
				}
				nCntBase++;
			}
			pObj = pObjNext;
		}

		m_nCntSellTime = 0;
	}

}
