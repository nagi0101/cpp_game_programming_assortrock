// 200628.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>

using namespace std;

/*
enum NUM {
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3
};
#define NUM_4 4

enum SRP {
	SRP_S = 1,
	SRP_R,
	SRP_P,
	SRP_END
};
int main()
{
	srand((unsigned int)time(0));

	int iPlayer, iAI;

	while (true) {
		cout << endl;
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3. 보" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		cin >> iPlayer;

		if (iPlayer < SRP_S || iPlayer>SRP_END) {
			cout << "잘못된 값을 입력하였습니다." << endl;
			//일시정지
			system("pause");
			//반복문 처음으로 돌아감
			continue;
		}
		else if (iPlayer == 4)
			break;

		//봇이 선택함
		iAI = rand() % 3 + SRP_S;

		switch (iAI) {
		case SRP_S:
			cout << "AI : 가위" << endl;
			break;
		case SRP_R:
			cout << "AI : 바위" << endl;
			break;
		case SRP_P:
			cout << "AI : 보" << endl;
			break;
		}

		int iWin = iPlayer - iAI;

		if (iWin == 1 || iWin == -2) {
			cout << "이겼습니다!" << endl;
		}
		else if (iWin == 0) {
			cout << "비겼습니다!" << endl;
		}
		else {
			cout << "졌습니다!" << endl;
		}

		switch (iWin) {
		case 1:
		case -2:
			cout << "이겼습니다!" << endl;
			break;
		case 0:
			cout << "비겼습니다!" << endl;
			break;
		default:
			cout << "졌습니다!" << endl;
			break;
		}

		system("pause");
	}

	return 0;
}
*/

int main() {
	/*for (int i = 0; i < 10; i++)
		cout << i << endl;
	return 0;

	//구구단 2단 출력
	for (int i = 1; i < 10; i++)
		cout << "2 * " << i << " = " << 2 * i << endl;

	//1-100중 짝수 출력
	for (int i = 2; i <= 100; i += 2)
		cout << i << endl;
	*/

	/*// 1 - 100중 3과 7의 공배수 출력
	for (int i = 1; i <= 100; i++) {
		if (i % 3 == 0 && i % 7 == 0)
			cout << i << endl;
	}*/

	/*for (int i = 2; i < 10; i++) {
		for (int k = 1; k < 10; k++) {
			cout << i << " * " << k << " = " << i * k << endl;
		}
		cout << endl;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	for (int l = 0; l < 4; l++) {
		for (int s = 0; s < 4 - (l + 1); s++) {
			cout << " ";
		}
		for (int k = 0; k < 2 * (l + 1) - 1; k++) {
			cout << "*";
		}
		cout << endl;
	}
	system("cls");*/

	/*
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int l = 1; l <= 3; l++) {
				if (((i - 1) * 3 + (l + 1)) % 3 == 1) {
					cout << (i - 1) * 3 + (l + 1) << " * " << j << " = " << ((i - 1) * 3 + (l + 1)) * j << endl;
				}
				else {
					cout << (i - 1) * 3 + (l + 1) << " * " << j << " = " << ((i - 1) * 3 + (l + 1)) * j << "\t";
				}
			}
		}
		cout << endl;
	}
	*/

	/*for (int i = 2; i < 11; i += 3) {
		for (int j = 1; j <= 9; j++) {
			cout << i << " * " << j << " = " << i * j << "\t";
			cout << i + 1 << " * " << j << " = " << (i + 1) * j << "\t";
			cout << i + 2 << " * " << j << " = " << (i + 2) * j << endl;
		}
	}*/

	/*int iLine = 31;
	int iCount = 0;
	for (int i = 0; i < iLine; i++) {
		//blank : 3,2,1,0,1,2,3
		//star  : 1,3,5,7,5,3,1
		iCount = i;
		//i값이 7줄 기준 4, 5, 6 즉 밑의 삼각형을 구성할때만 if 문에 들어감
		if (i > iLine / 2) {
			iCount = iLine - 1 - i;
		}
		for (int j = 0; j < iLine / 2 - iCount; ++j) {
			cout << " ";
		}
		for (int j = 0; j < iCount * 2 + 1; j++) {
			cout << "*";
		}
		cout << endl;
	}*/

	/*
	int iNumber = 0;
	do {
		cout << iNumber << endl;
	} while (iNumber > 0);
	return 0;
	*/

	int iArray[10] = {};
	iArray[0] = 1234;
	for (int i = 0; i < 10; i++)
		cout << iArray[i] << endl;
	//cout << iArray[4] << endl;

	int iArray2[10][10];

	return 0;
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