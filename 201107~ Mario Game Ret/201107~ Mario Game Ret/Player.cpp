#include "Player.h"
#include "MapManager.h"
#include "Stage.h"

bool CPlayer::Init()
{
	m_tPos.x = 0;
	m_tPos.y = 8;

	m_bJump = false;
	m_bComplete = false;
	m_iJumpDir = JD_STOP;
	m_iJumpState = 0;
	m_iScore = 0;
	m_bBulletFire = false;

	return true;
}

#define	JUMP_BLOCK_MAX 2

void CPlayer::Update()
{
	CStage* pStage = CMapManager::GetInst()->GetStage();

	//키 입력을 받는다.
	//GetAsyncKeyState 함수는 Win32 API에서 제공되는 키 입력 함수이다.
	//W키를 눌렀을 때 바로 반응하게 하기 위하여 0x8000과 &연산을 하여
	// 눌렀을 경우 true가 나오게 된다.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (pStage->GetBlock(m_tPos.x - 1, m_tPos.y) != SBT_WALL)
		{
			--m_tPos.x;

			if (m_tPos.x < 0)
				m_tPos.x = 0;
		}
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL)
		{
			++m_tPos.x;
			if (m_tPos.x >= 50)
				m_tPos.x = 49;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump)
	{
		m_bJump = true;
		m_iJumpDir = JD_UP;
		m_iJumpState = 0;
	}

	if (m_bJump)
	{
		CStage* pStage = CMapManager::GetInst()->GetStage();
		switch (m_iJumpDir)
		{
		case JD_UP:
			++m_iJumpState;

			if (m_iJumpState > JUMP_BLOCK_MAX)
			{
				m_iJumpState = JUMP_BLOCK_MAX;
				m_iJumpDir = JD_DOWN;
			}
			else if (pStage->GetBlock(m_tPos.x, m_tPos.y - 1) == SBT_WALL)
			{
				--m_iJumpState;

				//벽을 깼을 때 아이템을 랜덤하게 둘 중 하나로 나오게 한다.
				int iRand = rand() % 100;
				STAGE_BLOCK_TYPE eBlockType;

				if (iRand < 90)
					eBlockType = SBT_ITEM_BULLET;
				else
					eBlockType = SBT_ITEM_BIG;

				pStage->ChangeBlock(m_tPos.x, m_tPos.y - 1, eBlockType);
				m_iJumpDir = JD_DOWN;
			}
			else
			{
				--m_tPos.y;
			}
			break;
		case JD_DOWN:
			if (m_tPos.y >= BLOCK_Y)
			{
				cout << "플레이어 사망" << endl;
				system("pause");
				m_tPos.y = BLOCK_Y - 1;
			}

			else if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) == SBT_WALL)
			{
				m_iJumpDir = JD_STOP;
				m_bJump = false;
			}
			else
				++m_tPos.y;
			break;
		}
	}

	if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) != SBT_WALL && !m_bJump)
	{
		++m_tPos.y;
	}

	STAGE_BLOCK_TYPE eCurBlockType = (STAGE_BLOCK_TYPE)pStage->GetBlock(m_tPos.x, m_tPos.y);

	if (eCurBlockType == SBT_COIN)
	{
		pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
		m_iScore += 1000;
	}
	else if (eCurBlockType == SBT_ITEM_BULLET)
	{
		m_bBulletFire = true;
		pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
	}
	else if (eCurBlockType == SBT_END)
	{
		m_bComplete = true;
	}

	if (m_tPos.y >= BLOCK_Y)
	{
		cout << "플레이어 사망" << endl;
		m_tPos = pStage->GetStart();
		m_iScore = 0;
		pStage->ResetStage();
		system("pause");
		return;
	}

	//VK_LBUTTON : 마우스 왼쪽 버튼을 눌렀을 때
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_bBulletFire)
	{
	}
}