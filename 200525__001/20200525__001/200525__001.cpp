#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	typedef enum NUM {
		NUM_0 = 10,
		NUM_1,
		NUM_2 = 0x0010,
		NUM_3
	}Num;

	int iNum;
	cout << "숫자를 입력하세요 : ";
	cin >> iNum;

#define NUM_4	4

	switch (iNum)
	{
	case NUM_1:
		cout << "입력한 숫자는 1입니다. " << endl;
		break;
	case NUM_2:
		cout << "입력한 숫자는 2입니다. " << endl;
		break;
	case NUM_3:
		cout << "입력한 숫자는 3입니다. " << endl;
		break;
	case NUM_4:
		cout << "입력한 숫자는 4입니다. " << endl;
		break;
	default:
		cout << "그 외의 숫자입니다." << endl;
		break;
	}

	cout << sizeof(NUM) << endl;
	cout << typeid(NUM).name() << endl;
	/*
	int iNum;

	srand((unsigned int)time(0));

	cout << rand() << endl;
	cout << rand() << endl;
	cout << rand() << endl;
	cout << (rand() % 10000 / 100.f) << endl;

	int iUpgrade = 0;
	cout << "Upgrade 기본 수치를 입력하세요 : ";
	cin >> iUpgrade;

	float fPercent = rand() % 10000 / 100.f;

	cout << "Upgrade : " << iUpgrade << endl;
	cout << "Percent : " << fPercent << endl;

	if (iUpgrade <= 3)
		cout << "강화 성공\n";
	else if (4 <= iUpgrade && iUpgrade <= 6) {
		if (fPercent < 40.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	}
	else if (7 <= iUpgrade && iUpgrade <= 9) {
		if (fPercent < 10.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	}
	else if (10 <= iUpgrade && iUpgrade <= 13) {
		if (fPercent < 1.f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	}
	else if (14 <= iUpgrade && iUpgrade <= 15) {
		if (fPercent < 0.01f)
			cout << "강화 성공\n";
		else
			cout << "강화 실패\n";
	}
	*/

	return 0;
}