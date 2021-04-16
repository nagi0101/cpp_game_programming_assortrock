/*
버그:
HARD 난이도에서 AI가 1빙고 이후 숫자 선택을 하지 않으며, iLine은 기존 라인,
iInput은 플레이어가 입력한 숫자를 가지고 있음.
*/

#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER {
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

void printBingo(int iNumber[]) {
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++)
			if (iNumber[i * 5 + k] == INT_MAX)
				cout << "*\t";
			else
				cout << iNumber[i * 5 + k] << "\t";
		cout << endl;
	}
}

int countBingo(int iNumber[]) {
	bool iLBingo;
	int iBingo = 0;
	//세로줄 빙고 계산
	for (int i = 0; i < 5; i++) {
		iLBingo = true;
		for (int k = 0; k < 5; k++) {
			if (iNumber[i + 5 * k] != INT_MAX) {
				iLBingo = false;
				break;
			}
		}
		if (iLBingo == true)
			iBingo++;
	}
	//가로줄 빙고 계산
	for (int i = 0; i < 5; i++) {
		iLBingo = true;
		for (int k = 0; k < 5; k++) {
			if (iNumber[i * 5 + k] != INT_MAX) {
				iLBingo = false;
				break;
			}
		}
		if (iLBingo == true)
			iBingo++;
	}
	//오른쪽 위로 상승하는 대각선 계산
	iLBingo = true;
	for (int i = 0; i < 5; i++) {
		if (iNumber[4 + 4 * i] != INT_MAX) {
			iLBingo = false;
			break;
		}
	}
	if (iLBingo == true)
		iBingo++;
	//오른쪽 아래로 하강하는 대각선 계산
	iLBingo = true;
	for (int i = 0; i < 5; i++) {
		if (iNumber[6 * i] != INT_MAX) {
			iLBingo = false;
			break;
		}
	}
	if (iLBingo == true)
		iBingo++;

	return iBingo;
}

void shuffle(int iNumber[]) {
	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		tmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = tmp;
	}
}

int main() {
	int iNumber[25] = {};
	int iAINumber[25] = {};

	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}
	srand((unsigned int)time(0));

	//shuffle
	shuffle(iNumber);
	shuffle(iAINumber);

	//AI 난이도 선택
	int iAIMode;
	while (true) {
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 난이도를 선택하세요 : ";
		cin >> iAIMode;
		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}

	/*
	EASY : *로 바뀌지 않은 숫자 목록 중 랜덤하게 선택
	*/

	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;
	while (true) {
		system("cls");

		cout << "============== PLAYER ==============" << endl;

		//플레이어 빙고 출력
		printBingo(iNumber);

		//빙고 수 계산, 출력
		int iBingo = countBingo(iNumber);

		cout << iBingo << " Bingo!" << endl << endl;;

		cout << "================ AI ================" << endl;
		printBingo(iAINumber);

		int iAIBingo = countBingo(iAINumber);
		cout << iAIBingo << " Bingo!" << endl << endl;;

		//승리 조건 계산
		if (iBingo >= 5) {
			cout << "YOU WIN!!" << endl;
			break;
		}
		else if (iAIBingo >= 5) {
			cout << "YOU LOSE..." << endl;
			break;
		}

		//숫자 입력받기
		int iInput;
		cout << "1 ~ 25 사이의 숫자 입력. 0은 종료. : ";
		cin >> iInput;

		//종료
		if (iInput == 0)
			break;

		//예외처리
		if (iInput < 0 || iInput >25) {
			system("cls");
			continue;
		}

		//중복 체크
		bool bAcc = true;
		//입력받은 숫자 INT_MAX로 바꾸기
		for (int i = 0; i < 25; i++) {
			//같은 숫자 있는 경우
			if (iNumber[i] == iInput) {
				bAcc = false;
				iNumber[i] = INT_MAX;
				break;
			}
		}
		if (bAcc == true)
			continue;

		//중복이 아니면 AI의 숫자도 찾아 *로 바꾼다
		for (int i = 0; i < 25; i++) {
			//같은 숫자 있는 경우
			if (iAINumber[i] == iInput) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		//AI의 선택. 난이도에 따라 달라진다.
		int iNoneSelectCount = 0;
		switch (iAIMode) {
		case AM_EASY:
			//선택 안 된 숫자 목록 만들기
			for (int i = 0; i < 25; i++) {
				if (iAINumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					iNoneSelectCount++;
				}
			}
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			//현재 숫자 중 빙고줄 가능성이 가장 높은 줄 찾아서
			//그 줄의 숫자 중 하나를 *로 만든다
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			//줄 선택
			//가로
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {
					if (iAINumber[i * 5 + j] == INT_MAX) {
						++iStarCount;
					}
					if (iStarCount < 5 && iSaveCount < iStarCount) {
						iLine = i;
						iSaveCount = iStarCount;
					}
				}
			}
			//세로
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {
					if (iAINumber[j * 5 + i] == INT_MAX) {
						++iStarCount;
					}
					if (iStarCount < 5 && iSaveCount < iStarCount) {
						iLine = i + 5;
						iSaveCount = iStarCount;
					}
				}
			}
			//대각선(LT)
			iStarCount = 0;
			for (int i = 0; i < 25; i += 6) {
				if (iAINumber[i] == INT_MAX) {
					++iStarCount;
				}
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = LN_LT;
					iSaveCount = iStarCount;
				}
			}
			//대각선(RT)
			iStarCount = 0;
			for (int i = 4; i <= 20; i += 4) {
				if (iAINumber[i] == INT_MAX) {
					++iStarCount;
				}
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = LN_RT;
					iSaveCount = iStarCount;
				}
			}

			//줄 선택이 끝났으니 그 안의 *이 아닌 숫자 중 하나 선택한다
			if (iLine <= LN_H5) {
				//horizontal line is 0 ~4
				for (int i = 0; i < 5; i++) {
					//find number which isn't *
					if (iAINumber[iLine * 5 + i] != INT_MAX) {
						iInput = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}
			else if (iLine <= LN_V5) {
				for (int i = 0; i < 5; i++) {
					if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX) {
						iInput = iAINumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}
			else if (iLine == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (iAINumber[i] != INT_MAX) {
						iInput = iAINumber[i];
						break;
					}
				}
			}
			else if (iLine == LN_RT) {
				for (int i = 4; i <= 20; i += 4) {
					if (iAINumber[i] != INT_MAX) {
						iInput = iAINumber[i];
						break;
					}
				}
			}
		}

		//AI가 선택한 숫자도 플레이어와 AI의 숫자 *로 바꿔줌
		for (int i = 0; i < 25; i++) {
			if (iNumber[i] == iInput) {
				iNumber[i] = INT_MAX;
				break;
			}
		}
		for (int i = 0; i < 25; i++) {
			if (iAINumber[i] == iInput) {
				iAINumber[i] = INT_MAX;
				break;
			}
		}
	}

	cout << "게임을 종료합니다." << endl;
	return 0;
}