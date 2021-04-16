#include <iostream>
#include <time.h>

//console input output
#include <conio.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	iNumber[24] = INT_MAX;
	int iStarIdx = 24;

	int tmp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		tmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = tmp;
	}

	while (true) {
		system("cls");
		for (int i = 0; i < 5; i++) {
			for (int k = 0; k < 5; k++) {
				if (iNumber[i * 5 + k] == INT_MAX) {
					cout << "*\t";
				}
				else
					cout << iNumber[i * 5 + k] << "\t";
			}
			cout << endl;
		}

		bool bWin = true;

		//정답 체크
		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}

		if (bWin == true) {
			cout << "숫자를 모두 맞췄습니다!" << endl;
			break;
		}

		cout << "w : 위  s : 아래  a : 왼쪽  d : 오른쪽  q : 종료";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput) {
		case 'w':
		case 'W':
			if (iStarIdx > 4) {
				iNumber[iStarIdx] = iNumber[iStarIdx - 5];
				iNumber[iStarIdx - 5] = INT_MAX;
				iStarIdx -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIdx < 20) {
				iNumber[iStarIdx] = iNumber[iStarIdx + 5];
				iNumber[iStarIdx + 5] = INT_MAX;
				iStarIdx += 5;
			}
			break;
		case'a':
		case'A':
			if (iStarIdx % 5 != 0) {
				iNumber[iStarIdx] = iNumber[iStarIdx - 1];
				iNumber[iStarIdx - 1] = INT_MAX;
				iStarIdx--;
			}
			break;
		case'd':
		case'D':
			if (iStarIdx % 5 != 4) {
				iNumber[iStarIdx] = iNumber[iStarIdx + 1];
				iNumber[iStarIdx + 1] = INT_MAX;
				iStarIdx++;
			}
			break;
		}
	}

	cout << "게임을 종료합니다." << endl;

	return 0;
}