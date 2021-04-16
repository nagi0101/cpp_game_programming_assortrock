// 200629.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>
using namespace std;
/*
int main()
{
	int iLotto[45] = {};
	srand((unsigned int)time(0));

	//1 ~ 45까지의 숫자를 차례대로 넣어준다
	for (int i = 0; i < 45; ++i) {
		iLotto[i] = i + 1;
	}

	int iTemp, idx1, idx2;
	//100번정도 골고루 섞어준다
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}

	for (int i = 0; i < 6; i++) {
		cout << iLotto[i] << "\t";
	}
	cout << "보너스 번호 : " << iLotto[6];

	return 0;
}
*/

int main() {
	int iNum[9] = {};
	int i3Strk[3] = {};
	int iPlayer[3] = {};
	int iBall, iStrk, iOut;

	for (int i = 0; i < 9; i++) {
		iNum[i] = i + 1;
	}

	srand((unsigned int)time(0));
	int tmp, idx1, idx2;
	for (int i = 0; i < 20; ++i) {
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		tmp = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = tmp;
	}
	for (int i = 0; i < 3; i++) {
		i3Strk[i] = iNum[i];
	}

	while (true) {
		cout << "1 ~ 9 사이의 숫자 중 3개의 서로 다른 숫자를 입력하세요 : ";
		cin >> iPlayer[0] >> iPlayer[1] >> iPlayer[2];

		if (iPlayer[0] == 0 || iPlayer[1] == 0 || iPlayer[2] == 0)
			break;
		else if (iPlayer[0] < 0 || iPlayer[0]>9 || iPlayer[1] < 0 || iPlayer[1]>9 || iPlayer[2] < 0 || iPlayer[2]>9) {
			cout << "잘못된 숫자를 입력했습니다." << endl;
			continue;
		}
		else if (iPlayer[0] == iPlayer[1] || iPlayer[1] == iPlayer[2] || iPlayer[2] == iPlayer[0]) {
			cout << "중복된 숫자가 있습니다." << endl;
			continue;
		}

		iBall = iStrk = 0;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (i3Strk[i] == iPlayer[k]) {
					if (i == k)
						iStrk++;
					else
						iBall++;
					break;
				}
			}
		}
		if (iStrk == 0 && iBall == 0)
			cout << "Out!" << endl;
		else
			cout << iStrk << " Strk\t" << iBall << " Ball!" << endl << endl;

		if (iStrk == 3) {
			cout << "You Win!!" << endl;
			break;
		}
	}
	cout << "게임을 종료합니다." << endl;
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁:
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.