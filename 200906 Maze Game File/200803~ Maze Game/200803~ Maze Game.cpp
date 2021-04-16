#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

/*
0	벽
1	길
2	시작점
3	도착점
4	폭탄
5	파워아이템
6	벽밀기 아이템
7	투명아이템
8	웜홀
*/

struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagplayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bPushOnOff;
	bool		bTransparency;
	int			iBombPower;
}PLAYER, * PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos,
	PPOINT pEndPos)
{
	//mazeList.txt 불러와서 미로 목록 만든다.
	FILE* pFile = NULL;

	fopen_s(&pFile, "mazeList.txt", "rt");

	char** pMazeList = NULL;

	if (pFile)
	{
		char cCount;

		fread(&cCount, 1, 1, pFile);

		int iMazeCount = atoi(&cCount);
		fread(&cCount, 1, 1, pFile);

		//char* 배열을 미로 개수만큼 할당
		pMazeList = new char* [iMazeCount];

		for (int i = 0; i < iMazeCount; i++)
		{
			int iNameCount = 0;
			//현재 미로의 파일 이름을 저장할 배열 256개로 넉넉히 할당
			pMazeList[i] = new char[256];

			while (true)
			{
				fread(&cCount, 1, 1, pFile);

				if (cCount != '\n')
				{
					pMazeList[i][iNameCount] = cCount;
					++iNameCount;
				}
				else
					break;
			}
			//파일 이름 마지막에 0 추가.
			pMazeList[i][iNameCount] = 0;
		}

		fclose(pFile);

		//읽을 파일 목록 작성 완료. 각 파일중 하나를 선택해서 미로 설정
		for (int i = 0; i < iMazeCount; i++)
		{
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}

		cout << "미로를 선택하세요 : ";
		int iSelect;
		cin >> iSelect;

		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile)
		{
			for (int i = 0; i < 20; ++i)
			{
				fread(Maze[i], 1, 20, pFile);
				//현재 줄의 미로 검사. 시작점/도착점 있는지 검사
				for (int j = 0; j < 20; ++j)
				{
					if (Maze[i][j] == '2')
					{
						pStartPos->x = j;
						pStartPos->y = i;

						pPlayer->tPos = *pStartPos;
					}
					else if (Maze[i][j] == '3')
					{
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}
				fread(&cCount, 1, 1, pFile);
			}

			fclose(pFile);
		}
	}
	/*
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 12;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111000000000");
	strcpy_s(Maze[2], "00100000001111111000");
	strcpy_s(Maze[3], "00101111100000001000");
	strcpy_s(Maze[4], "01101000100000111000");
	strcpy_s(Maze[5], "01000011111111001000");
	strcpy_s(Maze[6], "01111110100001001000");
	strcpy_s(Maze[7], "01000100101111001000");
	strcpy_s(Maze[8], "01000100111000001000");
	strcpy_s(Maze[9], "01110100001111111000");
	strcpy_s(Maze[10], "00100100000000010000");
	strcpy_s(Maze[11], "00100111111111110000");
	strcpy_s(Maze[12], "11100100000000010000");
	strcpy_s(Maze[13], "10000100111111111110");
	strcpy_s(Maze[14], "01111101100000000010");
	strcpy_s(Maze[15], "01000001000000000110");
	strcpy_s(Maze[16], "01100001111110001100");
	strcpy_s(Maze[17], "00111111000010001000");
	strcpy_s(Maze[18], "00100000000011111000");
	strcpy_s(Maze[19], "00000000000030000000");
	*/
}

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "♨";
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "☆";
			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
			else if (Maze[i][j] == '5')
				cout << "㈜";
			else if (Maze[i][j] == '6')
				cout << "※";
			else if (Maze[i][j] == '7')
				cout << "▷";
		}
		cout << endl;
	}

	cout << "폭탄파워 : " << pPlayer->iBombPower << endl;
	cout << "벽통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";
	cout << "벽밀기 : ";
	if (pPlayer->bWallPush)
	{
		cout << "가능 / ";
		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "불가능 / OFF" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		if (pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;

		return true;
	}
	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;

		return true;
	}
	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	//다음이 인덱스 있음
	if (pPlayer->tPos.y - 1 >= 0)
	{
		//벽인지 체크
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			//다음이 벽이나 폭탄이 아니면 이동
			--pPlayer->tPos.y;
		}
		//벽 밀기가 가능하고 바로 다음칸이 벽일 경우
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			// 벽밀기가 ON 상태일 경우
			if (pPlayer->bPushOnOff)
			{
				//다다음칸이 0보다 크거나 같을 경우 인덱스가 있다는 의미
				if (pPlayer->tPos.y - 2 >= 0)
				{
					//다다음칸이 길이어야 밀기가 가능하다. 그러므로 길인지 체크한다.
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency) {
							--pPlayer->tPos.y;
						}
					}
					//다다음칸이 벽이 아닐 경우 벽을 밀어낸다
					else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] != '0')
					{
						//다다음칸을 벽으로 하고
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						//다음칸은 벽이었는데 길로 만들어준다
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						//플레이어를 이동시킨다.
						--pPlayer->tPos.y;
					}
				}
				else if (pPlayer->tPos.y - 2 == -1) {
					if (pPlayer->bTransparency) {
						--pPlayer->tPos.y;
						if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
							Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
						return;
					}
				}
				else {
					return;
				}
			}
			//벽 밀기 OFF 상태일 경우
			else if (pPlayer->bTransparency) {
				--pPlayer->tPos.y;

				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
				return;
			}
		}
		else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4') {
			if (pPlayer->bTransparency) {
				--pPlayer->tPos.y;
			}
		}
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
	//다음 인덱스 없을 때
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	//다음이 인덱스 있음
	if (pPlayer->tPos.y + 1 <= 19)
	{
		//벽인지 체크
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			//다음이 벽이나 폭탄이 아니면 이동
			++pPlayer->tPos.y;
		}
		//벽 밀기가 가능하고 바로 다음칸이 벽일 경우
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			// 벽밀기가 ON 상태일 경우
			if (pPlayer->bPushOnOff)
			{
				//다다음칸이 0보다 크거나 같을 경우 인덱스가 있다는 의미
				if (pPlayer->tPos.y + 2 <= 19)
				{
					//다다음칸이 길이어야 밀기가 가능하다. 그러므로 길인지 체크한다.
					if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency) {
							++pPlayer->tPos.y;
						}
					}
					//다다음칸이 벽이 아닐 경우 벽을 밀어낸다
					else if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] != '0')
					{
						//다다음칸을 벽으로 하고
						Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						//다음칸은 벽이었는데 길로 만들어준다
						Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						//플레이어를 이동시킨다.
						++pPlayer->tPos.y;
					}
				}
				else if (pPlayer->tPos.y + 2 == 20) {
					if (pPlayer->bTransparency) {
						++pPlayer->tPos.y;
						if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
							Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
						return;
					}
				}
				else {
					return;
				}
			}
			//벽 밀기 OFF 상태일 경우
			else if (pPlayer->bTransparency) {
				++pPlayer->tPos.y;

				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
				return;
			}
		}
		else if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4') {
			if (pPlayer->bTransparency) {
				++pPlayer->tPos.y;
			}
		}
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
	//다음 인덱스 없을 때
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	//다음이 인덱스 있음
	if (pPlayer->tPos.x + 1 <= 19)
	{
		//벽인지 체크
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			//다음이 벽이나 폭탄이 아니면 이동
			++pPlayer->tPos.x;
		}
		//벽 밀기가 가능하고 바로 다음칸이 벽일 경우
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			// 벽밀기가 ON 상태일 경우
			if (pPlayer->bPushOnOff)
			{
				//다다음칸이 0보다 크거나 같을 경우 인덱스가 있다는 의미
				if (pPlayer->tPos.x + 2 <= 19)
				{
					//다다음칸이 길이어야 밀기가 가능하다. 그러므로 길인지 체크한다.
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '0')
					{
						if (pPlayer->bTransparency) {
							++pPlayer->tPos.x;
						}
					}
					//다다음칸이 벽이 아닐 경우 벽을 밀어낸다
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] != '0')
					{
						//다다음칸을 벽으로 하고
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						//다음칸은 벽이었는데 길로 만들어준다
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						//플레이어를 이동시킨다.
						++pPlayer->tPos.x;
					}
				}
				else if (pPlayer->tPos.x + 2 == 20) {
					if (pPlayer->bTransparency) {
						++pPlayer->tPos.x;
						if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
							Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
						return;
					}
				}
				else {
					return;
				}
			}
			//벽 밀기 OFF 상태일 경우
			else if (pPlayer->bTransparency) {
				++pPlayer->tPos.x;

				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
				return;
			}
		}
		//벽밀기 불가능
		else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4') {
			if (pPlayer->bTransparency) {
				++pPlayer->tPos.x;
			}
		}
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
	//다음 인덱스 없을 때
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	//다음이 인덱스 있음
	if (pPlayer->tPos.x - 1 >= 0)
	{
		//벽인지 체크
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			//다음이 벽이나 폭탄이 아니면 이동
			--pPlayer->tPos.x;
		}
		//벽 밀기가 가능하고 바로 다음칸이 벽일 경우
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			// 벽밀기가 ON 상태일 경우
			if (pPlayer->bPushOnOff)
			{
				//다다음칸이 0보다 크거나 같을 경우 인덱스가 있다는 의미
				if (pPlayer->tPos.x - 2 >= 0)
				{
					//다다음칸이 길이어야 밀기가 가능하다. 그러므로 길인지 체크한다.
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '0')
					{
						if (pPlayer->bTransparency) {
							--pPlayer->tPos.x;
						}
					}
					//다다음칸이 벽이 아닐 경우 벽을 밀어낸다
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] != '0')
					{
						//다다음칸을 벽으로 하고
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						//다음칸은 벽이었는데 길로 만들어준다
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						//플레이어를 이동시킨다.
						--pPlayer->tPos.x;
					}
				}
				else if (pPlayer->tPos.x - 2 == -1) {
					if (pPlayer->bTransparency) {
						--pPlayer->tPos.x;
						if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
							Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
						return;
					}
				}
				else {
					return;
				}
			}
			//벽 밀기 OFF 상태일 경우
			else if (pPlayer->bTransparency) {
				--pPlayer->tPos.x;

				if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
					Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
				return;
			}
		}
		//벽밀기 불가능
		else if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4') {
			if (pPlayer->bTransparency) {
				--pPlayer->tPos.x;
			}
		}
		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
	//다음 인덱스 없을 때
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

void CreateBomb(char Maze[21][21], const PPLAYER pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount == 5)
		return;
	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; i++)
	{
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pBombArr,
	int* pBombCount)
{
	for (int i = 0; i < *pBombCount; i++)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = pStartPos->x;
			pPlayer->tPos.y = pStartPos->y;
		}

		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					//아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
					{
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
					}
				}
				//플레이어가 폭탄에 맞으면 시작지점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = pStartPos->x;
					pPlayer->tPos.y = pStartPos->y;
				}
			}
			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					//아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
					{
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
					}
				}

				//플레이어가 폭탄에 맞으면 시작지점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = pStartPos->x;
					pPlayer->tPos.y = pStartPos->y;
				}
			}
			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					//아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
					else
					{
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
					}
				}

				//플레이어가 폭탄에 맞으면 시작지점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = pStartPos->x;
					pPlayer->tPos.y = pStartPos->y;
				}
			}
			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					//아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
					{
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
					}
				}

				//플레이어가 폭탄에 맞으면 시작지점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = pStartPos->x;
					pPlayer->tPos.y = pStartPos->y;
				}
			}
		}
	}

	*pBombCount = 0;
}

int main()
{
	srand((unsigned int)time(0));

	//20 x 20 미로 만들어준다.
	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	//미로를 설정한다
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");

		//미로를 출력한다
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착!" << endl;
			break;
		}

		cout << "t : 폭탄 설치\tu : 폭탄 터트리기\ti : 벽밀기 ON/OFF" << endl;
		cout << "w: 위\ts : 아래\ta : 왼쪽\td : 오른쪽\tq : 종료";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;
		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		else if (cInput == 'u' || cInput == 'U')
			Fire(strMaze, &tPlayer, &tStartPos, tBombPos, &iBombCount);
		else if (cInput == 'i' || cInput == 'I')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}
		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}

	return 0;
}