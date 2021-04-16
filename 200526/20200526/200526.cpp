#include <iostream>
#include <time.h>

using namespace std;

int main() {
	system("cls");

	srand((unsigned int)time(0));

	int iPlayer, iAi;

	enum SRP {
		SRP_S = 1,
		SRP_R,
		SRP_P,
		SRP_END
	};

	while (true) {
		cout << "1. 가위\n";
		cout << "2. 바위\n";
		cout << "3. 보\n";
		cout << "4. 종료\n";
		cout << "메뉴를 선택하세요 : ";
		cin >> iPlayer;

		if (iPlayer < SRP_S || iPlayer > SRP_END) {
			cout << "잘못된 값을 입력하였습니다.\n";
			system("pause");
			continue;
		}
		else if (iPlayer == SRP_END)
			break;

		//봇이 선택한다
		iAi = rand() % 3 + SRP_S;

		switch (iAi) {
		case SRP_S:
			cout << "AI : 가위\n";
			break;
		case SRP_R:
			cout << "AI : 바위\n";
			break;
		case SRP_P:
			cout << "AI : 보\n";
			break;
		}

		int iWin = iPlayer - iAi;

		/*
		if (iWin == 1 || iWin == -2)
			cout << "Player 승리\n";
		else if (iWin == 0)
			cout << "비김\n";
		else
			cout << "AI 승리\n";
		*/

		switch (iWin)
		{
		case 1:
		case -2:
			cout << "Player 승리\n";
			break;
		case 0:
			cout << "비김\n";
			break;
		default:
			cout << "AI 승리\n";
			break;
		}

		system("pause");
		cout << "\n";
	}

	return 0;
}