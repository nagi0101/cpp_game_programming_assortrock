#include <iostream>

using namespace std;

int main()
{
	/*
	레퍼런스
	*/

	int iNumber = 100;
	int iNumber1 = 9999;
	//iRefNum 레퍼런스 변수는 iNumber를 참조한다.
	int& iRefNum = iNumber;

	iRefNum = 1234;

	iRefNum = iNumber1;

	cout << iNumber << endl;
	cout << sizeof(iRefNum) << endl;

	return 0;
}