//==============================
//
//  モーション処理[motion.h]
//  Author:kaiti
//
//==============================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

#define MAX_KEY (300)//キーの最大数

//クラス
class CMotion
{
public:
	//モーションの種類
	typedef enum
	{
		TYPE_NEUTRAL = 0,
		TYPE_MOVE,
		TYPE_ACTION,
		TYPE_JUMP,
		TYPE_LANDING,

		TYPE_MAX,
	}TYPE;

	//キーの構造体
	typedef struct
	{
		float fPosX;
		float fPosY;
		float fPosZ;

		float fRotX;
		float fRotY;
		float fRotZ;
	}KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[MAX_KEY];
	}MOTION_INFO;

	//メンバ関数
	CMotion();
	//仮想関数
	~CMotion();

	void StartBlend(TYPE from, TYPE to, int nBlendFrame);

	void Update(const int nMaxPart, CModel** pModel);

	static CMotion* Load(const char* pFilename);

	D3DXVECTOR3 LerpVec3(const D3DXVECTOR3& a, const D3DXVECTOR3& b, float t);
	D3DXVECTOR3 LerpKey(TYPE type, int part, int keyA, int keyB, float t, bool isPos);

	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }
private:
	MOTION_INFO m_aMotionInfo[TYPE_MAX];//モーション情報
	int m_nNumMotion;					//モーションの総数
	TYPE m_type;						//モーションの種類
	bool m_bLoop;						//ループするかどうか
	int m_nKey;							//現在のキーNo
	int m_nCntMotion;					//モーションのカウンター

	bool m_bBlend;						// ブレンド中か
	float m_fBlendRate;					// ブレンド進行 (0.0～1.0)
	int m_nBlendFrame;					// ブレンドにかけるフレーム数
	TYPE m_typeFrom;					// 元のモーション
	TYPE m_typeTo;						// 移行先モーション

	int m_nKeyFrom;
	int m_nKeyTo;
	int m_nCntFrom;
	int m_nCntTo;
};

#endif 