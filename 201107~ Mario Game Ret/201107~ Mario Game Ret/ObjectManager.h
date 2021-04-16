#pragma once

#include "value.h"

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	static CObjectManager* m_pInst;

public:
	static CObjectManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CObjectManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	//���� ���� �ϴ� ���� �ƴ� �ش� Ÿ���� ����ϰ��� �Ҷ�
	//���漱���� ���� ���� �ִ�.
	class CPlayer* m_pPlayer;
	class CBullet* m_pBullet[BULLET_COUNT_MAX];

public:
	class CPlayer* GetPlayer()
	{
		return m_pPlayer;
	}

public:
	bool Init();
};
