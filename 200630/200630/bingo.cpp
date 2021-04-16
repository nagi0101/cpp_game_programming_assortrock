#include <iostream>
#include <time.h>

using namespace std;

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

	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
	}
	srand((unsigned int)time(0));

	//shuffle
	shuffle(iNumber);

	while (true) {
		system("cls");

		//빙고 출력
		printBingo(iNumber);

		//빙고 수 계산, 출력
		int iBingo = countBingo(iNumber);
		cout << iBingo << " Bingo!" << endl;

		//승리 조건 계산
		if (iBingo >= 5) {
			cout << "YOU WIN!!" << endl;
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
			cout << "잘못된 숫자를 입력했습니다." << endl;
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
	}

	cout << "게임을 종료합니다." << endl;
	return 0;
}