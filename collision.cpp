//==============================
//
// �����蔻��[collision.cpp]
// Author:kaiti
//
//==============================
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
//==================
// �R���X�g���N�^
//==================
CCollision::CCollision()
{
}
//================
// �f�X�g���N�^
//================
CCollision::~CCollision()
{
}

//========================================================================
// 
// ������Ƃ鑊��̎�ނ𒲂ׂ鏈��(�ǂ�ȃI�u�W�F�N�g�Ƃ̔�����Ƃ邩)
// 
//========================================================================
//=========================
// �G�T�C�h�Ƃ̓����蔻��
//=========================
bool CCollision::ToEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::TYPE mytype, D3DXVECTOR3& outNormal)
{
	bool bColl = false;

	CObject* pObj = CObject::GetTop(PRIORITY_ENEMYBASE);
	while (pObj != NULL)
	{
		CObject* pObjNext = pObj->GetNext();
		CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
		switch (type)
		{
		case CObject::TYPE_ENEMY_BASE:
			//�I�u�W�F�N�g���G�Ȃ�
			bColl = EnemyBase(pObj, pos, rot, size, mytype, outNormal);
			break;

		default:
			break;
		}
		if (bColl == true)
		{
			return bColl;
		}	

		pObj = pObjNext;
	}	

	return bColl;
}
//=================================
// �v���C���[�T�C�h�Ƃ̓����蔻��
//=================================
bool CCollision::ToPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy* pEnemy)
{
	bool bColl = false;

	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = CObject::GetTop(nCnt);
		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
			switch (type)
			{
			case CObject::TYPE_PLAYER:
				//�I�u�W�F�N�g���v���C���[�Ȃ�
				bColl = Player(pObj, pos, size);
				break;
			case CObject::TYPE_BULLET:
				bColl = PlayerBullet(pObj, pos, size, pEnemy);
				break;
			case CObject::TYPE_GIMMICK:

				break;
			default:
				break;
			}
			if (bColl == true)
			{
				return bColl;
			}

			pObj = pObjNext;
		}
	}

	return bColl;
}
//=================================
// ���̋@�Ƃ̓����蔻��
//=================================
bool CCollision::ToVender(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::TYPE mytype, D3DXVECTOR3& outNormal)
{
	bool bColl = false;

	CObject* pObj = CObject::GetTop(PRIORITY_VENDER);
	while (pObj != NULL)
	{
		CObject* pObjNext = pObj->GetNext();
		CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
		switch (type)
		{
		case CObject::TYPE_VENDER:
			bColl = Vender(pObj, pos,rot, size * 2.0f, mytype, outNormal);
			break;

		default:
			break;
		}
		if (bColl == true)
		{
			return bColl;
		}

		pObj = pObjNext;
	}
	
	return bColl;
}

bool CCollision::ToStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3& outNormal)
{
	bool bColl = false;

	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = CObject::GetTop(nCnt);
		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
			switch (type)
			{
			case CObject::TYPE_STAGE:
				//�I�u�W�F�N�g���v���C���[�Ȃ�
				bColl = Stage(pObj, pos, rot, size, outNormal);
				break;
			case CObject::TYPE_WALL:
				bColl = InvisibleWall(pObj, pos, rot, size, outNormal);
				break;

			default:
				break;
			}
			if (bColl == true)
			{
				return bColl;
			}
			pObj = pObjNext;
		}
	}

	return bColl;
}

bool CCollision::ToGimmick(D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject::TYPE mytype)
{
	bool bColl = false;

	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = CObject::GetTop(nCnt);
		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
			switch (type)
			{
			case CObject::TYPE_GIMMICK:
				//�I�u�W�F�N�g���v���C���[�Ȃ�
				bColl = Gimmick(pObj, pos, size, mytype);
				break;
			case CObject::TYPE_ITEM:
				bColl = Item(pObj, pos, size, mytype);
				break;

			default:
				break;
			}
			if (bColl == true)
			{
				return bColl;
			}
			pObj = pObjNext;
		}
	}
	return bColl;
}

bool CCollision::ToStart(D3DXVECTOR3 pos, CObject::TYPE mytype)
{
	bool bColl = false;

	CObject* pObj = CObject::GetTop(PRIORITY_PLAYER);
	while (pObj != NULL)
	{
		CObject* pObjNext = pObj->GetNext();
		CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
		switch (type)
		{
		case CObject::TYPE_PLAYER:
			//�I�u�W�F�N�g���v���C���[�Ȃ�
			bColl = Start(pObj, pos, mytype);
			break;
		default:
			break;
		}
		if (bColl == true)
		{
			return bColl;
		}

		pObj = pObjNext;
	}

	return bColl;
}

bool CCollision::EnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	bool bColl = false;
	CObject* pObj = CObject::GetTop(PRIORITY_PLAYER);
	while (pObj != NULL)
	{
		CObject* pObjNext = pObj->GetNext();
		CObject::TYPE type = pObj->GetObjType();//�^�C�v�擾
		switch (type)
		{
		case CObject::TYPE_PLAYER:
		{
			CPlayer* pPlayer = (CPlayer*)pObj;
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//�ʒu�擾
			D3DXVECTOR3 Playersize = pPlayer->GetSize();

			bColl = Radius(pos, size, PlayerPos, Playersize);
			if (bColl == true)
			{//����������
				D3DXVECTOR3 move = PlayerPos - pos;
				D3DXVECTOR3 HitPos = PlayerPos + move;

				pPlayer->SetTargetPos(HitPos);
				pPlayer->Hit(1);
			}
			break;
		}
		default:
			break;
		}
		if (bColl == true)
		{
			return bColl;
		}

		pObj = pObjNext;
	}
	return bColl;
}

//===================================================
// 
// ��ޕʂ̔���Ɋւ��鏈��(���Ƃ̔�����Ƃ邩)
// 
//===================================================
//=======================
// �G���_�Ƃ̓����蔻��
//=======================
bool CCollision::EnemyBase(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::TYPE mytype, D3DXVECTOR3& outNormal)
{
	CEnemyBase* pEnemyBase = (CEnemyBase*)pObj;
	D3DXVECTOR3 EnemyPos = pEnemyBase->GetPos();//�ʒu�擾
	D3DXVECTOR3 Enemysize = pEnemyBase->GetSize();
	D3DXVECTOR3 EnemyRot = pEnemyBase->GetRot();
	bool bColl = false;
	bool bRespawn = false;

	bColl = OBB(pos, rot, size, EnemyPos, EnemyRot, Enemysize, outNormal);
	//CollisionModel(pos, size, EnemyPos, Enemysize);
	if (bColl == true)
	{//����������
		//ModelOn(pos, size, EnemyPos, Enemysize);
		if (mytype == CObject::TYPE_BULLET)
		{
			pEnemyBase->Hit(BULLET_ATTACK);
		}
	}

	if (mytype == CObject::TYPE_PLAYER)
	{
		bRespawn = Radius(pos, size, EnemyPos, Enemysize * 5);
		pEnemyBase->SetRespawn(bRespawn);
	}

	return bColl;
}
//===============================
// �G�ƃv���C���[�Ƃ̔���
//===============================
bool CCollision::Player(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer* pPlayer = (CPlayer*)pObj;
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//�ʒu�擾
	D3DXVECTOR3 Playersize = pPlayer->GetSize();

	bool bColl = Radius(pos, size, PlayerPos, Playersize);
	if (bColl == true)
	{//����������
		if (pPlayer->GetState() != pPlayer->STATE_HIT)
		{
			pPlayer->Hit(1);
		}
	}

	return bColl;
}
//=======================
// �G�ƒe�̔���
//=======================
bool CCollision::PlayerBullet(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size, CEnemy* pEnemy)
{
	bool bColl = false;
	CBullet* pBullet = (CBullet*)pObj;//�e�擾
	if (pBullet->GetUser() == CBullet::USER_PLAYER)
	{
		D3DXVECTOR3 BulletPos = pBullet->GetPos();//�ʒu�擾
		D3DXVECTOR3 Bulletsize = pBullet->GetSize();//�T�C�Y�擾
		CBullet::TYPE BulletType = pBullet->GetType();//�e�̃^�C�v�擾
		bool bUse = pBullet->GetUse();
		//�����擾
		CMatchUp* pMatchup = CGame::GetMatchup();

		CEnemy::TYPE type = pEnemy->GetType();//�G�̃^�C�v�擾
		if (bUse == true)
		{
			//���ł̔���
			bColl = Radius(pos, size, BulletPos, Bulletsize);
			if (bColl == true)
			{//����������
				//�e�ƓG�̑����𒲂ׂ�
				int nAttack = pMatchup->Check(BulletType, type);
				//�G�Ƀ_���[�W
				pEnemy->Hit(nAttack);
				//�e������
				pBullet->SetUse(false);
			}
		}
	}
	return bColl;
}
//============================
// ���̋@�Ƃ̓����蔻��
//============================
bool CCollision::Vender(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::TYPE mytype, D3DXVECTOR3& outNormal)
{
	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	CVender* pVender = (CVender*)pObj;

	//
	CRestock* pRestock = pVender->GetpRestock();

	D3DXVECTOR3 VenderPos = pVender->GetPos();//�ʒu�擾
	D3DXVECTOR3 VenderRot = pVender->GetRot();//�ʒu�擾
	D3DXVECTOR3 Vendersize = pVender->GetSize();

	bool bCOLL = OBB(pos, rot, size, VenderPos, VenderRot, Vendersize, outNormal);;//���f��

	if (mytype == CObject::TYPE_PLAYER)
	{
		bool bColl = Cylinder(pos, size, VenderPos, Vendersize);//����
		if (bColl == true)
		{//����������
			//���g��[
			int nRestock = pVender->GetRestock();
			//��ސݒ�
			CBullet::TYPE type = pVender->GetType();

			if (pRestock != nullptr)
			{
				int nCntContents = pPlayer->GetContents();
				if (nCntContents <= 0 || type == pPlayer->GetMyBullet())
				{//���g�O
					bool bUse = pVender->GetUse();
					if (bUse == true)
					{
						pRestock->SetUse(true);
						pRestock->Set(nRestock, type, pVender);
					}
					else
					{
						pRestock->SetUse(false);
					}
				}
				else
				{
					pRestock->SetUse(false);
				}
			}
		}
		else if (bColl == false)
		{
			pRestock->SetUse(false);
		}
	}

	if (bCOLL == true)
	{
		//ModelOn(pos, size, VenderPos, Vendersize);
	}

	return bCOLL;
}
//=========================
// �X�e�[�W���f���Ƃ̔���
//=========================
bool CCollision::Stage(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3& outNormal)
{
	CStage* pEnemyBase = (CStage*)pObj;
	D3DXVECTOR3 EnemyPos = pEnemyBase->GetPos();//�ʒu�擾
	D3DXVECTOR3 Enemysize = pEnemyBase->GetSize();
	D3DXVECTOR3 EnemyRot = pEnemyBase->GetRot();
	bool bColl = false;

	bColl = OBB(pos, rot, size, EnemyPos, EnemyRot, Enemysize, outNormal);
	if (bColl == true)
	{//����������
		//ModelOn(pos, size, EnemyPos, Enemysize);
	}
	return bColl;
}
//===================
// �����ǂƂ̔���
//===================
bool CCollision::InvisibleWall(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXVECTOR3& outNormal)
{
	CInvisibleWall* pWall = (CInvisibleWall*)pObj;
	D3DXVECTOR3 WallPos = pWall->GetPos();//�ʒu�擾
	D3DXVECTOR3 WallRot = pWall->GetRot();//�ʒu�擾
	D3DXVECTOR3 wallSize = pWall->GetSize();

	return OBB(pos, rot, size, WallPos, WallRot, wallSize, outNormal);
}
//======================
// �M�~�b�N�Ƃ̔���
//======================
bool CCollision::Gimmick(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject::TYPE mytype)
{
	CGimmick* pGimmick = (CGimmick*)pObj;
	D3DXVECTOR3 GimmickPos = pGimmick->GetPos();//�ʒu�擾
	D3DXVECTOR3 Gimmicksize = pGimmick->GetSize();
	D3DXMATRIX GimmickMtx = pGimmick->GetMtx();
	D3DXVECTOR3 GimmickRot = pGimmick->GetRot();
	bool bColl = false;

	float fRadius = max(size.x, max(size.y, size.z)) * 1.0f;
	bColl = SphereToOBB(pos, fRadius, GimmickPos, Gimmicksize, GimmickMtx);

	if (bColl == true)
	{//����������
		if (mytype == CObject::TYPE_PLAYER)
		{
			CPlayer* pPlayer = CGame::GetPlayer();

			if (pPlayer->GetState() != pPlayer->STATE_HIT)
			{
				CParticle::Create(GimmickPos, pPlayer->GetRot(), D3DCOLOR_RGBA(255, 1, 1, 255), 30, 5, CParticle::TYPE_NONE);
				pPlayer->Hit(5);
			}
		}
		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_CAR);
	}
	return bColl;
}

bool CCollision::Start(CObject* pObj, D3DXVECTOR3 pos, CObject::TYPE mytype)
{
	bool bColl = false;

	if (mytype == CObject::TYPE_START)
	{
		CPlayer* pPlayer = (CPlayer*)pObj;
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();//�ʒu�擾
		D3DXVECTOR3 PlayerRot = pPlayer->GetRot();
		D3DXVECTOR3 Playersize = pPlayer->GetSize();
		D3DXMATRIX PlayerMtx = pPlayer->GetMtx();

		if (PlayerPos.x >= pos.x)
		{
			bColl = true;
		}

		if (bColl == true)
		{//����������
			pPlayer->SetPosOffSet(PlayerPos);
			pPlayer->ClearContents();

			CGame::GetMap()->GetMapPlayer()->SetUse(true);
		}
	}
	return bColl;
}

bool CCollision::Item(CObject* pObj, D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject::TYPE mytype)
{
	bool bColl = false;

	if (mytype == CObject::TYPE_PLAYER)
	{
		CItem* pItem = (CItem*)pObj;//�e�擾
		D3DXVECTOR3 ItemPos = pItem->GetPos();//�ʒu�擾
		D3DXVECTOR3 Itemsize = pItem->GetSize();//�T�C�Y�擾
		bool bUse = pItem->GetUse();

		if (bUse == true)
		{
			//���ł̔���
			bColl = Radius(pos, size, ItemPos, Itemsize);
			if (bColl == true)
			{
				pItem->Bonus();
			}
		}
	}
	return bColl;
}


//===================================================
// 
// �������Ă��邩�𒲂ׂ鏈��(�ǂ�������Ƃ邩)
// 
//===================================================
//===================
// ���f�����m�̔���
//===================
bool CCollision::Model(D3DXVECTOR3 pos0, D3DXVECTOR3 size0, D3DXVECTOR3 pos1, D3DXVECTOR3 size1)
{
	if (pos0.x >= pos1.x - size1.x / 2		//��
		&& pos0.x <= pos1.x + size1.x / 2	//�E
		&& pos0.y + size0.y >= pos1.y		//��
		&& pos0.y <= pos1.y + size1.y		//��
		&& pos0.z >= pos1.z - size1.z / 2	//��O
		&& pos0.z <= pos1.z + size1.z / 2)	//��
	{//����������
		return true;
	}

	return false;
}
//===================
// �����m�̔���
//===================
bool CCollision::Radius(D3DXVECTOR3 pos0, D3DXVECTOR3 size0, D3DXVECTOR3 pos1, D3DXVECTOR3 size1)
{
	//����
	float fDistance = (((pos1.x - pos0.x) * (pos1.x - pos0.x))
		+ ((pos1.y - pos0.y) * (pos1.y - pos0.y))
		+ ((pos1.z - pos0.z) * (pos1.z - pos0.z)));

	//���ꂼ��̔��a���T�C�Y����Z�o
	float radius0 = max(size0.x, max(size0.y, size0.z)) * 0.5f;
	float radius1 = max(size1.x, max(size1.y, size1.z)) * 0.5f;

	//���a
	float RADIUS = (radius0 + radius1) * (radius0 + radius1);

	if (fDistance <= RADIUS)
	{
		return true;
	}
	return false;
}
//=============
// �ǂƂ̔���
//=============
bool CCollision::Wall(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 rot1, float fWidth)
{
	D3DXVECTOR3 aPos[2];
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;

	// �ǂ̗��[���Z�o�iXZ ���ʁj
	aPos[0].x = pos1.x - cosf(rot1.y) * fWidth;
	aPos[0].y = 0.0f;
	aPos[0].z = pos1.z + sinf(rot1.y) * fWidth;

	aPos[1].x = pos1.x + cosf(rot1.y) * fWidth;
	aPos[1].y = 0.0f;
	aPos[1].z = pos1.z - sinf(rot1.y) * fWidth;

	D3DXVECTOR3 posXZ = pos0;
	posXZ.y = 0.0f;

	// �ǃx�N�g���ƑΏۈʒu�x�N�g���iXZ���ʂ̂݁j
	vecA = aPos[1] - aPos[0];
	vecB = posXZ - aPos[0];

	// �O�ςō��E����i2D�N���X�ρj
	float fvec = (vecA.z * vecB.x) - (vecA.x * vecB.z);

	// ���e�ɂ�鋗���`�F�b�N
	float lenA = D3DXVec3Length(&vecA);
	float dot = D3DXVec3Dot(&vecA, &vecB);
	float projLen = dot / lenA;

	// ���e���ǂ͈͓̔��ɂ��邩
	if (projLen < 0.0f || projLen > lenA)
	{
		return false; // �͈͊O
	}

	// �����i���ʁj�ɂ��邩�ǂ���
	if (fvec < 0)
	{
		return true;
	}
	return false;
}

bool CCollision::Cylinder(D3DXVECTOR3 pos0, D3DXVECTOR3 size0, D3DXVECTOR3 pos1, D3DXVECTOR3 size1)
{
	//����
	float fDistance = (((pos1.x - pos0.x) * (pos1.x - pos0.x))
			   		 + ((pos1.z - pos0.z) * (pos1.z - pos0.z)));

	//���ꂼ��̔��a���T�C�Y����Z�o
	float radius0 = max(size0.x, max(size0.y, size0.z)) * 0.5f;
	float radius1 = max(size1.x, max(size1.y, size1.z)) * 0.5f;

	//���a
	float RADIUS = (radius0 + radius1) * (radius0 + radius1);

	if (fDistance <= RADIUS)
	{
		return true;
	}
	return false;
}


//===================================================
// 
// OBB�n�̏���
// 
//===================================================

bool CCollision::OBB(D3DXVECTOR3 pos0, D3DXVECTOR3 rot0, D3DXVECTOR3 size0, D3DXVECTOR3 pos1, D3DXVECTOR3 rot1, D3DXVECTOR3 size1, D3DXVECTOR3& outNormal)
{
	// ���[���h�s��𐶐��i��]�ƈʒu�������j
	D3DXMATRIX rot0Mtx, rot1Mtx, trans0Mtx, trans1Mtx;
	D3DXMatrixRotationYawPitchRoll(&rot0Mtx, rot0.y, rot0.x, rot0.z);
	D3DXMatrixRotationYawPitchRoll(&rot1Mtx, rot1.y, rot1.x, rot1.z);
	D3DXMatrixTranslation(&trans0Mtx, pos0.x, pos0.y, pos0.z);
	D3DXMatrixTranslation(&trans1Mtx, pos1.x, pos1.y, pos1.z);

	D3DXMATRIX world0 = rot0Mtx * trans0Mtx;
	D3DXMATRIX world1 = rot1Mtx * trans1Mtx;

	// OBB���x�N�g�������[���h�s�񂩂�擾
	D3DXVECTOR3 axes0[3] = {
		D3DXVECTOR3(world0._11, world0._12, world0._13),
		D3DXVECTOR3(world0._21, world0._22, world0._23),
		D3DXVECTOR3(world0._31, world0._32, world0._33),
	};
	D3DXVECTOR3 axes1[3] = {
		D3DXVECTOR3(world1._11, world1._12, world1._13),
		D3DXVECTOR3(world1._21, world1._22, world1._23),
		D3DXVECTOR3(world1._31, world1._32, world1._33),
	};

	for (int i = 0; i < 3; i++) {
		D3DXVec3Normalize(&axes0[i], &axes0[i]);
		D3DXVec3Normalize(&axes1[i], &axes1[i]);
	}

	D3DXVECTOR3 T = pos1 - pos0;

	// �ŏ��y�l�g���[�V��������T��
	float minPenetration = FLT_MAX;
	D3DXVECTOR3 minAxis = { 0, 1, 0 }; // �f�t�H���g�@���i������j

	auto tryAxis = [&](const D3DXVECTOR3& axis) -> bool {
		if (D3DXVec3LengthSq(&axis) < 1e-6f) return true; // �����Ȏ�
		D3DXVECTOR3 normAxis = axis;
		D3DXVec3Normalize(&normAxis, &normAxis);

		float penetration;
		if (!OverlapOnAxis(T, normAxis, axes0, size0, axes1, size1, penetration)) return false;

		if (penetration < minPenetration) {
			minPenetration = penetration;
			minAxis = normAxis;
		}
		return true;
	};


	// �e���`�F�b�N
	for (int i = 0; i < 3; i++) {
		if (!tryAxis(axes0[i])) return false;
		if (!tryAxis(axes1[i])) return false;
	}

	// �������`�F�b�N
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			D3DXVECTOR3 cross;
			D3DXVec3Cross(&cross, &axes0[i], &axes1[j]);
			if (!tryAxis(cross)) return false;
		}
	}

	outNormal = minAxis;
	return true;
}
bool CCollision::OverlapOnAxis(const D3DXVECTOR3& T,const D3DXVECTOR3& axis,
							   const D3DXVECTOR3 axes0[3], const D3DXVECTOR3& size0,
							   const D3DXVECTOR3 axes1[3], const D3DXVECTOR3& size1, float& outPenetration)
{
	float r0 =
		fabsf(D3DXVec3Dot(&axis, &axes0[0])) * size0.x / 2 +
		fabsf(D3DXVec3Dot(&axis, &axes0[1])) * size0.y / 2 +
		fabsf(D3DXVec3Dot(&axis, &axes0[2])) * size0.z / 2;

	float r1 =
		fabsf(D3DXVec3Dot(&axis, &axes1[0])) * size1.x / 2 +
		fabsf(D3DXVec3Dot(&axis, &axes1[1])) * size1.y / 2 +
		fabsf(D3DXVec3Dot(&axis, &axes1[2])) * size1.z / 2;

	float distance = fabsf(D3DXVec3Dot(&T, &axis));

	float penetration = (r0 + r1) - distance;
	outPenetration = penetration;
	return penetration > 0;
	//return distance <= (r0 + r1);
}

bool CCollision::SphereToOBB(const D3DXVECTOR3& sphereCenter, float sphereRadius, const D3DXVECTOR3& obbCenter, const D3DXVECTOR3& obbSize, const D3DXMATRIX& obbRotation)
{
	// OBB�̊e���i���[�J����x, y, z�j
	D3DXVECTOR3 obbX(obbRotation._11, obbRotation._12, obbRotation._13);
	D3DXVECTOR3 obbY(obbRotation._21, obbRotation._22, obbRotation._23);
	D3DXVECTOR3 obbZ(obbRotation._31, obbRotation._32, obbRotation._33);

	// ���̒��S����OBB���S�ւ̃x�N�g��
	D3DXVECTOR3 d = sphereCenter - obbCenter;

	// �ŋߐړ_���������iOBB��ԏ�j
	D3DXVECTOR3 closest = obbCenter;

	// �e���ɂ��ď���
	for (int i = 0; i < 3; ++i) {
		D3DXVECTOR3 axis;
		float halfLength = 0.0f;

		if (i == 0) { axis = obbX; halfLength = obbSize.x / 2.0f; }
		if (i == 1) { axis = obbY; halfLength = obbSize.y / 2.0f; }
		if (i == 2) { axis = obbZ; halfLength = obbSize.z / 2.0f; }

		// �����S�����ɓ��e
		float dist = D3DXVec3Dot(&d, &axis);

		// -halfLength �` +halfLength �ɃN�����v
		if (dist > halfLength) dist = halfLength;
		if (dist < -halfLength) dist = -halfLength;

		// �ŋߐړ_�ɂ��̎������𑫂�
		closest += axis * dist;
	}

	// �����S�ƍŋߐړ_�̋������v�Z
	D3DXVECTOR3 diff = sphereCenter - closest;
	float distanceSq = D3DXVec3LengthSq(&diff);

	// ���a�ȉ��Ȃ�Փ�
	return distanceSq <= (sphereRadius * sphereRadius);
}