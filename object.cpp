//==============================
//
// �I�u�W�F�N�g[object.cpp]
// Author:kaiti
//
//==============================
#include "object.h"
#include "manager.h"
#include "camera.h"
//�ÓI�����o�ϐ�
int CObject::m_nNumAll = 0;
CObject* CObject::m_apTop[NUM_PRIORITY] = {};
CObject* CObject::m_apCur[NUM_PRIORITY] = {};

//==================
// �R���X�g���N�^
//==================
CObject::CObject(int nPriority)
{
	if (m_apTop[nPriority] == NULL)
	{//�������擪�Ȃ�
		m_apTop[nPriority] = this;
		m_pPrev = NULL;
	}
	else
	{//����ȊO�Ȃ�
		m_pPrev = m_apCur[nPriority];
		m_pPrev->m_pNext = this;
	}

	m_apCur[nPriority] = this;//�������Ō���ɂ���
	m_pNext = NULL;//�����̎��N���A

	m_nNumAll++;			//�������Z
	m_nPriority = nPriority;//�`�揇�ۑ�
	m_bDeath = false;
}
//================
// �f�X�g���N�^
//================
CObject::~CObject()
{
}
//=======================
// �S�I�u�W�F�N�g�̔j��
//=======================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = m_apTop[nCnt];
		while (pObj != NULL)
		{// pObj���m�t�k�k����Ȃ�
			CObject* pObjNext = pObj->m_pNext;//���g�̎���ۑ�
			
			pObj->Uninit();
			if (pObj->m_bDeath == true)
			{
				delete pObj;
				pObj = nullptr;
			}

			pObj = pObjNext;//���̃I�u�W�F�N�g����
		}
		//�擪�ƍŌ�����N���A
		m_apTop[nCnt] = nullptr;
		m_apCur[nCnt] = nullptr;
	}
	m_nNumAll = 0;
}
//=======================
// �S�I�u�W�F�N�g�̍X�V
//=======================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = m_apTop[nCnt];
		while (pObj != NULL)
		{// pObj���m�t�k�k����Ȃ�
			CObject* pObjNext = pObj->m_pNext;//���g�̎���ۑ�

			//�X�V			
			pObj->Update();
		
			pObj = pObjNext;//���̃I�u�W�F�N�g����
		}
	}

	DeathCheck();
}
//=======================
// �S�I�u�W�F�N�g�̕`��
//=======================
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();
	pCamera->Set();

	//CFade* pFade = CManager::GetFade();
	//CFade::FADE fade = pFade->GetFade();
	CDebugProc* pDegub = CManager::GetDebug();
	pDegub->Print("�I�u�W�F�N�g���F%d", m_nNumAll);

	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = m_apTop[nCnt];
		while (pObj != NULL)
		{// pObj���m�t�k�k����Ȃ�
			CObject* pObjNext = pObj->m_pNext;//���g�̎���ۑ�
			//�`��
			pObj->Draw();

			pObj = pObjNext;//���̃I�u�W�F�N�g����
		}
	}
}
//=====================
// �I�u�W�F�N�g�̔j��
//=====================
void CObject::Release(void)
{ 
	m_bDeath = true;


	//int nPriority = m_nPriority;
	//
	//if (this == m_apTop[nPriority])
	//{//�������擪�Ȃ�
	//	m_apTop[nPriority] = m_pNext;//�擪�����g�̎�(m_pNext)��
	//	if (m_apTop[nPriority])
	//	{
	//		m_apTop[nPriority]->m_pPrev = NULL;
	//	}
	//}
	//else if (this == m_apCur[nPriority])
	//{//�������Ō���Ȃ�
	//	m_apCur[nPriority] = m_pPrev;//�Ō�������g�̑O(m_pPrev)��
	//	if (m_apCur[nPriority])
	//	{
	//		m_apCur[nPriority]->m_pNext = NULL;//�Ō���̎���NULL��
	//	}
	//}
	//else
	//{//����ȊO�̒��Ԓn�_�Ȃ�
	//	m_pPrev->m_pNext = m_pNext;//�����̑O�̎��̃I�u�W�F�N�g(this->m_pPrev->m_pNext)�������̎�(this->m_pNext)�ɂ���
	//	m_pNext->m_pPrev = m_pPrev;//�����̎��̑O�̃I�u�W�F�N�g(this->m_pNext->m_pPrev)�������̑O(this->m_pPrev)�ɂ���
	//}
	//
	//m_pNext = nullptr;
	//m_pPrev = nullptr;
	//
	//m_nNumAll--;
	//
	//delete this;
}
//===========================
// ���S�t���O�`�F�b�N����
//===========================
void CObject::DeathCheck(void)
{
	//���S�t���O�`�F�b�N
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObj = m_apTop[nCnt];
		while (pObj != NULL)
		{// pObj���m�t�k�k����Ȃ�
			CObject* pObjNext = pObj->m_pNext;//���g�̎���ۑ�

			if (pObj->m_bDeath == true)
			{
				if (pObj == m_apTop[nCnt])
				{//�������擪�Ȃ�
					m_apTop[nCnt] = pObj->m_pNext;//�擪�����g�̎�(m_pNext)��
					if (m_apTop[nCnt])
					{
						m_apTop[nCnt]->m_pPrev = NULL;
					}
				}
				else if (pObj == m_apCur[nCnt])
				{//�������Ō���Ȃ�
					m_apCur[nCnt] = pObj->m_pPrev;//�Ō�������g�̑O(m_pPrev)��
					if (m_apCur[nCnt])
					{
						m_apCur[nCnt]->m_pNext = NULL;//�Ō���̎���NULL��
					}
				}
				else
				{//����ȊO�̒��Ԓn�_�Ȃ�
					pObj->m_pPrev->m_pNext = pObj->m_pNext;//�����̑O�̎��̃I�u�W�F�N�g(this->m_pPrev->m_pNext)�������̎�(this->m_pNext)�ɂ���
					pObj->m_pNext->m_pPrev = pObj->m_pPrev;//�����̎��̑O�̃I�u�W�F�N�g(this->m_pNext->m_pPrev)�������̑O(this->m_pPrev)�ɂ���
				}

				pObj->m_pNext = nullptr;
				pObj->m_pPrev = nullptr;

				m_nNumAll--;

				//�폜
				delete pObj;
			}

			pObj = pObjNext;//���̃I�u�W�F�N�g����
		}
	}
}
